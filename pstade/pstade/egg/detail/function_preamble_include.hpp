

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    typedef function function_type;

    typedef typename detail::little_of<function_type>::type little_type;
    typedef typename detail::strategy_of<function_type>::type strategy_type;

    typedef typename
        detail::nullary_result_of_little<little_type, function>::type
    nullary_result_type;

    template<class Signature>
    struct result :
        detail::of_apply_little<Signature>
    { };

    typedef little_type base_type;

    little_type const& base() const
    {
        return this->little();
    }

    #include PSTADE_EGG_BLL_BINDABLE()

