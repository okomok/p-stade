#ifndef BOOST_EGG_RESISTER_NULLARY_RESULT_HPP
#define BOOST_EGG_RESISTER_NULLARY_RESULT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_result_of_fwd.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/detail/pp_seq_enum_args.hpp>
#include <boost/egg/detail/pp_seq_enum_params.hpp>
#include <boost/egg/detail/pp_to_template_param_seq.hpp>


#define BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TYPE(X) \
    namespace boost { \
    \
        template< > \
        struct result_of<X(BOOST_EGG_VOID_IN_FUN_SPEC)> \
        { \
            typedef X::nullary_result_type type; \
        }; \
    \
        template< > \
        struct result_of<X const(BOOST_EGG_VOID_IN_FUN_SPEC)> \
        { \
            typedef X::nullary_result_type type; \
        }; \
    \
    } \
/**/


#define BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(X, Seq) \
    BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE_aux(X, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Seq)) \
/**/

#define BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE_aux(X, Seq) \
    namespace boost { \
    \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Seq, T)> \
        struct result_of<X<BOOST_EGG_PP_SEQ_ENUM_ARGS(Seq, T)>(BOOST_EGG_VOID_IN_FUN_SPEC)> \
        { \
            typedef typename X<BOOST_EGG_PP_SEQ_ENUM_ARGS(Seq, T)>::nullary_result_type type; \
        }; \
    \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Seq, T)> \
        struct result_of<X<BOOST_EGG_PP_SEQ_ENUM_ARGS(Seq, T)> const(BOOST_EGG_VOID_IN_FUN_SPEC)> \
        { \
            typedef typename X<BOOST_EGG_PP_SEQ_ENUM_ARGS(Seq, T)>::nullary_result_type type; \
        }; \
    \
    } \
/**/


#include <boost/egg/detail/suffix.hpp>
#endif
