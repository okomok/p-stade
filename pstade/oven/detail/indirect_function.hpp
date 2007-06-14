#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INDIRECT_FUNCTION_HPP
#define PSTADE_OVEN_INDIRECT_FUNCTION_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/deferred.hpp>
#include <pstade/indirect.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Indirectable >
struct indirect_function_base :
    boost::remove_reference<
        typename boost::result_of<op_indirect(Indirectable const&)>::type
    >
{ };


template< class Indirectable >
struct indirect_function :
    callable<
        indirect_function<Indirectable>,
        typename boost::result_of<PSTADE_DEFERRED(typename indirect_function_base<Indirectable>::type)()>::type
    >
{
    typedef typename indirect_function_base<Indirectable>::type base_type;

    template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
    struct apply
    { }; // complete for SFINAE.

    // 0ary
    template< class Result >
    Result call() const
    {
        return (*m_ind)();
    }

    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/detail/indirect_function.hpp>))
    #include BOOST_PP_ITERATE()

    explicit indirect_function()
    { }

    explicit indirect_function(Indirectable ind) :
        m_ind(ind)
    { }

    typename boost::result_of<op_indirect(Indirectable const&)>::type
    base() const
    {
        return *m_ind;
    }

private:
    Indirectable m_ind;
};


} } } // namespace pstade::oven::detail


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::oven::detail::indirect_function, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<PSTADE_DEFERRED(base_type)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return (*m_ind)(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
