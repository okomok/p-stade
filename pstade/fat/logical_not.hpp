#ifndef PSTADE_FAT_LOGICAL_NOT_HPP
#define PSTADE_FAT_LOGICAL_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/object.hpp>


namespace pstade { namespace fat {


    struct op_logical_not
    {
        typedef bool result_type;

        template<class X>
        bool operator()(X const& x) const
        {
            return !x;
        }
    };


    PSTADE_EGG_OBJECT((op_logical_not), logical_not) = { };


} } // namespace pstade::fat


#endif
