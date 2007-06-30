#ifndef PSTADE_DEFERRED_HPP
#define PSTADE_DEFERRED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Deprecated; use "./result_of.hpp"


// What:
//
// Works around a bug that 'boost::result_of<const function-pointer(..)>' doesn't work.
// If a function object 'F' may be a const pointer, use 'PSTADE_DEFERRED(F)'.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/version.hpp>


#if 1
    #define PSTADE_DEFERRED typename PSTADE_DEFERRED_TYPE
    #define PSTADE_DEFERRED_TYPE(F) pstade::deferred_detail::aux< F >::type
#else
    // Someday...
    #define PSTADE_DEFERRED(F) F
    #define PSTADE_DEFERRED_TYPE(F) F
#endif


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) && (BOOST_VERSION < 103500)
    #include <pstade/has_xxx.hpp>
    #define PSTADE_DEFERRED_MSVC_WORKAROUND
#endif


namespace pstade { namespace deferred_detail {


    template<class T>
    struct is_pointer :
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
        boost::is_pointer<typename boost::remove_cv<T>::type>
#else
        boost::is_pointer<T>
#endif
    { };



#if defined(PSTADE_DEFERRED_MSVC_WORKAROUND)

    PSTADE_HAS_TYPE(anything)

    template<class F>
    struct force_instantiate
    {
        static bool const b = has_anything<F>::value;
        typedef F type;
    };

    template<class F>
    struct msvc_identity :
        boost::mpl::eval_if< boost::is_class<F>,
            force_instantiate<F>,
            boost::mpl::identity<F>
        >
    { };

#endif


    template<class F>
    struct aux :
        boost::mpl::eval_if<
            boost::mpl::or_< is_pointer<F>, boost::is_member_function_pointer<F> >,
            boost::remove_cv<F>,
#if defined(PSTADE_DEFERRED_MSVC_WORKAROUND)
            msvc_identity<F>
#else
            boost::mpl::identity<F>
#endif
        >
    { };


} } // namespace pstade::deferred_detail


#endif
