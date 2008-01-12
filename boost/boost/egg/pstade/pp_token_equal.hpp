#ifndef PSTADE_PP_TOKEN_EQUAL_HPP
#define PSTADE_PP_TOKEN_EQUAL_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Paul Mensonides 2003
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.


// Difference to BOOST_MPL_PP_TOKEN_EQUAL:
//
// Replaces BOOST_MPL_PP_IS_SEQ with BOOST_PP_IS_UNARY.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


#define PSTADE_PP_TOKEN_EQUAL(a, b) \
    BOOST_PP_IIF( \
        BOOST_PP_BITAND( \
              BOOST_PP_IS_UNARY( BOOST_PP_CAT(PSTADE_PP_TOKEN_EQUAL_, a)((unused)) ) \
            , BOOST_PP_IS_UNARY( BOOST_PP_CAT(PSTADE_PP_TOKEN_EQUAL_, b)((unused)) ) \
            ) \
        , PSTADE_PP_TOKEN_EQUAL_I \
        , 0 BOOST_PP_TUPLE_EAT(2) \
        )(a, b) \
/**/

#define PSTADE_PP_TOKEN_EQUAL_I(a, b) \
    BOOST_PP_COMPL(BOOST_PP_IS_UNARY( \
        PSTADE_PP_TOKEN_EQUAL_ ## a( \
            PSTADE_PP_TOKEN_EQUAL_ ## b \
            )((unused)) \
        )) \
/**/


#endif
