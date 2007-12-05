#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_CALLABLE_FACADE_HPP
#define PSTADE_EGG_CALLABLE_FACADE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include "./aggregate1.hpp"
#include "./apply_params.hpp"
#include "./callable.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace egg {


    template<class Derived, class NullaryResult>
    struct callable_facade;


    namespace callable_facade_detail {


        template<class Facade, class Derived>
        struct baby
        {
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply
            { }; // msvc warns if incomplete.

            // 0ary
            template<class Result>
            Result call() const
            {
                return derived().BOOST_NESTED_TEMPLATE call<Result>();
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/callable_facade.hpp>))
            #include BOOST_PP_ITERATE()

            Derived const& derived() const
            {
                return static_cast<Derived const&>(*m_pfacade);
            }

            Facade *m_pfacade;
        };


        template<class Derived, class NullaryResult>
        struct super_
        {
            typedef
                callable<
                    baby<callable_facade<Derived, NullaryResult>, Derived>,
                    NullaryResult
                >
            type;
        };


    } // namespace callable_facade_detail


    template<class Derived, class NullaryResult = boost::use_default>
    struct callable_facade :
        callable_facade_detail::super_<Derived, NullaryResult>::type        
    {
        typedef typename callable_facade_detail::super_<Derived, NullaryResult>::type super_t;

        callable_facade() :
            super_t(aggregate1()(boost::type<super_t>(), this))
        { }
    };


} } // namespace pstade::egg


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        Derived::BOOST_NESTED_TEMPLATE apply<
            Derived, BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return derived().BOOST_NESTED_TEMPLATE call<Result>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
