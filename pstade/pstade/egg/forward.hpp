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


#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/plain.hpp>
#include "./detail/bytag_at.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    // forward
    //

    template<class Bytag, class Lvalue>
    struct result_of_forward;

    template<class Lvalue>
    struct result_of_forward<by_perfect, Lvalue>
    {
        typedef Lvalue& type;
    };

    template<class Lvalue>
    struct result_of_forward<by_ref, Lvalue>
    {
        typedef Lvalue& type;
    };

    template<class Lvalue>
    struct result_of_forward<by_cref, Lvalue const>
    {
        typedef Lvalue const& type;
    };

    // For movable types, you can't add const-qualifier.
    template<class Lvalue>
    struct result_of_forward<by_value, Lvalue>
    {
        BOOST_MPL_ASSERT((is_plain<Lvalue>));
        typedef Lvalue type;
    };


PSTADE_ADL_BARRIER(forward) { // for C++0x

    template<class Bytag, class Lvalue>
    typename result_of_forward<Bytag, Lvalue>::type
    forward(Lvalue& v)
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
    forwarding(Lvalue& a)
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


#endif
