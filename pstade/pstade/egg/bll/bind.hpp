#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BLL_BIND_HPP
#define PSTADE_EGG_BLL_BIND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
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
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "../apply_decl.hpp"
#include "../by_cref.hpp"
#include "./config.hpp"
#include "./result_of.hpp" // inclusion guaranteed


namespace pstade { namespace egg {


    namespace bll_bind_detail {


        template<class X>
        struct fun_to_ref :
            boost::mpl::eval_if< boost::is_function<X>,
                boost::add_reference<X>,
                boost::mpl::identity<X>
            >
        { };


        struct little
        {
            template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_BLL_BIND_MAX_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

        #define PSTADE_bind_tuple_mapper(N) \
            typename boost::lambda::detail::bind_tuple_mapper< \
                PSTADE_PP_ENUM_PARAMS_WITH(N, typename fun_to_ref<A, >::type) \
            >::type \
        /**/
        #define PSTADE_lambda_functor_base(N) \
            boost::lambda::lambda_functor_base< \
                boost::lambda::action<N, boost::lambda::function_action<N> >, \
                PSTADE_bind_tuple_mapper(N) \
            > \
        /**/
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_BLL_BIND_MAX_ARITY, <pstade/egg/bll/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_lambda_functor_base
        #undef  PSTADE_bind_tuple_mapper
        };


    } // namespace bll_bind_detail


    typedef function<bll_bind_detail::little, by_cref> T_bll_bind;
    PSTADE_POD_CONSTANT((T_bll_bind), bll_bind) = {{}};


} } // namespace pstade::egg


#include "../detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            boost::lambda::lambda_functor<
                PSTADE_lambda_functor_base(n)
            > // const
        type;
    };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return PSTADE_lambda_functor_base(n)(
            PSTADE_bind_tuple_mapper(n)(
                BOOST_PP_ENUM_PARAMS(n, a)
            )
        );
    }


#undef  n
#endif
