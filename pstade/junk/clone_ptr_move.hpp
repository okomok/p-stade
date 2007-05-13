#ifndef PSTADE_CLONE_PTR_HPP
#define PSTADE_CLONE_PTR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This class is maybe nothing but workaround.
// The performance is, of course, bad.


// See: Clonable
//
// http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept
// T:CopyConstructible implies T:Clonable for any self_t T.


#include <algorithm> // swap
#include <memory> // auto_ptr
#include <boost/assert.hpp>
#include <boost/move.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/ptr_container/clone_allocator.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade {


template< class Clonable >
struct clone_ptr;


namespace clone_ptr_detail {


    template< class T > inline
    T *new_(T const& x)
    {
        return boost::heap_clone_allocator::allocate_clone(x);
    }

    template< class T > inline
    void delete_(T *ptr)
    {
        return boost::heap_clone_allocator::deallocate_clone(ptr);
    }


    template< class Clonable >
    struct super_
    {
        typedef
            radish::bool_testable < clone_ptr<Clonable>,
            radish::pointable     < clone_ptr<Clonable>, Clonable,
            radish::swappable     < clone_ptr<Clonable>,
            boost::totally_ordered< clone_ptr<Clonable>
            > > > >
        type;
    };


} // namespace clone_ptr_detail


template< class Clonable >
struct clone_ptr :
    clone_ptr_detail::super_<Clonable>::type,
    boost::movable< clone_ptr<Clonable> >
{
    typedef clone_ptr self_t;

// structors
    clone_ptr() :
        m_ptr(PSTADE_NULLPTR)
    { }

    ~clone_ptr()
    {
        clone_ptr_detail::delete_(m_ptr);
    }

    template< class Clonable_ >
    explicit clone_ptr(Clonable_ *p) :
        m_ptr(p)
    { }

    template< class Clonable_ >
    explicit clone_ptr(std::auto_ptr<Clonable_> ap) :
        m_ptr(ap.release())
    { }

// copy
    BOOST_LVALUE_COPY_CTOR(clone_ptr, (other)(:
        m_ptr(other ? clone_ptr_detail::new_(*other) : PSTADE_NULLPTR)),
    { })

    self_t& operator=(self_t const& other)
    {
        self_t(other).swap(*this);
        return *this;
    }

#if 0
    BOOST_LVALUE_ASSIGN(clone_ptr, (other),
    {
        self_t(other).swap(*this);
        return *this;
    })
#endif

// move
    clone_ptr(boost::move_from<self_t> other) :
        m_ptr(other.release().release())
    { }

#if 0
    self_t& operator=(boost::move_from<self_t> other)
    {
        self_t(other).swap(*this);
        return *this;
    }
#endif

    template< class Clonable_ >
    self_t& operator=(std::auto_ptr<Clonable_> ap)
    {
        self_t(ap).swap(*this);
        return *this;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_ptr);
    }

// pointable
    Clonable *operator->() const
    {
        BOOST_ASSERT(m_ptr);
        return m_ptr;
    }

    Clonable *get() const
    {
        return m_ptr;
    }

// swappable
    void swap(self_t& other)
    {
        std::swap(m_ptr, other.m_ptr);
    }

// totally_ordered
    bool operator< (self_t const& other) const
    {
        return m_ptr < other.m_ptr;
    }

    bool operator==(self_t const& other) const
    {
        return m_ptr == other.m_ptr;
    }

// release/reset
    std::auto_ptr<Clonable> release()
    {
        std::auto_ptr<Clonable> ap(m_ptr);
        m_ptr = PSTADE_NULLPTR;
        return ap;
    }

private:
    Clonable *m_ptr;
};


} // namespace pstade


#endif
