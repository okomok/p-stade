#ifndef PSTADE_UNUSED_TO_COPY_HPP
#define PSTADE_UNUSED_TO_COPY_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A unary template constructor can win the overloading race
// against copy-constructor. So disable it.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/eca7b43d751008cd/


// Note:
//
// Use this even if the parameter is const-qualified,
// which works around 'PSTADE_implicitly_defined_copy_is_broken'.
// 'boost::base_from_member' also seems broken by this VC bug.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
    // 12.8/8 says "the copy constructor for *the class* is used".
    // But VC8's implicitly-defined copy-constructor/copy-assignment-operator
    // passes derived object to base constructor without casting to base type.
    // Then the template constructor of base might be chosen.
    // The base can be constructed from the derived? It seems to be impossible.
    #define PSTADE_implicitly_defined_copy_is_broken
#endif


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace pstade {


template< class T, class A >
struct unused_to_copy :
    // give way to implicitly-declared copy-constructor.
    boost::disable_if<
#if !defined(PSTADE_implicitly_defined_copy_is_broken)
        boost::is_same<T, A>,
#else
        boost::mpl::or_<
            boost::is_same<T, A>,
            boost::is_base_of<T, A>
        >,
#endif
        void *
    >
{ };


template< class T, class A >
struct unused_to_copy_assign :
    boost::disable_if<
#if !defined(PSTADE_implicitly_defined_copy_is_broken)
        boost::is_same<T, A>,
#else
        boost::mpl::or_<
            boost::is_same<T, A>,
            boost::is_base_of<T, A>
        >,
#endif
        T&
    >
{ };


} // namespace pstade


// If the base class does not use 'unused_to_copy',
// place this in the derived class.
//
#if !defined(PSTADE_implicitly_defined_copy_is_broken)

    #define PSTADE_IMPLICITLY_DEFINED_COPY(T, Base) \
    /**/

#else

    #define PSTADE_IMPLICITLY_DEFINED_COPY(T, Base) \
        T(T const& other) : \
            Base(static_cast<Base const&>(other)) \
        { } \
        \
        T& operator=(T const& other) \
        { \
            Base::operator=(static_cast<Base const&>(other)); \
            return *this; \
        } \
    /**/

#endif


#undef PSTADE_implicitly_defined_copy_is_broken


#endif
