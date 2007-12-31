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
#include "./baby_apply.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/call_baby.hpp"
#include "./use_brace2.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace egg {


    template<
        class Derived,
        class NullaryResult = boost::use_default,
        class Strategy      = by_perfect
    >
    struct function_facade;


    namespace function_facade_detail {


        template<class Facade>
        struct baby;

        template<class Derived, class NullaryResult, class Strategy>
        struct baby< function_facade<Derived, NullaryResult, Strategy> >
        {
            function_facade<Derived, NullaryResult, Strategy> *m_pfacade;

            Derived const& derived() const
            {
                return static_cast<Derived const&>(*m_pfacade);
            }

        // 0ary
            typedef NullaryResult nullary_result_type;

            template<class Result>
            Result call() const
            {
                return detail::call_baby<Derived, Result>::call(derived());
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct PSTADE_EGG_BABY_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/function_facade.hpp>))
            #include BOOST_PP_ITERATE()
        };


        template<class Derived, class NullaryResult, class Strategy>
        struct super_
        {
            typedef
                function<
                    baby< function_facade<Derived, NullaryResult, Strategy> >,
                    Strategy
                >
            type;
        };


    } // namespace function_facade_detail


    template<class Derived, class NullaryResult, class Strategy>
    struct function_facade :
        function_facade_detail::super_<Derived, NullaryResult, Strategy>::type
    {
    private:
        typedef typename function_facade_detail::super_<Derived, NullaryResult, Strategy>::type super_t;

    public:
        function_facade() :
            super_t(use_brace2()(boost::type<super_t>(), this))
        { }

    // You can't copy 'm_pfacade', which refers to the other facade.
        function_facade(function_facade const&) :
            super_t(use_brace2()(boost::type<super_t>(), this))
        { }

        function_facade& operator=(function_facade const&)
        {
            return *this;
        }
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
        Derived::template apply<Derived const, BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return detail::call_baby<Derived, Result>::call(derived(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
