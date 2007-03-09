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


#include <memory> // auto_ptr
#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_warning.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_returnable.hpp>
#include "./detail/pure_traversal.hpp"


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
        // 'Iterator' types must be the same.
        return *boost::polymorphic_downcast<To const *>(&from);
    }


    template< class T, class A, class Ptr > inline
    void assign_new(A const& a, Ptr& p)
    {
        // Boost v1.34 'shared_ptr' needs lvalue 'auto_ptr'.
        std::auto_ptr<T> ap(new T(a));
        p = ap;
    }


    template< class Reference, class Traversal, class Difference, class T = Traversal >
    struct placeholder :
        private boost::noncopyable
    {
        // In fact, 'shared_ptr' needs no virtual destructor,
        // but there is no way to suppress GCC warning.
        virtual ~placeholder() { }

        // Dr.Becker's way!
        typedef placeholder<Reference, T, Difference> most_derived_t;

        virtual Reference dereference() const = 0;
        virtual bool equal(most_derived_t const& other) const = 0;
        virtual void increment() = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::forward_traversal_tag, Difference, T> :
        placeholder<Reference, boost::single_pass_traversal_tag, Difference, T>
    {
        typedef placeholder<Reference, T, Difference> most_derived_t;
        virtual most_derived_t *clone() const = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::bidirectional_traversal_tag, Difference, T> :
        placeholder<Reference, boost::forward_traversal_tag, Difference, T>
    {
        virtual void decrement() = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::random_access_traversal_tag, Difference, T> :
        placeholder<Reference, boost::bidirectional_traversal_tag, Difference, T>
    {
        virtual void advance(Difference const& d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;
    };


    // customizes Clonable for 'clone_ptr'.
    template< class Reference, class Traversal, class Difference > inline
    placeholder<Reference, Traversal, Difference> *
    new_clone(placeholder<Reference, Traversal, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class From, class To, class Traversal >
    struct is_convertible_difference :
        boost::mpl::eval_if< boost::is_same<Traversal, boost::random_access_traversal_tag>,
            is_convertible_in_enable_if<From, To>,
            boost::mpl::true_
        >
    { };


    template< class Iterator, class Reference, class Traversal, class Difference >
    struct holder :
        placeholder<Reference, Traversal, Difference>
    {
    private:
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_reference<Iterator>::type, Reference>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_traversal<Iterator>::type, Traversal>));
        BOOST_MPL_ASSERT((is_convertible_difference<typename boost::iterator_difference<Iterator>::type, Difference, Traversal>));
 
        typedef holder self_t;
        typedef placeholder<Reference, Traversal, Difference> placeholder_t;

    public:
        explicit holder(Iterator const& held) :
            m_held(held)
        {
            // VC7.1 complains if this is at class scope.
            BOOST_STATIC_WARNING((is_returnable<typename boost::iterator_reference<Iterator>::type, Reference>::value)); 
        }

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
        typedef
            boost::iterator_facade<
                any_iterator<Reference, Traversal, Value, Difference>,
                Value,
                Traversal,
                Reference,
                Difference
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


template< class Iterator, class AnyIterator >
struct is_convertible_to_any_iterator :
    boost::mpl::and_<
        is_convertible_in_enable_if<
            typename boost::iterator_reference<Iterator>::type,
            typename AnyIterator::reference
        >,
        is_convertible_in_enable_if<
            typename boost::iterator_traversal<Iterator>::type,
            typename detail::pure_traversal<AnyIterator>::type
        >,
        any_iterator_detail::is_convertible_difference<
            typename boost::iterator_difference<Iterator>::type,
            typename AnyIterator::difference_type, typename detail::pure_traversal<AnyIterator>::type
        >
    >
{ };


template<
    class Reference,
    class Traversal,
    class Value,
    class Difference
>
struct any_iterator :
    any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type

{
private:
    typedef any_iterator self_t;
    typedef typename any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename any_iterator_detail::pimpl_of<Reference, Traversal, Difference>::type pimpl_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_iterator_detail::holder<Iterator, Reference, Traversal, Difference> type;
    };

public:
// structors
    any_iterator()
    { }

    // This constructor can't be implicit.
    // Use 'is_convertible_to_any_iterator' instead.
    // Dr.Becker's "UglyIssue.txt" tells in detail.
    template< class Iterator >
    explicit any_iterator(Iterator const& it) :
        m_pimpl(new typename holder_of<Iterator>::type(it))
    { }

    template< class R, class T, class V, class D >
    any_iterator(any_iterator<R, T, V, D> const& other,
        typename enable_if< is_convertible_to_any_iterator<any_iterator<R, T, V, D>, self_t> >::type = 0
    ) :
        m_pimpl(new typename holder_of< any_iterator<R, T, V, D> >::type(other))
    { }

    template< class Iterator >
    Iterator const& base() const
    {
        return any_iterator_detail::downcast<typename holder_of<Iterator>::type>(*m_pimpl).held();
    }

// assignment to work around 'explicit' above
    template< class Iterator >
    typename disable_if<boost::is_convertible<Iterator, self_t>, self_t&>::type
    operator=(Iterator const& it)
    {
        any_iterator_detail::assign_new<typename holder_of<Iterator>::type>(it, m_pimpl);
        return *this;
    }

private:
    pimpl_t m_pimpl;

friend class boost::iterator_core_access;
    Reference dereference() const
    {
        return m_pimpl->dereference();
    }

    // can't be a template; 'placeholder' type is fairly different.
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

    void advance(Difference const& d)
    {
        m_pimpl->advance(d);
    }

    Difference distance_to(self_t const& other) const
    {
        return m_pimpl->difference_to(*other.m_pimpl);
    }
};


} } // namespace pstade::oven


#endif
