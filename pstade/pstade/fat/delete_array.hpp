#ifndef PSTADE_FAT_DELETE_ARRAY_HPP
#define PSTADE_FAT_DELETE_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/checked_delete.hpp>
#include <pstade/egg/object.hpp>


namespace pstade { namespace fat {


    struct op_delete_array
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_array_delete(p);
        }
    };


    PSTADE_EGG_OBJECT((op_delete_array), delete_array) = {};


} } // namespace pstade::fat


#endif
