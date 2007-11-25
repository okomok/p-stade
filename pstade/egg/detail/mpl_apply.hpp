#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_MPL_APPLY_HPP
#define PSTADE_EGG_DETAIL_MPL_APPLY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes nullary and large arity well-formed.


#include <boost/mpl/always.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./nullary_meta.hpp"


namespace pstade { namespace egg { namespace detail {


// 0ary
    template<class F>
    struct mpl_apply0
    {
        // returns void by default, following result_of way.
        typedef void type;
    };

    template<class F>
    struct mpl_apply0< nullary_meta<F> > :
        boost::mpl::apply0<F>
    { };

    template<class U>
    struct mpl_apply0< boost::mpl::always<U> >
    {
        typedef U type;
    };


// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/mpl_apply.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


#if n <= BOOST_MPL_LIMIT_METAFUNCTION_ARITY

    template<class F, BOOST_PP_ENUM_PARAMS(n, class T)>
    struct BOOST_PP_CAT(mpl_apply, n) :
        boost::mpl::BOOST_PP_CAT(apply, n)<F, BOOST_PP_ENUM_PARAMS(n, T)>
    { };

    template<class F, BOOST_PP_ENUM_PARAMS(n, class T)>
    struct BOOST_PP_CAT(mpl_apply, n)< nullary_meta<F>, BOOST_PP_ENUM_PARAMS(n, T)> :
        boost::mpl::BOOST_PP_CAT(apply, n)<F, BOOST_PP_ENUM_PARAMS(n, T)>
    { };

#else

    template<class F, BOOST_PP_ENUM_PARAMS(n, class T)>
    struct BOOST_PP_CAT(mpl_apply, n);

#endif

    // This is "optimization". Also, only always<> can work in large arity.
    template<class U, BOOST_PP_ENUM_PARAMS(n, class T)>
    struct BOOST_PP_CAT(mpl_apply, n)<boost::mpl::always<U>, BOOST_PP_ENUM_PARAMS(n, T)>
    {
        typedef U type;
    };


#undef n
#endif
