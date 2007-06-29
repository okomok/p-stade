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


#include "./baby/fused_automatic.hpp"
#include "./baby/unfuse_result.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    // 'x|foo' seems impossible without yet another 'function<>'.

    template<class Lambda>
    struct automatic
    {
        typedef
            function<
                baby::unfuse_result<
                    function< baby::fused_automatic<Lambda> >,
                    boost::use_default,
                    use_nullary_result
                >
            >
        type;
    };


} } // namespace pstade::egg


#endif
