#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_LAZY_HPP
#define BOOST_EGG_LAZY_HPP
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
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_LAZY_MAX_LEVEL
#include <boost/egg/const.hpp>
#include <boost/egg/construct_variadic1.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/detail/tuple_prepend.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    namespace lazy_detail {


        template<class Base, class Bind>
        struct little_result
        {
            Base m_base;

            Base const &base() const
            {
                return m_base;
            }

            template<class Me, class Args>
            struct apply :
                result_of_<
                    typename result_of_<
                        details::T_tuple_fuse(Bind)
                    >::type(typename result_of_<details::X_tuple_prepend<by_ref>(Args &, Base const &)>::type)
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return details::tuple_fuse(Bind())
                    (details::X_tuple_prepend<by_ref>()(args, m_base));
            }
        };


    } // namespace lazy_detail


    template<class Base, class Bind = use_default>
    struct result_of_lazy :
        variadic<
            lazy_detail::little_result<
                Base,
                typename details::if_use_default<Bind, T_bll_bind>::type
            >,
            by_value // not by_cref, following Boost.Bind.
        >
    { };

    #define BOOST_EGG_LAZY_L BOOST_EGG_VARIADIC_L {
    #define BOOST_EGG_LAZY_R } BOOST_EGG_VARIADIC_R
    #define BOOST_EGG_LAZY(F) BOOST_EGG_LAZY_L F BOOST_EGG_LAZY_R


    template<class Bind = use_default>
    struct X_lazy : details::derived_from_eval<
        generator<
            typename result_of_lazy<deduce<mpl::_1, as_value>, Bind>::type,
            by_value,
            X_construct_variadic1<>
        > >
    { };

    typedef X_lazy<>::base_class T_lazy;
    BOOST_EGG_CONST((T_lazy), lazy) = BOOST_EGG_GENERATOR();


    namespace lazy_0_detail {

        template<class Bind>
        struct nested
        {
            typedef Bind type;
        };

    }

    // 1level-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_LAZY_MAX_LEVEL, <boost/egg/lazy.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()
#define n_1 BOOST_PP_DEC(n)


    namespace BOOST_EGG_PP_CAT3(lazy_, n, _detail) {

        template<class Bind>
        struct nested :
            result_of_lazy<Bind, typename BOOST_EGG_PP_CAT3(lazy_, n_1, _detail)::nested<Bind>::type>
        { };

    }

    template<class Base, class Bind = use_default>
    struct BOOST_PP_CAT(result_of_lazy_, n) :
        result_of_lazy<
            Base,
            typename BOOST_EGG_PP_CAT3(lazy_, n, _detail)::nested<
                typename details::if_use_default<Bind, T_bll_bind>::type
            >::type
        >
    { };

    template<class Bind = use_default>
    struct BOOST_PP_CAT(X_lazy_, n) :
        X_lazy<
            typename BOOST_EGG_PP_CAT3(lazy_, n, _detail)::nested<
                typename details::if_use_default<Bind, T_bll_bind>::type
            >::type
        >
    { };

    typedef BOOST_PP_CAT(X_lazy_, n)<>::base_class BOOST_PP_CAT(T_lazy_, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_lazy_, n)), BOOST_PP_CAT(lazy_, n)) = BOOST_EGG_GENERATOR();


#undef  n_1
#undef  n
#endif
