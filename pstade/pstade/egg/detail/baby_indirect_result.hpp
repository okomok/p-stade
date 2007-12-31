#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_INDIRECT_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_INDIRECT_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../baby_apply.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../deref.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Dereferenceable>
    struct indirecting_fun :
        boost::remove_reference<
            typename result_of_deref<Dereferenceable const>::type
        >
    { };


    template<class Dereferenceable>
    struct baby_indirect_result
    {
        Dereferenceable m_drf;

        typedef typename indirecting_fun<Dereferenceable>::type base_type;

        typename result_of_deref<Dereferenceable const>::type
        base() const
        {
            return *m_drf;
        }

    // 0ary
        typedef typename
            result_of<base_type()>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return (*m_drf)();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct PSTADE_EGG_BABY_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/baby_indirect_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<base_type(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return (*m_drf)(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
