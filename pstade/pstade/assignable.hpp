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
// T:CopyConstructible implies T:Clonable for any type T.
// A reference type is not Clonable.


#include <algorithm> // swap
#include <boost/mpl/assert.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <pstade/overload.hpp>
#include <pstade/radish/output_streamable.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade {


template< class Clonable >
struct assignable;


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


    template< class Clonable >
    struct super_
    {
        BOOST_MPL_ASSERT_NOT((boost::is_reference<Clonable>));

        typedef
            radish::output_streamable< assignable<Clonable>,
            radish::pointable< assignable<Clonable>, Clonable,
            radish::swappable< assignable<Clonable>,
            boost::totally_ordered< assignable<Clonable>
            > > > >
        type;
    };


} // namespace assignable_detail


template< class Clonable >
struct assignable :
    assignable_detail::super_<Clonable>::type
{
private:
    typedef assignable self_t;

public:
    explicit assignable() :
        m_ptr(assignable_detail::new_clone(Clonable()))
    { }

    explicit assignable(Clonable const& x) :
        m_ptr(assignable_detail::new_clone(x))
    { }

    assignable(self_t const& other) :
        m_ptr(assignable_detail::new_clone(*other))
    { }

    self_t& operator=(self_t const& other)
    {
        self_t(other).swap(*this);
        return *this;
    }

    ~assignable()
    {
        assignable_detail::delete_clone(m_ptr);
    }

// totally_ordered
    bool operator< (self_t const& other) const
    {
        return *m_ptr < *other;
    }

    bool operator==(self_t const& other) const
    {
        return *m_ptr == *other;
    }

// pointable
    Clonable *operator->() const
    {
        return m_ptr;
    }

// swappable
    void swap(self_t& other)
    {
        std::swap(m_ptr, other.m_ptr);
    }

private:
    Clonable *m_ptr;

friend class radish::access;
    template< class OStream >
    void pstade_radish_output(OStream& os) const
    {
        os << *m_ptr;
    }
};


template< class Clonable > inline
assignable<Clonable> const
make_assignable(Clonable const& x)
{
    return assignable<Clonable>(x);
}


} // namespace pstade


#endif
