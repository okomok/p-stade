#ifndef PSTADE_FAT_DELETE_HPP
#define PSTADE_FAT_DELETE_HPP
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


    struct op_delete_
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_delete(p);
        }
    };


    PSTADE_EGG_OBJECT((op_delete_), delete_) = {};


} } // namespace pstade::fat


#endif
