#ifndef PSTADE_EGG_FORWARD_HPP
#define PSTADE_EGG_FORWARD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <pstade/adl_barrier.hpp>
#include "./detail/bytag_at.hpp"
#include "./detail/result_of_forward.hpp"


namespace pstade { namespace egg {


    // forward
    //

PSTADE_ADL_BARRIER(forward) { // for C++0x
    template<class Bytag, class Lvalue> inline
    typename result_of_forward<Bytag, Lvalue>::type
    forward(Lvalue &v)
    {
        return v;
    }
}


    // forwarding
    //

    template<class Strategy, int Arity, int Index, class Lvalue>
    struct result_of_forwarding :
        result_of_forward<
            typename detail::bytag_at<Strategy, Arity, Index>::type,
            Lvalue
        >
    { };

    template<class Strategy, int Arity, int Index, class Lvalue> inline
    typename result_of_forwarding<Strategy, Arity, Index, Lvalue>::type
    forwarding(Lvalue &a)
    {
        return a;
    }


#define PSTADE_EGG_FORWARDING_META_ARGS(Arity, Var, Stg) \
    BOOST_PP_ENUM(Arity, PSTADE_EGG_FORWARDING_META_ARGS_op, (3, (Stg, Arity, Var))) \
/**/

    #define PSTADE_EGG_FORWARDING_META_ARGS_op(Z, I, S_A_V) \
        typename pstade::egg::result_of_forwarding<BOOST_PP_ARRAY_ELEM(0, S_A_V), BOOST_PP_ARRAY_ELEM(1, S_A_V), I, BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(2, S_A_V), I)>::type \
    /**/

#define PSTADE_EGG_FORWARDING_ARGS(Arity, Var, Stg) \
    BOOST_PP_ENUM(Arity, PSTADE_EGG_FORWARDING_ARGS_op, (3, (Stg, Arity, Var))) \
/**/

    #define PSTADE_EGG_FORWARDING_ARGS_op(Z, I, S_A_V) \
        pstade::egg::forwarding<BOOST_PP_ARRAY_ELEM(0, S_A_V), BOOST_PP_ARRAY_ELEM(1, S_A_V), I>( BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(2, S_A_V), I) ) \
    /**/


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
