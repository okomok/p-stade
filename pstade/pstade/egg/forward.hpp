#ifndef PSTADE_EGG_FORWARD_HPP
#define PSTADE_EGG_FORWARD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// We can't use this in function<>::operator().
// Otherwise, it introduces the forwarding problem into little functions.


#include <boost/mpl/eval_if.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include "./detail/bytag_at.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    namespace forward_detail {


        template<class Lvalue, class By>
        struct pass
        {
            typedef Lvalue& type;
        };

        // For movable types, you can't add const-qualifier.
        template<class Lvalue>
        struct pass<Lvalue, by_value> :
            boost::remove_cv<Lvalue>
        { };


    } // forward_detail


    template<class Strategy, int N, class Lvalue>
    struct result_of_forward :
        forward_detail::pass<
            Lvalue, typename detail::bytag_at<Strategy, N>::type
        >
    { };


PSTADE_ADL_BARRIER(forward) { // for C++0x

    template<class Strategy, int N, class Lvalue> inline
    typename result_of_forward<Strategy, N, Lvalue>::type
    forward(Lvalue& a)
    {
        return a;
    }

}


    #define PSTADE_EGG_FORWARD_ENUM_META_ARGS(N, A, Stg) \
        BOOST_PP_ENUM(N, PSTADE_EGG_FORWARD_ENUM_META_ARGS_op, (2, (Stg, A))) \
    /**/

        #define PSTADE_EGG_FORWARD_ENUM_META_ARGS_op(Z, N, Stg_A) \
            typename pstade::egg::result_of_forward<BOOST_PP_ARRAY_ELEM(0, Stg_A), N, BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(1, Stg_A), N)>::type \
        /**/


    #define PSTADE_EGG_FORWARD_ENUM_ARGS(N, A, Stg) \
        BOOST_PP_ENUM(N, PSTADE_EGG_FORWARD_ENUM_ARGS_op, (2, (Stg, A))) \
    /**/

        #define PSTADE_EGG_FORWARD_ENUM_ARGS_op(Z, N, Stg_A) \
            pstade::egg::forward<BOOST_PP_ARRAY_ELEM(0, Stg_A), N>( BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(1, Stg_A), N) ) \
        /**/


} } // namespace pstade::egg


#endif
