#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_AMBI_HPP
#define PSTADE_EGG_AMBI_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./apply_decl.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./forward.hpp"
#include "./function_fwd.hpp"
#include "./generator.hpp"
#include "./pipable.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    #define PSTADE_EGG_AMBI_L { {
    #define PSTADE_EGG_AMBI_R } }
    #define PSTADE_EGG_AMBI(F) PSTADE_EGG_AMBI_L F PSTADE_EGG_AMBI_R


    // 0ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_PIPABLE_MAX_ARITY, <pstade/egg/ambi.hpp>))
    #include BOOST_PP_ITERATE()


    // If msvc fails to find operator|, use this as super type.
    using ambi0_detail::lookup_ambi_operator;


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    namespace PSTADE_PP_CAT3(ambi, n, _detail) {


        template<class Base, class Strategy, class OperandBytag>
        struct little_result
        {
            Base m_base;

            typedef Base base_type;

            Base base() const
            {
                return m_base;
            }

#if n == 0
        // as pipe
            typedef
                function<little_result, Strategy>
            nullary_result_type;

            template<class Result>
            Result call() const
            {
                Result r = { { m_base } };
                return r;
            }

        // as function call
            template<class Myself, class A0>
            struct apply :
                result_of<Base const(typename result_of_forward<OperandBytag, A0>::type)>
            { };

            template<class Result, class A0>
            Result call(A0& a0) const
            {
                return m_base(egg::forward<OperandBytag>(a0));
            }
#else
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(BOOST_PP_INC(n), A)>
            struct PSTADE_EGG_APPLY_DECL;

        // as pipe
            template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
            struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
                result_of<
                    typename result_of<X_pipable<Strategy, OperandBytag>(Base const&)>::type(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
                >
            { };

            template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
            Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
            {
                return X_pipable<Strategy, OperandBytag>()(m_base)(BOOST_PP_ENUM_PARAMS(n, a));
            }

        // as function call
            template<class Myself, class O, BOOST_PP_ENUM_PARAMS(n, class A)>
            struct apply<Myself, O, BOOST_PP_ENUM_PARAMS(n, A)> :
                result_of<Base const(typename result_of_forward<OperandBytag, O>::type, PSTADE_EGG_FORWARDING_META_ARGS(n, A, Strategy const))>
            { };

            template<class Result, class O, BOOST_PP_ENUM_PARAMS(n, class A)>
            Result call(O& o, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
            {
                return m_base(egg::forward<OperandBytag>(o), PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
            }
#endif // n == 0
        };


#if n == 0

        struct lookup_ambi_operator { };
        using detail::or_is_same;


        // operator|
        //

        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< or_is_same<by_perfect, by_ref, OperandBytag>, result_of<Base(O&)> >::type
        operator|(O& o, function<little_result<Base, Strategy, OperandBytag>, Strategy> pi)
        {
            return pi.little().m_base(o);
        }

        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< or_is_same<by_perfect, by_cref, OperandBytag>, result_of<Base(PSTADE_DEDUCED_CONST(O)&)> >::type
        operator|(O const& o, function<little_result<Base, Strategy, OperandBytag>, Strategy> pi)
        {
            return pi.little().m_base(o);
        }

        // by_value
        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< boost::is_same<by_value, OperandBytag>, result_of<Base(O)> >::type
        operator|(O o, function<little_result<Base, Strategy, OperandBytag>, Strategy> pi)
        {
            return pi.little().m_base(egg::forward<by_value>(o));
        }


        // operator|=
        //

        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< or_is_same<by_perfect, by_ref, OperandBytag>, result_of<Base(O&)> >::type
        operator|=(function<little_result<Base, Strategy, OperandBytag>, Strategy> pi, O& o)
        {
            return pi.little().m_base(o);
        }

        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< or_is_same<by_perfect, by_cref, OperandBytag>, result_of<Base(PSTADE_DEDUCED_CONST(O)&)> >::type
        operator|=(function<little_result<Base, Strategy, OperandBytag>, Strategy> pi, O const& o)
        {
            return pi.little().m_base(o);
        }

        // by_value
        template<class O, class Base, class Strategy, class OperandBytag> inline
        typename lazy_enable_if< boost::is_same<by_value, OperandBytag>, result_of<Base(O)> >::type
        operator|=(function<little_result<Base, Strategy, OperandBytag>, Strategy> pi, O o)
        {
            return pi.little().m_base(egg::forward<by_value>(o));
        }

#endif // n == 0


    } // namespace ambiN_detail


    template<class Base, class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct PSTADE_PP_CAT3(result_of_, ambi, n)
    {
        typedef
            function<PSTADE_PP_CAT3(ambi, n, _detail)::little_result<Base, Strategy, OperandBytag>, Strategy>
        type;
    };


    template<class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct BOOST_PP_CAT(X_ambi, n) :
        generator<
            typename PSTADE_PP_CAT3(result_of_, ambi, n)<deduce<boost::mpl::_1, as_value>, Strategy, OperandBytag>::type,
            by_value,
            use_brace2
        >::type
    { };

    typedef BOOST_PP_CAT(X_ambi, n)<>::function_type BOOST_PP_CAT(T_ambi, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_ambi, n)), BOOST_PP_CAT(ambi, n)) = PSTADE_EGG_GENERATOR();


#undef n
#endif
