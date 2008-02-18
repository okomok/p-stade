#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_MONO_HPP
#define BOOST_EGG_MONO_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/implicit_cast.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/construct_braced1.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/detail/plain.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace mono_detail {


        template<class Base, class Signature>
        struct result_;

    #define BOOST_EGG_forward(Z, N, _) boost::implicit_cast<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/mono.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_forward


    } // namespace mono_detail


    template<class Base, class Signature>
    struct result_of_mono
    {
        typedef mono_detail::result_<Base, Signature> type;
    };

    #define BOOST_EGG_MONO_L {
    #define BOOST_EGG_MONO_R }
    #define BOOST_EGG_MONO(F) BOOST_EGG_MONO_L F BOOST_EGG_MONO_R


    template<class Signature>
    struct X_mono :
        generator<
            typename result_of_mono<deduce<mpl::_1, as_value>, Signature>::type,
            by_value,
            X_construct_braced1<>
        >::type
    { };

    template<class Signature, class Base> inline
    typename result_of_<X_mono<Signature>(Base &)>::type mono(Base base)
    {
        return X_mono<Signature>()(base);
    }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()

#define fparams BOOST_EGG_PP_ENUM_PARAMS_IN_FUN_SPEC(n, A)


    template<class Base, class R BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct result_<Base, R(fparams)>
    {
        typedef typename
            details::eval_if_use_default< R,
                result_of_<Base const(fparams)>
            >::type
        result_type;

        typedef result_type (signature_type)(fparams);

        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

        result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
        {
            return m_base(BOOST_PP_ENUM(n, BOOST_EGG_forward, ~));
        }

#if n == 1
        typedef typename details::plain<A0>::type argument_type;
#elif n == 2
        typedef typename details::plain<A0>::type first_argument_type;
        typedef typename details::plain<A1>::type second_argument_type;
#endif
    };


#undef  fparams

#undef  n
#endif
