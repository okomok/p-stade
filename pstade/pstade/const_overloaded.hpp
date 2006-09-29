#ifndef PSTADE_CONST_OVERLOADED_HPP
#define PSTADE_CONST_OVERLOADED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/2dc6189c2eec0fd5/
// This class doesn't always do the same thing as 'disable_if<is_const<T> >'.
// This is nothing but a workaround for bugs. So, it has this name.


#include <boost/config.hpp> // BOOST_MSVC, BOOST_NO_SFINAE
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp> // disable_if


// Workaround:
// Turn it off; VC++ has problems around array types
// under weird situation even with Boost v1.34 or later.
#if defined(BOOST_MSVC) || defined(BOOST_NO_SFINAE)
    #define PSTADE_CONST_OVERLOADED_NOT_REQUIRED
#endif


namespace pstade {


namespace const_overloaded_detail {


template<
    class T0, class T1, class T2, class T3, class T4,
    class T5, class T6, class T7, class T8, class T9
>
struct or10 :
    boost::mpl::or_<
        boost::mpl::or_<T0, T1, T2, T3, T4>,
        boost::mpl::or_<T5, T6, T7, T8, T9>
    >
{ };


template<
    class A0, class A1, class A2, class A3, class A4,
    class A5, class A6, class A7, class A8, class A9
>
struct contains_const :
    or10<
        boost::is_const<A0>,
        boost::is_const<A1>,
        boost::is_const<A2>,
        boost::is_const<A3>,
        boost::is_const<A4>,
        boost::is_const<A5>,
        boost::is_const<A6>,
        boost::is_const<A7>,
        boost::is_const<A8>,
        boost::is_const<A9>
    >
{ };


} // namespace const_overloaded_detail


#if !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


    template<
        class A0,        class A1 = void, class A2 = void, class A3 = void, class A4 = void,
        class A5 = void, class A6 = void, class A7 = void, class A8 = void, class A9 = void
    >
    struct const_overloaded :
        boost::disable_if<
            const_overloaded_detail::contains_const<
                A0, A1, A2, A3, A4,
                A5, A6, A7, A8, A9
            >,
            void *
        >
    { };


#else


    template<
        class A0,        class A1 = void, class A2 = void, class A3 = void, class A4 = void,
        class A5 = void, class A6 = void, class A7 = void, class A8 = void, class A9 = void
    >
    struct const_overloaded :
        boost::mpl::identity<void *>
    { };


#endif // !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


} // namespace pstade


#endif
