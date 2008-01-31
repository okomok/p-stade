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
#include "./construct_braced2.hpp"
#include "./detail/is_a_or_b.hpp"
#include "./forward.hpp"
#include "./function_fwd.hpp"
#include "./generator.hpp"
#include "./pipable.hpp"


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


        template<class Base, class Bytag>
        struct little_result
        {
            Base m_base;

            Base const& base() const
            {
                return m_base;
            }

#if n == 0
        // as pipe
            typedef
                function<little_result, Bytag>
            nullary_result_type;

            template<class Re>
            Re call() const
            {
                Re r = { { m_base } };
                return r;
            }

        // as function call
            template<class Me, class A0>
            struct apply :
                result_of<Base const(typename result_of_forward<Bytag, A0>::type)>
            { };

            template<class Re, class A0>
            Re call(A0& a0) const
            {
                return m_base(egg::forward<Bytag>(a0));
            }
#else
            template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(BOOST_PP_INC(n), A)>
            struct PSTADE_EGG_APPLY_DECL;

        // as pipe
            template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
            struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
                result_of<
                    typename result_of<X_pipable<Bytag, Bytag>(Base const&)>::type(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
                >
            { };

            template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
            Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
            {
                return X_pipable<Bytag, Bytag>()(m_base)(BOOST_PP_ENUM_PARAMS(n, a));
            }

        // as function call
            template<class Me, class O, BOOST_PP_ENUM_PARAMS(n, class A)>
            struct apply<Me, O, BOOST_PP_ENUM_PARAMS(n, A)> :
                result_of<Base const(typename result_of_forward<Bytag, O>::type, PSTADE_EGG_FORWARDING_META_ARGS(n, A, Bytag const))>
            { };

            template<class Re, class O, BOOST_PP_ENUM_PARAMS(n, class A)>
            Re call(O& o, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
            {
                return m_base(egg::forward<Bytag>(o), PSTADE_EGG_FORWARDING_ARGS(n, a, Bytag const));
            }
#endif // n == 0
        };


#if n == 0

        struct lookup_ambi_operator { };
        using detail::is_a_or_b;


        // operator|
        //

        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< is_a_or_b<Bytag, by_perfect, by_ref>, result_of<Base(O&)> >::type
        operator|(O& o, function<little_result<Base, Bytag>, Bytag> pi)
        {
            return pi.little().m_base(o);
        }

        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< is_a_or_b<Bytag, by_perfect, by_cref>, result_of<Base(PSTADE_DEDUCED_CONST(O)&)> >::type
        operator|(O const& o, function<little_result<Base, Bytag>, Bytag> pi)
        {
            return pi.little().m_base(o);
        }

        // by_value
        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< boost::is_same<Bytag, by_value>, result_of<Base(O)> >::type
        operator|(O o, function<little_result<Base, Bytag>, Bytag> pi)
        {
            return pi.little().m_base(egg::forward<by_value>(o));
        }


        // operator|=
        //

        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< is_a_or_b<Bytag, by_perfect, by_ref>, result_of<Base(O&)> >::type
        operator|=(function<little_result<Base, Bytag>, Bytag> pi, O& o)
        {
            return pi.little().m_base(o);
        }

        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< is_a_or_b<Bytag, by_perfect, by_cref>, result_of<Base(PSTADE_DEDUCED_CONST(O)&)> >::type
        operator|=(function<little_result<Base, Bytag>, Bytag> pi, O const& o)
        {
            return pi.little().m_base(o);
        }

        // by_value
        template<class O, class Base, class Bytag> inline
        typename lazy_enable_if< boost::is_same<Bytag, by_value>, result_of<Base(O)> >::type
        operator|=(function<little_result<Base, Bytag>, Bytag> pi, O o)
        {
            return pi.little().m_base(egg::forward<by_value>(o));
        }

#endif // n == 0


    } // namespace ambiN_detail


    template<class Base, class Bytag = by_perfect>
    struct PSTADE_PP_CAT3(result_of_, ambi, n)
    {
        typedef
            function<PSTADE_PP_CAT3(ambi, n, _detail)::little_result<Base, Bytag>, Bytag>
        type;
    };


    template<class Bytag = by_perfect>
    struct BOOST_PP_CAT(X_ambi, n) :
        generator<
            typename PSTADE_PP_CAT3(result_of_, ambi, n)<deduce<mpl_1, as_value>, Bytag>::type,
            by_value,
            X_construct_braced2<>
        >::type
    { };

    typedef BOOST_PP_CAT(X_ambi, n)<>::function_type BOOST_PP_CAT(T_ambi, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_ambi, n)), BOOST_PP_CAT(ambi, n)) = PSTADE_EGG_GENERATOR();


#undef  n
#endif
