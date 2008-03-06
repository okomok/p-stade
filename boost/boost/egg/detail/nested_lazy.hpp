#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_NEST_IMPL_HPP
#define BOOST_EGG_DETAIL_NEST_IMPL_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_NEST_MAX_LEVEL
#include <boost/egg/lazy.hpp>
#include <boost/egg/preprocessor/cat3.hpp>


namespace boost { namespace egg { namespace details {


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_NEST_MAX_LEVEL, <boost/egg/detail/nest_impl.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    namespace BOOST_EGG_PP_CAT3(nest_impl, n, _detail) {
#if n == 1
        template<class Bind>
        struct with_
        {
            typedef Bind type;
        };
#else
        template<class Bind>
        struct with_ :
            result_of_lazy<Bind, typename BOOST_EGG_PP_CAT3(nest_impl, BOOST_PP_DEC(n), _detail)::with_<Bind>::type>
        { };
#endif
    }

    template<class Bind>
    struct BOOST_PP_CAT(X_nest_impl, n) :
        X_lazy<
            typename BOOST_EGG_PP_CAT3(nest_impl, n, _detail)::with_<Bind>::type
        >
    { };


#undef  n
#endif
