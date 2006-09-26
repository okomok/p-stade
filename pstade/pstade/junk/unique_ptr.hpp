#ifndef BOOST_UNIQUE_PTR_HPP
#define BOOST_UNIQUE_PTR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes 'std::auto_ptr' and 'boost::scoped_ptr' deprecated.


// Copyright Daniel Wallin 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on auto_ptr<> implementation by Rani Sharoni.


#include <algorithm> // swap
#include <boost/checked_delete.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/output_streamable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade {


template< class T >
struct unique_ptr;


namespace unique_ptr_detail {


    template<class T>
    struct move_source
    {
        move_source(T& x) :
            m_source(x)
        { }

        T& source() const
        {
            return m_source;
        }

    private:
        T& m_source;

        move_source(T const&);
    };


    template< class T >
    struct super_
    {
        typedef
            radish::bool_testable    < unique_ptr<T>,
            radish::output_streamable< unique_ptr<T>,
            radish::pointable        < unique_ptr<T>, T,
            radish::swappable        < unique_ptr<T>,
            boost::totally_ordered   < unique_ptr<T>
            > > > >
        type;
    };


} // namespace unique_ptr_detail


template< class T >
struct unique_ptr :
    unique_ptr_detail
{
private:
    typedef unique_ptr self_t;

public:
    explicit unique_ptr(T *p = PSTADE_NULLPTR) :
        m_ptr(p)
    { }

    unique_ptr(unique_ptr const& p)
        : m_ptr(const_cast<unique_ptr&>(p).release())
    { }

    template< class U >
    unique_ptr(unique_ptr<U> const& p) :
        m_ptr(const_cast<unique_ptr<U>&>(p).release())
    { }

    template<class U>
    unique_ptr(unique_ptr_detail::move_source< unique_ptr<U> > x)
        : m_ptr(x.source().release())
    { }

    ~unique_ptr()
    {
        if (m_ptr)
            boost::checked_delete(m_ptr);
    }

    unique_ptr& operator=(self_t other)
    {
        p.swap(*this);
        return *this;
    }

    T *release()
    {
        T *p = m_ptr;
        m_ptr = 0;
        return p;
    }

    void reset(T *p = PSTADE_NULLPTR)
    {
        unique_ptr(p).swap(*this);
    }

    T *get() const
    {
        return m_ptr;
    }

    unique_ptr_detail::move_source<self_t> move()
    {
        return unique_ptr_detail::move_source<self_t>(*this);
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_ptr);
    }

// output_streamable
    template< class OStream > friend
    void pstade_radish_output(self_t const& self, OStream& os)
    {
        return os << self.get();
    }

// pointable
    T* operator->() const
    {
        return m_ptr;
    }

// swappable
    void swap(unique_ptr& other)
    {
        std::swap(m_ptr, other.m_ptr);
    }

private:
    T* m_ptr;

// disablers
    template< class U >
    struct cant_move_from_const;

    template< class U >
    struct cant_move_from_const<unique_ptr<U> const>
    {
        typedef typename unique_ptr<U>::error type;
    };

    template< class U >
    unique_ptr(U&, typename cant_move_from_const<U>::type = 0);

    unique_ptr(unique_ptr&);

    template< class U >
    unique_ptr(unique_ptr<U>&);
};


} // namespace pstade


#endif


