#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INITIAL_VALUES_HPP
#define PSTADE_OVEN_INITIAL_VALUES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Simple version of 'boost::assign::cref_list_of'.
// A1-AN must be convertible to A0.


#include <cstddef> // size_t
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/callable.hpp> // NULLARY_RESULT_OF_TYPE
#include <pstade/constant.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include "./copy_range.hpp"


#if !defined(PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY)
    #define PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY 20
#endif


namespace pstade { namespace oven {


namespace initial_values_detail {


    struct temp0
    {
        template< class To >
        operator To() const
        {
            return To();
        }
    };


    template< class Value, std::size_t N >
    struct temp
    {
        Value m_elems[N];

        template< class To >
        operator To() const
        {
            return oven::copy_range<To>(m_elems);
        }

    // as range
        typedef Value const *iterator;
        typedef iterator     const_iterator;
        typedef std::size_t  size_type;

        iterator begin() const
        {
            return m_elems;
        }

        iterator end() const
        {
            return m_elems + N;
        }

        size_type size() const
        {
            return N;
        }
    };


} // namespace initial_values_detail


struct op_initial_values :
    lambda_sig
{
// 0ary
    typedef
        initial_values_detail::temp0 const
    nullary_result_type;

    nullary_result_type operator()() const
    {
        return nullary_result_type();
    }

// 1ary-
    template< class FunCall >
    struct result;

    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_OVEN_INITIAL_VALUES_MAX_ARITY, <pstade/oven/initial_values.hpp>))
    #include BOOST_PP_ITERATE()
};


PSTADE_CONSTANT(initial_values, (op_initial_values))


} } // namespace pstade::oven


PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE((pstade)(oven)(op_initial_values))


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    struct BOOST_PP_CAT(result, n)
    {
        typedef
            initial_values_detail::temp<
                typename pass_by_value<A0>::type, n
            > const
        type;
    };

public:
    template< class Fun, BOOST_PP_ENUM_PARAMS(n, class A) >
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template< BOOST_PP_ENUM_PARAMS(n, class A) >
    typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const
    {
        typedef typename BOOST_PP_CAT(result, n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)>::type result_t;
        result_t result = { { BOOST_PP_ENUM_PARAMS(n, a) } };
        return result;
    }


#undef n
#endif
