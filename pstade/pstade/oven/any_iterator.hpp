#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Is it possible to support OutputIterator?


#include <cstddef> // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/new_delete.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/unused.hpp>
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


    template<
        class Reference,
        class Difference
    >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual placeholder *clone() const = 0;

        virtual Reference dereference() const = 0;
        virtual bool equal(placeholder const& other) const = 0;
        virtual void increment() = 0;
        virtual void decrement() = 0;
        virtual void advance(Difference const& d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;
    };


    // Workaround:
    // If this definition is in 'placeholder' using friend-injection,
    // GCC3.4's ADL fails to find 'new_clone' for 'placeholder'.
    // 'pstade::new_' does something bad for GCC.
    // It seems a bug of GCC. I don't certainly know, though.
    template< class Reference, class Difference > inline
    placeholder<Reference, Difference> *
    new_clone(placeholder<Reference, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class Iterator > inline
    void decrement_aux(Iterator& it, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(it);
    }

    template< class Iterator > inline
    void decrement_aux(Iterator& it, boost::bidirectional_traversal_tag)
    {
        --it;
    }


    template< class Iterator, class Difference > inline
    void advance_aux(Iterator& it, Difference const& d, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(it, d);
    }

    template< class Iterator, class Difference > inline
    void advance_aux(Iterator& it, Difference const& d, boost::random_access_traversal_tag)
    {
        it += d;
    }


    template< class Difference, class Iterator > inline
    Difference difference_to_aux(Iterator const& first, Iterator const& last, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(first, last);
        return Difference();
    }

    template< class Difference, class Iterator > inline
    Difference difference_to_aux(Iterator const &first, Iterator const& last, boost::random_access_traversal_tag)
    {
        return last - first;
    }


    template<
        class Iterator,
        class Reference,
        class Traversal,
        class Difference
    >
    struct holder :
        placeholder<Reference, Difference>
    {
    private:
        BOOST_MPL_ASSERT((detail::reference_is_convertible_aux<typename boost::iterator_reference<Iterator>::type, Reference>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_traversal<Iterator>::type,  Traversal>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_difference<Iterator>::type, Difference>));

        typedef holder self_t;
        typedef placeholder<Reference, Difference> placeholder_t;

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

        virtual placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    public:
        virtual Reference dereference() const
        {
            return *m_held;
        }

        virtual bool equal(placeholder_t const& other) const
        {
            return m_held == any_iterator_detail::downcast<self_t>(other).m_held;
        }

        virtual void increment()
        {
            ++m_held;
        }

        virtual void decrement()
        {
            any_iterator_detail::decrement_aux(m_held, Traversal());
        }

        virtual void advance(Difference const& d)
        {
            any_iterator_detail::advance_aux(m_held, d, Traversal());
        }

        virtual Difference difference_to(placeholder_t const& other) const
        {
            return any_iterator_detail::difference_to_aux<Difference>(
                m_held, any_iterator_detail::downcast<self_t>(other).m_held, Traversal());
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
    typedef typename any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename boost::iterator_category_to_traversal<typename super_t::iterator_category>::type trv_t;
    typedef typename super_t::difference_type diff_t;
    typedef any_iterator_detail::placeholder<ref_t, diff_t> placeholder_t;

public:
    explicit any_iterator()
    { }

    // There is no implicit constructor which can be used to convert.
    // 'm_pimpl' must hold the same 'Iterator_' type which enables
    // 'holder::equals/difference_to' to downcast properly.
    // But there is no way to know the 'Iterator_' type beforehand,
    // thus no way to know the convertibility.
    // Note that this implies that 'Other' below is always the same as
    // self type.

    template< class Iterator_ >
    explicit any_iterator(Iterator_ const& it) :
        m_pimpl(op_new_auto<
            any_iterator_detail::holder<Iterator_, ref_t, trv_t, diff_t>
        >()(it))
    { }

    template< class Iterator_ >
    Iterator_ const& base() const
    {
        return any_iterator_detail::downcast<
            any_iterator_detail::holder<Iterator_, ref_t, trv_t, diff_t>
        >(*m_pimpl).held();
    }

private:
    clone_ptr<placeholder_t> m_pimpl;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pimpl->dereference();
    }

    template< class Other >
    bool equal(Other const& other) const
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

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return m_pimpl->difference_to(*other.m_pimpl);
    }
};


} } // namespace pstade::oven


#endif
