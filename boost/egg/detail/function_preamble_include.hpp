

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    typedef typename boost::egg::
        details::little_of<function>::type
    little_type;

    typedef typename boost::egg::
        details::strategy_of<function>::type
    strategy_type;

    typedef typename boost::egg::
        details::nullary_result_of_little<little_type, function>::type
    nullary_result_type;

    template<class BoostEgg_FunCall>
    struct result : boost::egg::
        details::of_apply_little<BoostEgg_FunCall>
    { };

    little_type const &base() const
    {
        return this->little();
    }

    template<class BoostEgg_FunArgs>
    struct sig : boost::egg::
        bll_sig_impl<BoostEgg_FunArgs>
    { };
