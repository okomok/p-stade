#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_fuse_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_fuse
    {
        typedef
            function<detail::little_fuse_result<Base>, by_perfect>
        type;
    };


    #define PSTADE_EGG_FUSE_L { {
    #define PSTADE_EGG_FUSE_R } }
    #define PSTADE_EGG_FUSE(F) PSTADE_EGG_FUSE_L F PSTADE_EGG_FUSE_R


    typedef
        generator<
            result_of_fuse< deduce<boost::mpl::_1, as_value> >::type,
            by_value,
            use_brace2
        >::type
    T_fuse;


    PSTADE_POD_CONSTANT((T_fuse), fuse) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
