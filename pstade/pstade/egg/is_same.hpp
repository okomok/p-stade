#ifndef PSTADE_EGG_IS_SAME_HPP
#define PSTADE_EGG_IS_SAME_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_is_same
    {
        typedef bool result_type;

        template<class X, class Y>
        bool operator()(X const& x, Y const& y) const
        {
            return boost::addressof(x) == boost::addressof(y);
        }
    };


    PSTADE_POD_CONSTANT((T_is_same), is_same) = {};


} } // namespace pstade::egg


#endif
