#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BY_PERFECT_HPP
#define BOOST_EGG_BY_PERFECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/detail/bytag_at.hpp>
#include <boost/egg/detail/result_of_forward.hpp>
#include <boost/egg/function_extension.hpp>


namespace boost { namespace egg {


    namespace details {


        // by_perfect(use_default) isn't complete type.

        template<int Arity, int Index>
        struct bytag_at<by_perfect, Arity, Index>
        {
            typedef by_perfect type;
        };

        template<int Arity, int Index>
        struct bytag_at<by_perfect const, Arity, Index>
        {
            typedef by_perfect type;
        };


    } // namespace details


    template<class Little>
    struct function<Little, by_perfect>
    {
        BOOST_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const &little() const
        {
            return m_little;
        }

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_ARITY, <boost/egg/by_perfect.hpp>))
        #include BOOST_PP_ITERATE()
    };


    template<class Lvalue>
    struct result_of_forward<by_perfect, Lvalue>
    {
        typedef Lvalue &type;
    };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(n, const)


#undef  n
#endif
