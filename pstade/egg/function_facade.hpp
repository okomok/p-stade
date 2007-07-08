#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNCTION_FACADE_HPP
#define PSTADE_EGG_FUNCTION_FACADE_HPP
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
#include <pstade/use_default.hpp>
#include "./apply_params.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./function.hpp"
#include "./use_brace_level1.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace egg {


    template<class Derived, class NullaryResult>
    struct function_facade;


    namespace function_facade_detail {


        template<class Facade>
        struct baby;

        template<class Derived, class NullaryResult>
        struct baby< function_facade<Derived, NullaryResult> >
        {
            function_facade<Derived, NullaryResult> *m_pfacade;

            Derived const& derived() const
            {
                return static_cast<Derived const&>(*m_pfacade);
            }

        // 0ary
            typedef NullaryResult nullary_result_type;

            template<class Result>
            Result call() const
            {
                return derived().template call<Result>();
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply { }; // msvc warns if incomplete.

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/function_facade.hpp>))
            #include BOOST_PP_ITERATE()
        };


        template<class Derived, class NullaryResult>
        struct super_
        {
            typedef
                function<
                    baby< function_facade<Derived, NullaryResult> >
                >
            type;
        };


    } // namespace function_facade_detail


    template<class Derived, class NullaryResult = boost::use_default>
    struct function_facade :
        function_facade_detail::super_<Derived, NullaryResult>::type        
    {
    private:
        typedef typename function_facade_detail::super_<Derived, NullaryResult>::type super_t;

    public:
        function_facade() :
            super_t(use_brace_level1()(boost::type<super_t>(), this))
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
        Derived::template apply<
            Derived, BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return derived().template call<Result>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
