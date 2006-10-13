#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // swap
#include <cstddef> // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/iterator/iterator_categories.hpp> // tags
#include <boost/iterator/iterator_facade.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven {


template<
    class Reference,
    class Traversal,
    class Difference
>
struct any_iterator;


namespace any_iterator_detail {


    template< class T >
    struct clone_ptr :
        radish::pointable<clone_ptr<T>, T>
    {
    private:
        typedef clone_ptr self_t;

    public:
        clone_ptr() :
            m_ptr(PSTADE_NULLPTR)
        { }

        explicit clone_ptr(T *ptr) :
            m_ptr(ptr)
        { }

        clone_ptr(self_t const& other) :
            m_ptr(other->clone())
        { }

        ~clone_ptr()
        {
            boost::checked_delete(m_ptr);
        }

        self_t& operator=(self_t const& other)
        {
            self_t(other).swap(*this);
            return *this;
        }

        T *operator->() const
        {
            BOOST_ASSERT(m_ptr);
            return m_ptr;
        }

        void swap(self_t& other)
        {
            std::swap(m_ptr, other.m_ptr);
        }

    private:
        T *m_ptr;
    };


    struct clonable
    {
        virtual ~clonable() { };
        virtual clonable *clone() const = 0;
    };


    template<
        class Reference,
        class Difference
    >
    struct placeholder
    {
        virtual ~placeholder() { }
        virtual Reference dereference() const = 0;
        virtual bool equal(placeholder const& other) const = 0;
        virtual void increment() = 0;
        virtual void decrement() = 0;
        virtual void advance(Difference d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;

        virtual placeholder *clone() const = 0;
    };


    template< class Iterator >
    void decrement_aux(Iterator& it, boost::incrementable_traversal_tag)
    {
        pstade::unused(it);
    }

    template< class Iterator >
    void decrement_aux(Iterator& it, boost::bidirectional_traversal_tag)
    {
        --it;
    }


    template< class Iterator, class Difference >
    void advance_aux(Iterator& it, Difference d, boost::incrementable_traversal_tag)
    {
        pstade::unused(it, d);
    }

    template< class Iterator, class Difference >
    void advance_aux(Iterator& it, Difference d, boost::random_access_traversal_tag)
    {
        it += d;
    }


    template< class Difference, class Iterator >
    Difference difference_to_aux(Iterator const& first, Iterator const& last, boost::incrementable_traversal_tag)
    {
        pstade::unused(first, last);
        return Difference();
    }

    template< class Difference, class Iterator >
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
        typedef holder self_t;
        typedef placeholder<Reference, Difference> placeholder_t;

    public:
        holder(Iterator const& held) :
          m_held(held)
        { }

    public: 
        virtual Reference dereference() const
        {
            return *m_held;
        }

        virtual bool equal(placeholder_t const& other) const
        {
            return m_held == static_cast<self_t const&>(other).m_held;
        }

        virtual void increment()
        {
            ++m_held;
        }

        virtual void decrement()
        {
            any_iterator_detail::decrement_aux(m_held, Traversal());
        }

        virtual void advance(Difference d)
        {
            any_iterator_detail::advance_aux(m_held, d, Traversal());
        }

        virtual Difference difference_to(placeholder_t const& other) const
        {
            return any_iterator_detail::difference_to_aux<Difference>(
                m_held, static_cast<self_t const&>(other).m_held, Traversal());
        }

    public:
        virtual placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    private:
        Iterator m_held;
    };


    template<
        class Reference,
        class Traversal,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_facade<
            any_iterator<Reference, Traversal, Difference>,
            typename remove_cvr<Reference>::type,
            Traversal,
            Reference,
            Difference
        > type;
    };


} // namespace any_iterator_detail


template<
    class Reference,
    class Traversal,
    class Difference = std::ptrdiff_t
>
struct any_iterator :
    any_iterator_detail::super_<Reference, Traversal, Difference>::type
{
private:
    typedef any_iterator self_t;
    typedef typename any_iterator_detail::super_<Reference, Traversal, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef any_iterator_detail::placeholder<Reference, Difference> placeholder_t;

public:
    explicit any_iterator()
    { }

    template< class Iterator >
    explicit any_iterator(Iterator const& it) :
        m_pimpl(new any_iterator_detail::holder<Iterator, Reference, Traversal, Difference>(it))
    { }

template< class, class, class > friend struct any_iterator;

private:
    any_iterator_detail::clone_ptr<placeholder_t> m_pimpl;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pimpl->dereference();
    }

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

    void advance(diff_t d)
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
