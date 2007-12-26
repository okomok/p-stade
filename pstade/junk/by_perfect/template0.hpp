#ifndef PSTADE_EGG_BY_PERFECT_TEMPLATE_HPP
#define PSTADE_EGG_BY_PERFECT_TEMPLATE_HPP
#include "../detail//prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



    typedef typename
        detail::nullary_result<Baby, function>::type
    nullary_result_type;

    nullary_result_type operator()() const
    {
        return detail::call_baby<
            Baby, nullary_result_type
        >::call(m_baby);
    }


#endif
