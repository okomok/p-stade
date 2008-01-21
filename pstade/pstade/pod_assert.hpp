#ifndef PSTADE_POD_ASSERT_HPP
#define PSTADE_POD_ASSERT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// clearly imperfect...
// FWIW, msvc is_pod<> doesn't correctly work at all.


#include <boost/preprocessor/cat.hpp>
#include <pstade/pp_line.hpp>
#include <pstade/unevaluated.hpp>


#define PSTADE_POD_ASSERT(T) \
    struct BOOST_PP_CAT(POD_ASSERTION_FAILURE_in_line_, PSTADE_PP_LINE()) \
    { \
        PSTADE_POD_ASSERT_aux(T) \
    } \
/**/


#define PSTADE_POD_ASSERT_OF(T, O) \
    struct BOOST_PP_CAT(POD_ASSERTION_FAILURE_of_, O) \
    { \
        PSTADE_POD_ASSERT_aux(T) \
    } \
/**/


    #define PSTADE_POD_ASSERT_aux(T) \
        void failed() \
        { \
            pstade::pod_assert_detail::must_be_pod(pstade::pod_assert_detail::make<void T>::value()); \
        } \
    /**/


namespace pstade { namespace pod_assert_detail {


    // Some compilers can warn if non-POD passed through ellipsis. 
    inline void must_be_pod(...) { }


    template<class Sig>
    struct make;

    template<class T>
    struct make<void(T)>
    {
        static T value()
        {
            return unevaluated<T>();
        }
    };


} } // namespace pstade::pod_assert_detail


#endif
