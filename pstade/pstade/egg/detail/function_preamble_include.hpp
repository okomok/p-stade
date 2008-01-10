

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    typedef function function_type;
    typedef typename pstade::egg::detail::little_of<function_type>::type little_type;
    typedef typename pstade::egg::detail::strategy_of<function_type>::type strategy_type;

    typedef typename
        pstade::egg::detail::nullary_result<little_type, function>::type
    nullary_result_type;

    template<class Signature>
    struct result :
        pstade::egg::detail::of_apply_little<Signature>
    { };

    #include PSTADE_EGG_BLL_BINDABLE()

