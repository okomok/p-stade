#ifndef BOOST_EGG_DETAIL_POD_ASSERT_HPP
#define BOOST_EGG_DETAIL_POD_ASSERT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// clearly imperfect...
// FWIW, msvc is_pod<> doesn't correctly work at all.


#include <boost/preprocessor/cat.hpp>
#include <boost/egg/preprocessor/line.hpp>
#include <boost/egg/detail/fake.hpp>


#define BOOST_EGG_POD_ASSERT(T) \
    struct BOOST_PP_CAT(pod_assertion_in_line_, BOOST_EGG_PP_LINE()) \
    { \
        BOOST_EGG_POD_ASSERT_aux(T) \
    } \
/**/


#define BOOST_EGG_POD_ASSERT_OF(T, O) \
    struct BOOST_PP_CAT(pod_assertion_of_, O) \
    { \
        BOOST_EGG_POD_ASSERT_aux(T) \
    } \
/**/


    #define BOOST_EGG_POD_ASSERT_aux(T) \
        ERROR_BOOST_EGG_POD_ASSERTION_FAILURE failed() \
        { \
            return boost::egg::details::must_be_pod(boost::egg::details::make_pod<void T>::value()); \
        } \
    /**/


struct ERROR_BOOST_EGG_POD_ASSERTION_FAILURE { };


namespace boost { namespace egg { namespace details {


    // Some compilers can warn if non-POD passed through ellipsis. 
    inline ERROR_BOOST_EGG_POD_ASSERTION_FAILURE must_be_pod(...)
    {
        return ERROR_BOOST_EGG_POD_ASSERTION_FAILURE();
    }


    template<class Sig>
    struct make_pod;

    template<class T>
    struct make_pod<void(T)>
    {
        static T value()
        {
            return fake<T>();
        }
    };


} } } // namespace boost::egg::details


#endif
