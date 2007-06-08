#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_CALLABLE_BY_VALUE_HPP
#define PSTADE_CALLABLE_BY_VALUE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A "movable type" like 'auto_ptr' must be called by value.
// "./callable.hpp" makes rvalue unmovable.


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp> // inclusion guaranteed
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


PSTADE_ADL_BARRIER(callable_by_value) {


    template<class Derived, class NullaryResult = boost::use_default>
    struct callable_by_value :
        provide_sig
    {
        template<class FunCall>
        struct result
        { };

        // 0ary
        typedef typename
            if_use_default< NullaryResult, callable_error_non_nullary<Derived> >::type
        nullary_result_type;

        nullary_result_type
        operator()() const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                nullary_result_type
            >();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/callable_by_value.hpp>))
        #include BOOST_PP_ITERATE()

    private:
        Derived const& derived() const
        {
            return static_cast<Derived const&>(*this);
        }
    };


} // ADL barrier


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        Derived::BOOST_NESTED_TEMPLATE apply<
            Derived,
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename pass_by_value<A, >::type)
        >
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        return derived().BOOST_NESTED_TEMPLATE call<
            typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type            
        >(BOOST_PP_ENUM_PARAMS(n, a));
    }
    

#undef n
#endif
