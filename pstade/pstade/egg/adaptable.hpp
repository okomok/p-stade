#ifndef PSTADE_EGG_ADAPTABLE_HPP
#define PSTADE_EGG_ADAPTABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Converts a FunctionObject supporting 'result_of' into an Adaptable one.


#include <pstade/result_of.hpp>
#include "./generator.hpp"
#include "./specified.hpp"
#include "./use_brace_level0.hpp"


namespace pstade { namespace egg {


    // unary

    template<class Base, class A0>
    struct result_of_unary_adaptable
    {
        typedef result_of_unary_adaptable type;

        Base m_base;

        // 'std::unary_function' would make this non-pod.
        typedef A0 argument_type;
        typedef typename result_of<Base const(A0&)>::type result_type;

        result_type operator()(A0& a0) const
        {
            return m_base(a0);
        }
    }; // ::type = { Base };

    #define PSTADE_EGG_UNARY_ADAPTABLE_L {
    #define PSTADE_EGG_UNARY_ADAPTABLE_R }

    template<class A0>
    struct tp_unary_adaptable :
        generator<
            result_of_unary_adaptable<deduce<boost::mpl::_1, as_value>, A0>,
            use_brace_level0
        >
    { };

    template<class A0>
    struct xp_unary_adaptable :
        tp_unary_adaptable<A0>::type
    { };

    PSTADE_EGG_SPECIFIED1(unary_adaptable, xp_unary_adaptable, (class))


    // binary

    template<class Base, class A0, class A1>
    struct result_of_binary_adaptable
    {
        typedef result_of_binary_adaptable type;

        Base m_base;

        typedef A0 first_argument_type;
        typedef A1 second_argument_type;
        typedef typename result_of<Base const(A0&, A1&)>::type result_type;

        result_type operator()(A0& a0, A1& a1) const
        {
            return m_base(a0, a1);
        }
    }; // ::type = { Base };

    #define PSTADE_EGG_BINARY_ADAPTABLE_L {
    #define PSTADE_EGG_BINARY_ADAPTABLE_R }

    template<class A0, class A1>
    struct tp_binary_adaptable :
        generator<
            result_of_binary_adaptable<deduce<boost::mpl::_1, as_value>, A0, A1>,
            use_brace_level0
        >
    { };

    template<class A0, class A1>
    struct xp_binary_adaptable :
        tp_binary_adaptable<A0, A1>::type
    { };

    PSTADE_EGG_SPECIFIED1(binary_adaptable, xp_binary_adaptable, (class)(class))


} } // namespace pstade::egg


#endif
