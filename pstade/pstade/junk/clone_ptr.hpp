#ifndef PSTADE_CLONE_PTR_HPP
#define PSTADE_CLONE_PTR_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes a copy-constructible type assignable and default-constructible.


// See:
//
// http://d.hatena.ne.jp/Cryolite/20060108


// Question:
//
// The default-constructibility seems to increase complexity.
//


#include <algorithm> // swap
#include <iosfwd> // basic_ostream
#include <boost/assert.hpp>
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/nullptr.hpp>


namespace pstade {


namespace clone_ptr_detail {


    struct deallocate
    {
        virtual ~deallocate() // not required, in fact.
        { }

        virtual void call(void *p) const = 0;
    };


    template< class T, class CloneAllocator >
    struct deallocate_impl :
        deallocate
    {
        void call(void *p) const // override
        {
            CloneAllocator::deallocate_clone( static_cast<T *>(p) );
        }
    };


} // namespace clone_ptr_detail


template<
    class T,
    class CloneAllocator = boost::heap_clone_allocator
>
struct clone_ptr
{
    // structors
    //
    clone_ptr() :
        m_ptr(PSTADE_NULLPTR)
    { }

    clone_ptr(clone_ptr const& other) :
        m_ptr(CloneAllocator::allocate_clone(*other)),
        m_pda(new clone_ptr_detail::deallocate_impl<T, CloneAllocator>())
    { }

    template< class T_ >
    explicit clone_ptr(T_ const& x) :
        m_ptr(CloneAllocator::allocate_clone(x)),
        m_pda(new clone_ptr_detail::deallocate_impl<T_, CloneAllocator>())
    { }

    ~clone_ptr()
    {
        if (m_ptr != PSTADE_NULLPTR)
            m_pda->call(m_ptr);
    }

    // modifiers
    //
    clone_ptr& operator=(clone_ptr const& other)
    {
        clone_ptr(other).swap(*this);
        return *this;
    }

    void reset()
    {
        clone_ptr().swap(*this);
    }

    void reset(T const& x)
    {
        clone_ptr(x).swap(*this);
    }

    void swap(clone_ptr& other)
    {
        std::swap(m_ptr, other.m_ptr);
        boost::swap(m_pda, other.m_pda);
    }

    // accessors
    //
    T& operator*() const
    {
        BOOST_ASSERT(m_ptr != PSTADE_NULLPTR);
        return *m_ptr;
    }

    T *operator->() const
    {
        BOOST_ASSERT(m_ptr != PSTADE_NULLPTR);
        return m_ptr;
    }

    T *get() const
    {
        return m_ptr;
    }

    typedef T element_type;
    typedef T value_type;
    typedef T *pointer;
    typedef typename boost::shared_ptr<T>::reference reference;

    // utilities
    //
    operator bool() const
    {
        return m_ptr != PSTADE_NULLPTR;
    }

    bool operator!() const
    {
        return m_ptr == PSTADE_NULLPTR;
    }

private:
    T *m_ptr;
    boost::shared_ptr<clone_ptr_detail::deallocate> m_pda;
};


template< class T1, class CloneAllocator1, class T2, class CloneAllocator2 >
bool operator==(clone_ptr<T1, CloneAllocator1> const& p1, clone_ptr<T2, CloneAllocator2> const& p2)
{
    if (!p1 && !p2) // both are null
        return true;
    else if (!p1 ^ !p2) // one is null, one isn't
        return false;
    else
        return *p1 == *p2;
}


template< class T1, class CloneAllocator1, class T2, class CloneAllocator2 > inline
bool operator!=(clone_ptr<T1, CloneAllocator1> const& p1, clone_ptr<T2, CloneAllocator2> const& p2)
{
    return !(p1 == p2);
}


template< class T1, class CloneAllocator1, class T2, class CloneAllocator2 >
bool operator<(clone_ptr<T1, CloneAllocator1> const& p1, clone_ptr<T2, CloneAllocator2> const& p2)
{
    if (!p1 && !p2)
        return false;
    else if (!p1 && p2)
        return true;
    else if (p1 && !p2)
        return false;
    else
        return *p1 < *p2;
}


template< class T1, class CloneAllocator1, class T2, class CloneAllocator2 >inline
void swap(clone_ptr<T1, CloneAllocator1>& p1, clone_ptr<T2, CloneAllocator2>& p2)
{
    p1.swap(p2);
}


template< class T, class CloneAllocator > inline
T *get_pointer(clone_ptr<T, CloneAllocator> const& p)
{
    return p.get();
}


template< class CharT, class Traits, class T, class CloneAllocator >
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, clone_ptr<T, CloneAllocator> const& p)
{
    if (p)
        os << *p;
    else
        os << p.get();

    return os;
}


template< class T > inline
clone_ptr<T> make_clone_ptr(T const& x)
{
    return clone_ptr<T>(x);
}


} // namespace pstade


#endif
