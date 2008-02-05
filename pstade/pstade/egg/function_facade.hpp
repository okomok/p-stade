#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNCTION_FACADE_HPP
#define PSTADE_EGG_FUNCTION_FACADE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <pstade/use_default.hpp>
#include "./apply_decl.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/call_little_impl.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace egg {


    template<
        class Derived,
        class Strategy      = by_perfect,
        class NullaryResult = boost::use_default
    >
    struct function_facade;


    namespace function_facade_detail {


        template<class Facade>
        struct little;

        template<class Derived, class Strategy, class NullaryResult>
        struct little< function_facade<Derived, Strategy, NullaryResult> >
        {
            function_facade<Derived, Strategy, NullaryResult> *m_pfacade;

            Derived const& derived() const
            {
                return static_cast<Derived const&>(*m_pfacade);
            }

        // 0ary
            typedef NullaryResult nullary_result_type;

            template<class Re>
            Re call() const
            {
                return call_little_impl<
                    Derived, Re
                >::call0(derived());
            }

        // 1ary-
            template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/function_facade.hpp>))
            #include BOOST_PP_ITERATE()
        };


        template<class Derived, class Strategy, class NullaryResult>
        struct super_
        {
            typedef
                function<
                    little< function_facade<Derived, Strategy, NullaryResult> >,
                    Strategy
                >
            type;
        };


        template<class Super, class Derived> inline
        Super make_(Derived *derived)
        {
            Super s = {{derived}};
            return s;
        }


    } // namespace function_facade_detail


    template<class Derived, class Strategy, class NullaryResult>
    struct function_facade :
        function_facade_detail::super_<Derived, Strategy, NullaryResult>::type
    {
    private:
        typedef typename function_facade_detail::super_<Derived, Strategy, NullaryResult>::type super_t;

    public:
        function_facade() :
            super_t(function_facade_detail::make_<super_t>(this))
        { }

    // You can't copy 'm_pfacade', which refers to the other facade.
        function_facade(function_facade const&) :
            super_t(function_facade_detail::make_<super_t>(this))
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


#include "./detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        Derived::template apply<Derived const, BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return call_little_impl<
            Derived, Re
        >::BOOST_PP_CAT(call, n)(derived(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
