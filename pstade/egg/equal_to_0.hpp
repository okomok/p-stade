#ifndef PSTADE_EGG_EQUAL_TO_0_HPP
#define PSTADE_EGG_EQUAL_TO_0_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./object.hpp"


namespace pstade { namespace egg {


    struct op_equal_to_0
    {
        typedef bool result_type;

        template< class X >
        bool operator()(X const& x) const
        {
            return x == X(0);
        }
    };

    
    PSTADE_EGG_OBJECT((op_equal_to_0), equal_to_0) = {};


} } // namespace pstade::egg


#endif
