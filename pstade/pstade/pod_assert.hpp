#ifndef PSTADE_POD_ASSERT_HPP
#define PSTADE_POD_ASSERT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/preprocessor/cat.hpp>
#include <pstade/ignore_unused.hpp>
#include <pstade/pp_line.hpp>
#include <pstade/unevaluated.hpp>


#define PSTADE_POD_ASSERT(T) \
    static std::size_t const PSTADE_IGNORE_UNUSED \
        BOOST_PP_CAT(pod_assertion_in_line_, PSTADE_PP_LINE()) \
            = sizeof( pstade::pod_assert_detail::arg((void (*) T)0, 1) ); \
    PSTADE_POD_ASSERT_pray(T) \
/**/


#define PSTADE_POD_ASSERT_pray(T) \
    struct BOOST_PP_CAT(POD_ASSERTION_FAILURE_in_line_, PSTADE_PP_LINE()) \
    { \
        void failed() \
        { \
            pstade::pod_assert_detail::must_be_pod(pstade::pod_assert_detail::make<void T>::value()); \
        } \
    } \
/**/


namespace pstade {


    // In fact, less strict
    template<class T>
    union POD_ASSERTION_FAILURE
    {
        T failed;
    };


    namespace pod_assert_detail {


        template<class T>
        struct assertion
        {
            static POD_ASSERTION_FAILURE<T> x;
            typedef int type;
        };

        template<class T> inline
        int arg(void (*)(T), typename assertion<T>::type);


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


    } // namespace pod_assert_detail


} // namespace pstade::pod_assert_detail


#endif
