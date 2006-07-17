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
#include <boost/operators.hpp> // totally_ordered
#include <boost/ptr_container/clone_allocator.hpp>
#include <pstade/overload.hpp>
#include <pstade/radish/outputable.hpp>
#include <pstade/radish/pointer.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade {


namespace assignable_detail {


    template< class T > inline
    T *pstade_assignable_new_clone(T const& x, overload<>)
    {
        return boost::heap_clone_allocator::allocate_clone(x);
    }


    template< class T > inline
    void pstade_assignable_delete_clone(T *ptr, overload<>)
    {
        return boost::heap_clone_allocator::deallocate_clone(ptr);
    }


    template< class T > inline
    T *new_clone(T const& x)
    {
        return pstade_assignable_new_clone(x, overload<>());
    }


    template< class T > inline
    void delete_clone(T *ptr)
    {
        return pstade_assignable_delete_clone(ptr, overload<>());
    }


} // namespace assignable_detail


template< class Clonable >
struct assignable :
    radish::outputable< assignable<Clonable> >,
    radish::pointer< assignable<Clonable>, Clonable >,
    radish::swappable< assignable<Clonable> >,
    boost::totally_ordered< assignable<Clonable> >
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

    assignable& operator=(assignable const& other)
    {
        assignable(other).swap(*this);
        return *this;
    }

    // radish
    //
    template< class OStream >
    void pstade_radish_output(OStream& os) const
    {
        os << *m_ptr;
    }

    Clonable *pstade_radish_pointer() const
    {
        return m_ptr;
    }

    void pstade_radish_swap(assignable& other)
    {
        std::swap(m_ptr, other.m_ptr);
    }

    // totally_ordered
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
assignable<Clonable> make_assignable(Clonable const& x)
{
    return assignable<Clonable>(x);
}


} // namespace pstade


#endif
