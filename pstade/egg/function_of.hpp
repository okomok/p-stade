#ifndef PSTADE_EGG_FUNCTION_OF_HPP
#define PSTADE_EGG_FUNCTION_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./function_fwd.hpp"
#include "./detail/strategy_of_little.hpp"


namespace pstade { namespace egg {


    template<class Little, class Strategy = boost::use_default>
    struct function_of
    {
        typedef
            function<Little, typename detail::strategy_of_little<Little, Strategy>::type>
        type;
    };


} } // namespace pstade::egg


#endif
