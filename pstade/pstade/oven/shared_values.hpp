#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_SHARED_VALUES_HPP
#define PSTADE_OVEN_SHARED_VALUES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/egg/bll/sig_base.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./shared.hpp"


#if !defined(PSTADE_OVEN_SHARED_VALUES_MAX_ARITY)
    #define PSTADE_OVEN_SHARED_VALUES_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


template< class Value = boost::use_default >
struct X_shared_values
{
    template< class A >
    struct value_ :
        eval_if_use_default< Value, pass_by_value<A> >
    { };

// 1ary-
    template< class FunCall >
    struct result;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_SHARED_VALUES_MAX_ARITY, <pstade/oven/shared_values.hpp>))
    #include BOOST_PP_ITERATE()

    template<class FunArgs>
    struct sig :
        egg::bll_sig_base<FunArgs>
    { };
};


typedef X_shared_values<> T_shared_values;
PSTADE_POD_CONSTANT((T_shared_values), shared_values) = {};


template< class Value, std::size_t N >
struct result_of_shared_values :
    result_of<
        T_shared(boost::array<Value, N> *)
    >
{ };


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n) :
        result_of<
            T_shared(boost::array<typename value_<A0>::type, n> *)
        >
    { };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const
    {
        typedef boost::array<typename value_<A0 const&>::type, n> rng_t;
        rng_t r = { { BOOST_PP_ENUM_PARAMS(n, a) } };
        return shared(new rng_t(r));
    }


#undef n
#endif
