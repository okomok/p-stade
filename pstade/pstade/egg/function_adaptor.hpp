#ifndef PSTADE_EGG_FUNCTION_ADAPTOR_HPP
#define PSTADE_EGG_FUNCTION_ADAPTOR_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/singleton.hpp>
#include "./function.hpp"


#define PSTADE_EGG_FUNCTION_ADAPTOR(Object, BabyTemplate) \
    PSTADE_EGG_FUNCTION_ADAPTOR_aux(Object, BabyTemplate, BOOST_PP_CAT(op_, Object)) \
/**/


    #define PSTADE_EGG_FUNCTION_ADAPTOR_aux(Object, BabyTemplate, Type) \
        struct Type \
        { \
            template< class Signature > \
            struct result; \
            \
            template< class _, class Function > \
            struct result<_(Function)> \
            { \
                typedef typename pstade::pass_by_value<Function>::type fun_t; \
                typedef pstade::egg::function< BabyTemplate<fun_t> > type; \
            }; \
            \
            template< class Function > \
            typename result<int(Function)>::type operator()(Function fun) const \
            { \
                return typename result<int(Function)>::type(fun); \
            } \
        }; \
        \
        PSTADE_SINGLETON_CONST(Object, Type) \
    /**/


#endif
