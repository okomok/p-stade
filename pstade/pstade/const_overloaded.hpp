#ifndef PSTADE_CONST_OVERLOADED_HPP
#define PSTADE_CONST_OVERLOADED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
// http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/2dc6189c2eec0fd5/


#include <boost/config.hpp> // BOOST_MSVC, BOOST_NO_SFINAE
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp> // disable_if, lazy_disable_if


// Workaround:
// Turn it off, VC++ has problems around array types
// under weird situation even with Boost v1.34 or later.
#if defined(BOOST_MSVC) || defined(BOOST_NO_SFINAE)
    #define PSTADE_CONST_OVERLOADED_NOT_REQUIRED
#endif


namespace pstade {


#if !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


    template<
        class Result,
        class T0 = void, class T1 = void, class T2 = void, class T3 = void, class T4 = void,
        class T5 = void, class T6 = void, class T7 = void, class T8 = void, class T9 = void
    >
    struct const_overloaded :
        boost::disable_if<
            boost::mpl::or_<
                boost::mpl::or_<
                    boost::is_const<T0>,
                    boost::is_const<T1>,
                    boost::is_const<T2>,
                    boost::is_const<T3>,
                    boost::is_const<T4>
                >,
                boost::mpl::or_<
                    boost::is_const<T5>,
                    boost::is_const<T6>,
                    boost::is_const<T7>,
                    boost::is_const<T8>,
                    boost::is_const<T9>
                >
            >,
            Result
        >
    { };


    template<
        class Result,
        class T0 = void, class T1 = void, class T2 = void, class T3 = void, class T4 = void,
        class T5 = void, class T6 = void, class T7 = void, class T8 = void, class T9 = void
    >
    struct const_overloaded_eval :
        boost::lazy_disable_if<
            boost::mpl::or_<
                boost::mpl::or_<
                    boost::is_const<T0>,
                    boost::is_const<T1>,
                    boost::is_const<T2>,
                    boost::is_const<T3>,
                    boost::is_const<T4>
                >,
                boost::mpl::or_<
                    boost::is_const<T5>,
                    boost::is_const<T6>,
                    boost::is_const<T7>,
                    boost::is_const<T8>,
                    boost::is_const<T9>
                >
            >,
            Result
        >
    { };


#else


    template<
        class Result,
        class T0 = void, class T1 = void, class T2 = void, class T3 = void, class T4 = void,
        class T5 = void, class T6 = void, class T7 = void, class T8 = void, class T9 = void
    >
    struct const_overloaded :
        boost::mpl::identity<Result>
    { };


    template<
        class Result,
        class T0 = void, class T1 = void, class T2 = void, class T3 = void, class T4 = void,
        class T5 = void, class T6 = void, class T7 = void, class T8 = void, class T9 = void
    >
    struct const_overloaded_eval :
        Result
    { };


#endif // !defined(PSTADE_CONST_OVERLOADED_NOT_REQUIRED)


} // namespace pstade


#endif
