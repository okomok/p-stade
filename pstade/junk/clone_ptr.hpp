#ifndef PSTADE_CLONE_PTR_HPP
#define PSTADE_CLONE_PTR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Clonable
//
// http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept
// T:CopyConstructible implies T:Clonable for any type T.


#include <algorithm> // swap
#include <memory> // auto_ptr
#include <boost/assert.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/ptr_container/clone_allocator.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade {


// clone_ptr
//

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
    clone_ptr_detail::super_<Clonable>::type
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
    clone_ptr(self_t const& other) :
        m_ptr(other ? clone_ptr_detail::new_(*other) : PSTADE_NULLPTR)
    { }

    self_t& operator=(self_t const& other)
    {
        self_t(other).swap(*this);
        return *this;
    }

    template< class Clonable_ >
    self_t& operator=(Clonable_ *p)
    {
        self_t(p).swap(*this);
        return *this;
    }

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


// clone_on_get_ptr
//

template< class Clonable >
struct clone_on_get_ptr;


namespace clone_on_get_ptr_detail {


    template< class Clonable >
    struct super_
    {
        typedef
            radish::bool_testable < clone_on_get_ptr<Clonable>,
            radish::pointable     < clone_on_get_ptr<Clonable>, Clonable,
            radish::swappable     < clone_on_get_ptr<Clonable>,
            boost::totally_ordered< clone_on_get_ptr<Clonable>
            > > > >
        type;
    };


} // namespace clone_on_get_ptr_detail


template< class Clonable >
struct clone_on_get_ptr :
    clone_on_get_ptr_detail::super_<Clonable>::type
{
    typedef clone_on_get_ptr self_t;

// structors
    clone_on_get_ptr()
    { }

    template< class Clonable_ >
    explicit clone_on_get_ptr(Clonable_ *p) :
        m_sp(p)
    { }

    template< class Clonable_ >
    explicit clone_on_get_ptr(std::auto_ptr<Clonable_> ap) :
        m_sp(ap.release())
    { }

// copy
    template< class Clonable_ >
    self_t& operator=(Clonable *p)
    {
        self_t(p).swap(*this);
        return *this;
    }

    template< class Clonable_ >
    self_t& operator=(std::auto_ptr<Clonable_> ap)
    {
        self_t(ap).swap(*this);
        return *this;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return m_sp || m_cp;
    }

// pointable
    Clonable *operator->() const
    {
        BOOST_ASSERT(m_sp || m_cp);
        return get();
    }

    Clonable *get() const
    {
        on_get();
        return m_cp.get();
    }

// swappable
    void swap(self_t& other)
    {
        m_cp.swap(other.m_cp);
        m_sp.swap(other.m_sp);
    }

// totally_ordered
    bool operator< (self_t const& other) const
    {
        if (!m_cp)
            return m_sp < other.m_sp;
        else
            return m_cp < other.m_cp;
    }

    bool operator==(self_t const& other) const
    {
        if (!m_cp)
            return m_sp == other.m_sp;
        else
            return m_cp == other.m_cp;
    }

// release/reset
    std::auto_ptr<Clonable> release()
    {
        get();
        return m_cp.release();
    }

private:
    mutable clone_ptr<Clonable> m_cp;
    mutable boost::shared_ptr<Clonable> m_sp;

    void on_get() const
    {
        if (!m_cp) {
            m_cp = m_sp.get();
            m_sp.reset();
        }
    }
};



} // namespace pstade


#endif
