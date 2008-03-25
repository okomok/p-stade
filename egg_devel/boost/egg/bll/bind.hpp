#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BLL_BIND_HPP
#define BOOST_EGG_BLL_BIND_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/bind.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/bll/config.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace bll_bind_detail {


        template<class X>
        struct fun_to_ref :
            mpl::eval_if< is_function<X>,
                add_reference<X>,
                mpl::identity<X>
            >
        { };


        struct little
        {
            template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_BLL_BIND_MAX_ARITY, A)>
            struct BOOST_EGG_APPLY_DECL;

        #define BOOST_EGG_bind_tuple_mapper(N) \
            typename lambda::detail::bind_tuple_mapper< \
                BOOST_EGG_PP_ENUM_PARAMS_WITH(N, typename fun_to_ref<A, >::type) \
            >::type \
        /**/
        #define BOOST_EGG_lambda_functor_base(N) \
            lambda::lambda_functor_base< \
                lambda::action<N, lambda::function_action<N> >, \
                BOOST_EGG_bind_tuple_mapper(N) \
            > \
        /**/
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_BLL_BIND_MAX_ARITY, <boost/egg/bll/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  BOOST_EGG_lambda_functor_base
        #undef  BOOST_EGG_bind_tuple_mapper
        };


    } // namespace bll_bind_detail


    typedef function<bll_bind_detail::little, by_cref> T_bll_bind;
    BOOST_EGG_CONST((T_bll_bind), bll_bind) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            lambda::lambda_functor<
                BOOST_EGG_lambda_functor_base(n)
            > // const
        type;
    };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return BOOST_EGG_lambda_functor_base(n)(
            BOOST_EGG_bind_tuple_mapper(n)(
                BOOST_PP_ENUM_PARAMS(n, a)
            )
        );
    }


#undef  n
#endif
