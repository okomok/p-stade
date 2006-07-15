#ifndef PSTADE_ASSIGNABLE_HPP
#define PSTADE_ASSIGNABLE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes a copy-constructible type to be assignable.
// Note that 'default_constructible' is 'boost::optional',
// which requires assignability. Thus,
// 'boost::optional< assignable<T> > x;' does what you want.


// See: Clonable
//
// http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept


#include <algorithm> // swap
#include <iosfwd> // basic_ostream
#include <boost/operators.hpp> // totally_ordered
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/overload.hpp>


namespace pstade {


namespace assignable_detail {


    template< class T >
    T *pstade_new_clone(T const& x, overload<>)
    {
        return boost::heap_clone_allocator::allocate_clone(x);
    }


    template< class T > inline
    void pstade_delete_clone(T *ptr, overload<>)
    {
        return boost::heap_clone_allocator::deallocate_clone(ptr);
    }


    template< class T > inline
    T *new_clone(T const& x)
    {
        return pstade_new_clone(x, overload<>());
    }


    template< class T > inline
    void delete_clone(T *ptr)
    {
        return pstade_delete_clone(ptr, overload<>());
    }


} // namespace assignable_detail


template< class Clonable >
struct assignable :
    private boost::totally_ordered< assignable<Clonable> >
{
    // structors
    //
    assignable() :
        m_ptr(assignable_detail::new_clone(Clonable()))
    { }

    assignable(assignable const& other) :
        m_ptr(assignable_detail::new_clone(*other))
    { }

    explicit assignable(Clonable const& x) :
        m_ptr(assignable_detail::new_clone(x))
    { }

    ~assignable()
    {
        assignable_detail::delete_clone(m_ptr);
    }

    // modifiers
    //
    assignable& operator=(assignable const& other)
    {
        assignable(other).swap(*this);
        return *this;
    }

    void swap(assignable& other)
    {
        std::swap(m_ptr, other.m_ptr);
    }

    // accessors
    //
    Clonable& operator*() const
    {
        return *m_ptr;
    }

    Clonable *operator->() const
    {
        return m_ptr;
    }

    typedef Clonable element_type; // for 'boost::pointee'

    // relationals
    //
    bool operator< (assignable const& other) const
    {
        return *m_ptr < *other;
    }

    bool operator==(assignable const& other) const
    {
        return *m_ptr == *other;
    }

private:
    Clonable *m_ptr;
};


template< class Clonable > inline
void swap(assignable<Clonable>& a1, assignable<Clonable>& a2)
{
    a1.swap(a2);
}


template< class Clonable > inline
Clonable *get_pointer(assignable<Clonable> const& a)
{
    return boost::addressof(*a);
}


template< class CharT, class Traits, class Clonable >
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, assignable<Clonable> const& a)
{
    os << *a;
    return os;
}


template< class Clonable > inline
assignable<Clonable> make_assignable(Clonable const& x)
{
    return assignable<Clonable>(x);
}


} // namespace pstade


#endif
