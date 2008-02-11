#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_BLL_POLY_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_BLL_POLY_RESULT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include "../apply_decl.hpp"
#include "../bll/config.hpp" // PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY
#include "../by_ref.hpp"


template<class Bindable>
struct ERROR_PSTADE_EGG_BLL_POLY_NON_NULLARY;


namespace pstade { namespace egg { namespace detail {


    template<class Bindable, class IsNullary>
    struct little_bll_poly_result
    {
        Bindable m_base;

        Bindable const &base() const
        {
            return m_base;
        }

    // 0ary
        struct result0 :
            Bindable::template sig<
                boost::tuples::tuple<Bindable>
            >
        { };

        typedef typename
            boost::mpl::eval_if< IsNullary,
                result0,
                boost::mpl::identity< ERROR_PSTADE_EGG_BLL_POLY_NON_NULLARY<Bindable> >
            >::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            return m_base();
        }

    // 1ary-
        template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, <pstade/egg/detail/little_bll_poly_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        Bindable::template sig<
            boost::tuples::tuple<
                Bindable,
                BOOST_PP_ENUM_PARAMS(n, A)
            >
        >
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return m_base(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
