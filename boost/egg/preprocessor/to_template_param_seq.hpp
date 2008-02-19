#ifndef BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ_HPP
#define BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/egg/preprocessor/is_seq.hpp>


// Same as 'BOOST_TYPEOF_TOSEQ' at <boost/typeof/template_encoding.hpp>
// (class)(int) -> as is; 2 -> (class)(class)
#define BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount) \
    BOOST_PP_IIF( BOOST_EGG_PP_IS_SEQ(ParamSeqOrCount), \
        ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_REPEAT \
    )(ParamSeqOrCount, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ_op, ~) \
/**/

    #define BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ_op(Z, N, _) \
        (class) \
    /**/


#endif
