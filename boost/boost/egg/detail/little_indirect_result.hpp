#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_INDIRECT_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_INDIRECT_RESULT_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // BOOST_EGG_MAX_LINEAR_ARITY
#include "../forward.hpp"
#include "./functional1.hpp" // dereference


namespace pstade { namespace egg { namespace detail {


    template<class Ptr>
    struct indirecting_fun :
        boost::remove_reference<
            typename result_of<T_dereference(Ptr const&)>::type
        >
    { };


    template<class Ptr, class Strategy>
    struct little_indirect_result
    {
        Ptr m_ptr;

        typedef typename indirecting_fun<Ptr>::type base_type;

        typename result_of<T_dereference(Ptr const&)>::type
        base() const
        {
            return *m_ptr;
        }

    // 0ary
        typedef typename
            result_of<base_type()>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return (*m_ptr)();
        }

    // 1ary-
        template<class Myself, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/little_indirect_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<base_type(BOOST_EGG_FORWARDING_ENUM_META_ARGS(n, A, Strategy const))>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return (*m_ptr)(BOOST_EGG_FORWARDING_ENUM_ARGS(n, a, Strategy const));
    }


#undef n
#endif
