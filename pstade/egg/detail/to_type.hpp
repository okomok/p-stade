#ifndef PSTADE_EGG_DETAIL_TO_TYPE_HPP
#define PSTADE_EGG_DETAIL_TO_TYPE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type.hpp>


namespace pstade { namespace egg { namespace detail {


    // An explicit template parameter breaks down GCC overload resolution.

    template<class X> inline
    boost::type<X> to_type()
    {
        return boost::type<X>();
    }


} } } // namespace pstade::egg::detail


#endif
