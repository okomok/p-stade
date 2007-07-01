#ifndef PSTADE_EGG_IS_MAKABLE_HPP
#define PSTADE_EGG_IS_MAKABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade { namespace egg {


    template<class X>
    struct is_makable :
        boost::mpl::false_
    { };


} } // namespace pstade::egg


#endif
