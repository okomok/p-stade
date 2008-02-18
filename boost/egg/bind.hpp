#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BIND_HPP
#define BOOST_EGG_BIND_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/bind_n.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/config.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/result_of_bind.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace bind_detail {


        template<class NullaryResult>
        struct little
        {
            template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
            struct BOOST_EGG_APPLY_DECL;

        #define PSTADE_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <boost/egg/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity
        };


    } // namespace bind_detail


    template<class NullaryResult = use_default>
    struct X_bind : details::derived_from<
        function<bind_detail::little<NullaryResult>, by_cref> >
    { };

    typedef X_bind<>::base_class T_bind;
    BOOST_EGG_CONST((T_bind), bind) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    struct apply<Me, Base BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)> :
        result_of<BOOST_PP_CAT(X_bind, n)<NullaryResult>(Base & BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg))>
    { };

    template<class Re, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
    Re call(Base &base BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, Arg, &arg)) const
    {
        return BOOST_PP_CAT(X_bind, n)<NullaryResult>()(base BOOST_PP_ENUM_TRAILING_PARAMS(n, arg));
    }


#undef  n
#endif
