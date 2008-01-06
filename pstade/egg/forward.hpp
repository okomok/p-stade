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


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template<class A, class Strategy>
    struct result_of_forward
    {
        typedef A& type;
    };

    // must return non-const rvalue for movable types.
    template<class A>
    struct result_of_forward<A, by_value> :
        boost::remove_cv<A>
    { };


PSTADE_ADL_BARRIER(forward) { // for C++0x

    template<class Strategy, class A> inline
    typename result_of_forward<A, Strategy>::type
    forward(A& a)
    {
        return a;
    }

}


    #define PSTADE_EGG_FORWARD_ENUM_META_ARGS(N, A, Stg) \
        BOOST_PP_ENUM(N, PSTADE_EGG_FORWARD_ENUM_META_ARGS_op, (2, (A, Stg))) \
    /**/

        #define PSTADE_EGG_FORWARD_ENUM_META_ARGS_op(Z, N, A_Stg) \
            typename pstade::egg::result_of_forward<BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, A_Stg), N), BOOST_PP_ARRAY_ELEM(1, A_Stg)>::type \
        /**/


    #define PSTADE_EGG_FORWARD_ENUM_ARGS(N, A, Stg) \
        BOOST_PP_ENUM(N, PSTADE_EGG_FORWARD_ENUM_ARGS_op, (2, (A, Stg))) \
    /**/

        #define PSTADE_EGG_FORWARD_ENUM_ARGS_op(Z, N, A_Stg) \
            pstade::egg::forward<BOOST_PP_ARRAY_ELEM(1, A_Stg)>( BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, A_Stg), N) ) \
        /**/


} } // namespace pstade::egg


#endif
