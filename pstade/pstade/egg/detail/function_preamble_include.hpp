

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    typedef typename pstade::egg::detail::little_of<function>::type little_type;
    typedef typename pstade::egg::detail::strategy_of<function>::type strategy_type;

    typedef typename
        pstade::egg::detail::nullary_result_of_little<little_type, function>::type
    nullary_result_type;

    template<class PStadeEgg_FunCall>
    struct result :
        pstade::egg::detail::of_apply_little<PStadeEgg_FunCall>
    { };

    little_type const &base() const
    {
        return this->little();
    }

    template<class PStadeEgg_FunArgs>
    struct sig :
        pstade::egg::bll_sig<PStadeEgg_FunArgs>
    { };
