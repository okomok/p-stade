#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BY_CREF_HPP
#define BOOST_EGG_BY_CREF_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/mpl/always.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/deduced_const.hpp>
#include <boost/egg/detail/pp_enum_template_params.hpp>
#include <boost/egg/detail/result_of_forward.hpp>
#include <boost/egg/function_extension.hpp>


namespace boost { namespace egg {


    struct by_cref :
        mpl::always<by_cref>
    { };


    template<class Little>
    struct function<Little, by_cref>
    {
        #include BOOST_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const &little() const
        {
            return m_little;
        }

    #define BOOST_EGG_const(Z, N, A) BOOST_EGG_DEDUCED_CONST(BOOST_PP_CAT(A, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/by_cref.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_const
    };


    template<class Lvalue>
    struct result_of_forward<by_cref, Lvalue const>
    {
        typedef Lvalue const &type;
    };

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
    template<class T, std::size_t N>
    struct result_of_forward<by_cref, T const[N]>
    {
        typedef T const (&type)[N];
    };
#endif


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    typename apply_little<Little const BOOST_PP_ENUM_TRAILING(n, BOOST_EGG_const, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const &a)) const
    {
        return call_little(m_little BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
