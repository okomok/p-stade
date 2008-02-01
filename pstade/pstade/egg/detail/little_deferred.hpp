#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_DEFERRED_HPP
#define PSTADE_EGG_DETAIL_LITTLE_DEFERRED_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "../apply_decl.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Expr>
    struct little_deferred
    {
        template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/egg/detail/little_deferred.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef typename
            boost::mpl::BOOST_PP_CAT(apply, n)<
                Expr, BOOST_PP_ENUM_PARAMS(n, A)
            >::type
        impl_t;

        typedef typename impl_t::result_type type;
    };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename apply<void, BOOST_PP_ENUM_PARAMS(n, A)>::impl_t impl_t;
        return impl_t()(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
