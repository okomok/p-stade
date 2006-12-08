#ifndef PSTADE_FUNCTION_ADAPTOR_HPP
#define PSTADE_FUNCTION_ADAPTOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/singleton.hpp>


#define PSTADE_FUNCTION_ADAPTOR(Object, Template) \
    PSTADE_FUNCTION_ADAPTOR_aux(Object, Template, BOOST_PP_CAT(op_, Object)) \
/**/


    #define PSTADE_FUNCTION_ADAPTOR_aux(Object, Template, Type) \
        struct Type : \
            pstade::lambda_sig \
        { \
            template< class Signature > \
            struct result; \
            \
            template< class Self, class Function > \
            struct result<Self(Function)> \
            { \
                typedef Template<typename pstade::pass_by_value<Function>::type> type; \
            }; \
            \
            template< class Function > \
            typename result<Type(Function)>::type operator()(Function fun) const \
            { \
                return typename result<Type(Function)>::type(fun); \
            } \
        }; \
        \
        PSTADE_SINGLETON_CONST(Object, Type) \
    /**/


#endif
