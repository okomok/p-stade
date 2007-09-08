#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./detail/baby_fuse_result.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_fuse
    {
        typedef
            function<detail::baby_fuse_result<Base>, by_perfect>
        type;
    };


    #define PSTADE_EGG_FUSE_L { {
    #define PSTADE_EGG_FUSE_R } }


    typedef
        generator<
            result_of_fuse< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace_level1
        >::type
    op_fuse;


    PSTADE_POD_CONSTANT((op_fuse), fuse) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
