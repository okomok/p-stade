#ifndef PSTADE_EGG_DELETE_ARRAY_HPP
#define PSTADE_EGG_DELETE_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/checked_delete.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_delete_array
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_array_delete(p);
        }
    };


    PSTADE_POD_CONSTANT((T_delete_array), delete_array) = {};


} } // namespace pstade::egg


#endif
