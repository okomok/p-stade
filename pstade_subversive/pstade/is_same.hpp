#ifndef PSTADE_IS_SAME_HPP
#define PSTADE_IS_SAME_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    struct op_is_same
    {
        typedef bool result_type;

        template<class X, class Y>
        bool operator()(X const& x, Y const& y) const
        {
            return boost::addressof(x) == boost::addressof(y);
        }
    };


    PSTADE_CONSTANT(is_same, (op_is_same))


} // namespace pstade


#endif
