#ifndef PSTADE_CLONE_PTR_HPP
#define PSTADE_CLONE_PTR_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20060108


// Question:
//
// Should be nullable?


#include <algorithm> // swap
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/shared_ptr.hpp>


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
    template< class U >
    explicit clone_ptr(U const& x) :
        m_ptr(CloneAllocator::allocate_clone(x)),
        m_pda(new clone_ptr_detail::deallocate_impl<U, CloneAllocator>())
    { }

    clone_ptr(clone_ptr const& other) :
        m_ptr(CloneAllocator::allocate_clone(*other)),
        m_pda(new clone_ptr_detail::deallocate_impl<T, CloneAllocator>())
    { }

    ~clone_ptr()
    {
        m_pda->call(m_ptr);
    }

    // modifiers
    //
    clone_ptr& operator=(clone_ptr const& other)
    {
        clone_ptr(other).swap(*this);
        return *this;
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
        return *m_ptr;
    }

    T *operator->() const
    {
        return m_ptr;
    }

    typedef T element_type;

private:
    T *m_ptr;
    boost::shared_ptr<clone_ptr_detail::deallocate> m_pda;
};


template< class T, class U > inline
bool operator==(clone_ptr<T> const& p1, clone_ptr<U> const& p2)
{
    return *p1 == *p2;
}


template< class T, class U > inline
bool operator!=(clone_ptr<T> const& p1, clone_ptr<U> const& p2)
{
    return *p1 != *p2;
}


template< class T, class U > inline
bool operator<(clone_ptr<T> const& p1, clone_ptr<U> const& p2)
{
    return *p1 < *p2;
}


template< class T > inline
void swap(clone_ptr<T>& p1, clone_ptr<T>& p2)
{
    p1.swap(p2);
}


} // namespace pstade


#endif
