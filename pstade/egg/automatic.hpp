#ifndef PSTADE_EGG_AUTOMATIC_HPP
#define PSTADE_EGG_AUTOMATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This couldn't support the reference type as 'To',
// because the behavior of conversion-operator template
// varies from compiler to compiler...


#include "./detail/baby_fused_automatic.hpp"
#include "./function.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    // 'x|foo' seems impossible without yet another 'function<>'.

    template<class Lambda>
    struct automatic :
        unfuse_result<
            function< detail::baby_fused_automatic<Lambda> >,
            boost::use_default,
            use_nullary_result
        >
    { };


    #define PSTADE_EGG_AUTOMATIC_INITIALIZER() \
        PSTADE_EGG_UNFUSE_RESULT_INITIALIZER({ {} }, {})
    /**/


} } // namespace pstade::egg


#endif
