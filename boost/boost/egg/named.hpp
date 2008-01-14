#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_NAMED_HPP
#define BOOST_EGG_NAMED_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/include/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include "./by_value.hpp"
#include "./by_cref.hpp"
#include "./config.hpp" // BOOST_EGG_MAX_LINEAR_ARITY
#include "./detail/get_arg.hpp"
#include "./fusion/pack.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {



    // BOOST_EGG_UNFUSE_L { { B } } BOOST_EGG_UNFUSE_M BOOST_EGG_FUSION_PACK_INIT BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_NAMED_L BOOST_EGG_UNFUSE_L { {
    #define BOOST_EGG_NAMED_R } } BOOST_EGG_UNFUSE_M BOOST_EGG_FUSION_PACK_INIT BOOST_EGG_UNFUSE_R
    #define BOOST_EGG_NAMED(B) BOOST_EGG_NAMED_L B BOOST_EGG_NAMED_R

// 1ary-
#define PSTADE_in_apply(Z, N, _) typedef typename result_of<detail::get_arg<Base, N>(NamedArgs&, boost::fusion::vector<BOOST_PP_ENUM_PARAMS(N, t_b)>)>::type BOOST_PP_CAT(t_b, N);
#define PSTADE_in_call(Z, N, _)  typename apply_::BOOST_PP_CAT(t_b, N) BOOST_PP_CAT(b, N) = detail::get_arg<Base, N>()(nargs, boost::fusion::vector<BOOST_PP_ENUM_PARAMS(N, typename apply_::t_b)>(BOOST_PP_ENUM_PARAMS(N, b)));
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/named.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_in_call
#undef  PSTADE_in_apply


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base>
    struct PSTADE_PP_CAT3(little_fused_named, n, _result)
    {
        typedef Base base_type;
        Base m_base;
        Base base() const { return m_base; }

        template<class Myself, class NamedArgs>
        struct apply
        {
            BOOST_PP_REPEAT(n, PSTADE_in_apply, ~)
            typedef typename result_of<Base const(PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::add_reference<t_b, >::type))>::type type;
        };

        template<class Result, class NamedArgs>
        Result call(NamedArgs& nargs) const
        {
            typedef apply<void, NamedArgs> apply_;
            BOOST_PP_REPEAT(n, PSTADE_in_call, ~)
            return m_base(BOOST_PP_ENUM_PARAMS(n, b));
        }
    };


    template<class Base, class NullaryResult = boost::use_default>
    struct PSTADE_PP_CAT3(result_of_, named, n) :
        result_of_unfuse<
            function<PSTADE_PP_CAT3(little_fused_named, n, _result)<Base>, by_cref>,
            T_fusion_pack,
            NullaryResult,
            by_cref
        >
    { };


    struct BOOST_PP_CAT(little_named, n)
    {
        template<class Myself, class Base>
        struct apply :
            PSTADE_PP_CAT3(result_of_, named, n)<Base>
        { };

        template<class Result, class Base>
        Result call(Base base) const
        {
            Result r = BOOST_EGG_NAMED(base);
            return r;
        }
    };

    typedef function<BOOST_PP_CAT(little_named, n), by_value> BOOST_PP_CAT(T_named, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_named, n)), BOOST_PP_CAT(named, n)) = BOOST_EGG_GENERATOR();


#undef n
#endif
