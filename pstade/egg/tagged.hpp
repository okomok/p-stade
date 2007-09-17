#ifndef PSTADE_EGG_TAGGED_HPP
#define PSTADE_EGG_TAGGED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./ret.hpp"


namespace pstade { namespace egg {


    template<class Base, class Tag, class Strategy = boost::use_default>
    struct result_of_tagged :
        result_of_ret<Base, boost::use_default, Strategy, Tag>
    { };


    #define PSTADE_EGG_TAGGED_L PSTADE_EGG_RET_L
    #define PSTADE_EGG_TAGGED_R PSTADE_EGG_RET_R


} } // namespace pstade::egg


#endif
