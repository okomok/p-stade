#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_AMBI_HPP
#define PSTADE_EGG_AMBI_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1742.pdf


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./baby_apply.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./generator.hpp"
#include "./pipable.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    #define PSTADE_EGG_AMBI_L { {
    #define PSTADE_EGG_AMBI_R } }
    #define PSTADE_EGG_AMBI(F) PSTADE_EGG_AMBI_L F PSTADE_EGG_AMBI_R


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/ambi.hpp>))
    #include BOOST_PP_ITERATE()


    // If msvc fails to find operator|, use this as super type.
    using ambi1_detail::lookup_ambi_operator;


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()
#define n_1 BOOST_PP_DEC(n)


    namespace PSTADE_PP_CAT3(ambi, n, _detail) {


        template<class Base>
        struct baby_result
        {
            Base m_base;

            typedef Base base_type;

            Base base() const
            {
                return m_base;
            }

#if n == 1
        // as pipe
            typedef
                function<baby_result, by_perfect>
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
                result_of<Base const(A0&)>
            { };

            template<class Result, class A0>
            Result call(A0& a0) const
            {
                return m_base(a0);
            }
#else
            template<class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct PSTADE_EGG_BABY_APPLY_DECL;

        // as pipe
            template<class Myself BOOST_PP_ENUM_TRAILING_PARAMS(n_1, class A)>
            struct apply<Myself BOOST_PP_ENUM_TRAILING_PARAMS(n_1, A)> :
                result_of<
                    typename result_of<T_pipable(Base const&)>::type(PSTADE_PP_ENUM_PARAMS_WITH(n_1, A, &))
                >
            { };

            template<class Result BOOST_PP_ENUM_TRAILING_PARAMS(n_1, class A)>
            Result call(BOOST_PP_ENUM_BINARY_PARAMS(n_1, A, & a)) const
            {
                return pipable(m_base)(BOOST_PP_ENUM_PARAMS(n_1, a));
            }

        // as function call
            template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
            struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
                result_of<Base const(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>
            { };    

            template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
            Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
            {
                return m_base(BOOST_PP_ENUM_PARAMS(n, a));
            }
#endif // n == 1
        };


#if n == 1
    // as pipe
        template<class A0, class Base> inline
        typename result_of<Base(A0&)>::type
        operator|(A0& a0, function<baby_result<Base>, by_perfect> pi)
        {
            return pi.baby().m_base(a0);
        }

        template<class A0, class Base> inline
        typename result_of<Base(PSTADE_DEDUCED_CONST(A0)&)>::type
        operator|(A0 const& a0, function<baby_result<Base>, by_perfect> pi)
        {
            return pi.baby().m_base(a0);
        }

        template<class A0, class Base> inline
        typename result_of<Base(A0&)>::type
        operator|=(function<baby_result<Base>, by_perfect> pi, A0& a0)
        {
            return pi.baby().m_base(a0);
        }

        template<class A0, class Base> inline
        typename result_of<Base(PSTADE_DEDUCED_CONST(A0)&)>::type
        operator|=(function<baby_result<Base>, by_perfect> pi, A0 const& a0)
        {
            return pi.baby().m_base(a0);
        }

        struct lookup_ambi_operator { };
#endif


    } // namespace ambin_detail


    template<class Base>
    struct PSTADE_PP_CAT3(result_of_, ambi, n)
    {
        typedef
            function<PSTADE_PP_CAT3(ambi, n, _detail)::baby_result<Base>, by_perfect>
        type;
    };

    typedef
        generator<
            PSTADE_PP_CAT3(result_of_, ambi, n)< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    BOOST_PP_CAT(T_ambi, n);

    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_ambi, n)), BOOST_PP_CAT(ambi, n)) = PSTADE_EGG_GENERATOR;


#undef n_1
#undef n
#endif
