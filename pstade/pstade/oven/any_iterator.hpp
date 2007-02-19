#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Waiting for Dr.Becker's implementation to come into the Boost...
// http://thbecker.net/free_software_utilities/type_erasure_for_cpp_iterators/start_page.html


#include <cstddef> // ptrdiff_t
#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./detail/reference_is_convertible.hpp"


namespace pstade { namespace oven {


template<
    class Reference,
    class Traversal,
    class Value,
    class Difference
>
struct any_iterator;


namespace any_iterator_detail {


    template< class To, class From > inline
    To const& downcast(From const& from)
    {
        // 'Iterator_' types must be the same.
        return *boost::polymorphic_downcast<To const *>(&from);
    }


    template< class Reference, class Traversal, class Difference, class Traversal_ = Traversal >
    struct placeholder :
        private boost::noncopyable
    {
        // In fact, 'shared_ptr' needs no virtual destructor,
        // but there is no way to suppress GCC warning.
        virtual ~placeholder() { }

        // Dr.Becker's way!
        typedef placeholder<Reference, Traversal_, Difference> most_derived_t;

        virtual Reference dereference() const = 0;
        virtual bool equal(most_derived_t const& other) const = 0;
        virtual void increment() = 0;
    };

    template< class Reference, class Difference, class Traversal_ >
    struct placeholder<Reference, boost::forward_traversal_tag, Difference, Traversal_> :
        placeholder<Reference, boost::single_pass_traversal_tag, Difference, Traversal_>
    {
        typedef placeholder<Reference, Traversal_, Difference> most_derived_t;
        virtual most_derived_t *clone() const = 0;
    };

    template< class Reference, class Difference, class Traversal_ >
    struct placeholder<Reference, boost::bidirectional_traversal_tag, Difference, Traversal_> :
        placeholder<Reference, boost::forward_traversal_tag, Difference, Traversal_>
    {
        virtual void decrement() = 0;
    };

    template< class Reference, class Difference, class Traversal_ >
    struct placeholder<Reference, boost::random_access_traversal_tag, Difference, Traversal_> :
        placeholder<Reference, boost::bidirectional_traversal_tag, Difference, Traversal_>
    {
        virtual void advance(Difference const& d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;
    };


    // Clonable concept
    template< class Reference, class Traversal, class Difference > inline
    placeholder<Reference, Traversal, Difference> *
    new_clone(placeholder<Reference, Traversal, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class Iterator, class Traversal, class Difference >
    struct is_valid_difference :
        boost::mpl::eval_if< boost::is_same<Traversal, boost::random_access_traversal_tag>,
            boost::is_convertible<typename boost::iterator_difference<Iterator>::type, Difference>,
            boost::mpl::true_
        >
    { };


    template< class Iterator, class Reference, class Traversal, class Difference >
    struct holder :
        placeholder<Reference, Traversal, Difference>
    {
    private:
        BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<typename boost::iterator_reference<Iterator>::type, Reference>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_traversal<Iterator>::type, Traversal>));
        BOOST_MPL_ASSERT((is_valid_difference<Iterator, Traversal, Difference>));

        typedef holder self_t;
        typedef placeholder<Reference, Traversal, Difference> placeholder_t;

    public:
        explicit holder(Iterator const& held) :
            m_held(held)
        { }

        Iterator const& held() const
        {
            return m_held;
        }

    private:
        Iterator m_held;

    // These may be 'virtual', depending on the base 'placeholder'.

        placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    public:
        Reference dereference() const
        {
            return *m_held;
        }

        bool equal(placeholder_t const& other) const
        {
            return m_held == any_iterator_detail::downcast<self_t>(other).m_held;
        }

        void increment()
        {
            ++m_held;
        }

        void decrement()
        {
            --m_held;
        }

        void advance(Difference const& d)
        {
            m_held += d;
        }

        Difference difference_to(placeholder_t const& other) const
        {
            return any_iterator_detail::downcast<self_t>(other).m_held - m_held;
        }
    };


    template<
        class Reference,
        class Traversal,
        class Value,
        class Difference
    >
    struct super_
    {
        typedef typename
            use_default_eval_to< Value, remove_cvr<Reference> >::type
        value_t;

        typedef typename
            use_default_to<Difference, std::ptrdiff_t>::type
        diff_t;

        typedef
            boost::iterator_facade<
                any_iterator<Reference, Traversal, Value, Difference>,
                value_t,
                Traversal,
                Reference,
                diff_t
            >
        type;
    };


    template< class Reference, class Traversal, class Difference >
    struct pimpl_of
    {
        typedef
            placeholder<Reference, Traversal, Difference>
        placeholder_t;

        // As a recursive range is Forward, 'shared_ptr' isn't used.
        // Hence there is no reference-cycles.
        typedef typename
            boost::mpl::if_< boost::is_same<Traversal, boost::single_pass_traversal_tag>,
                boost::shared_ptr<placeholder_t>,
                clone_ptr<placeholder_t>
            >::type
        type;
    };


} // namespace any_iterator_detail


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_iterator :
    any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type
{
private:
    typedef any_iterator self_t;
    typedef typename any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename any_iterator_detail::pimpl_of<Reference, Traversal, diff_t>::type pimpl_t;

public:
    explicit any_iterator()
    { }

    // The constructor from 'Iterator_' isn't implicit.
    // 'UglyIssue.txt' of Dr.Becker's implemenation tells why.

    template< class Iterator_ >
    explicit any_iterator(Iterator_ const& it) :
        m_pimpl(new
            any_iterator_detail::holder<Iterator_, Reference, Traversal, diff_t>
        (it))
    { }

template< class, class, class, class > friend struct any_iterator;
    template< class R, class T, class V, class D >
    any_iterator(any_iterator<R, T, V, D> const& other,
        typename enable_if< boost::is_convertible<R, Reference> >::type = 0,
        typename enable_if< boost::is_convertible<T, Traversal> >::type = 0,
        typename enable_if< boost::is_convertible<typename any_iterator<R, T, V, D>::diff_t, diff_t> >::type = 0
    ) :
        m_pimpl(new
            any_iterator_detail::holder<any_iterator<R, T, V, D>, Reference, Traversal, diff_t>
        (other))
    { }

    template< class Iterator_ >
    Iterator_ const& base() const
    {
        return any_iterator_detail::downcast<
            any_iterator_detail::holder<Iterator_, Reference, Traversal, diff_t>
        >(*m_pimpl).held();
    }

private:
    pimpl_t m_pimpl;

friend class boost::iterator_core_access;
    Reference dereference() const
    {
        return m_pimpl->dereference();
    }

    // This can't take 'any_iterator<R, T, V, D>' without implicit conversion,
    // because 'placeholder' type is farely different.
    bool equal(self_t const& other) const
    {
        return m_pimpl->equal(*other.m_pimpl);
    }

    void increment()
    {
        m_pimpl->increment();
    }

    void decrement()
    {
        m_pimpl->decrement();
    }

    void advance(diff_t const& d)
    {
        m_pimpl->advance(d);
    }

    diff_t distance_to(self_t const& other) const
    {
        return m_pimpl->difference_to(*other.m_pimpl);
    }
};


} } // namespace pstade::oven


#endif
