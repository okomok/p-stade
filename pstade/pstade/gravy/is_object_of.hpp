#ifndef PSTADE_GRAVY_IS_OBJECT_OF_HPP
#define PSTADE_GRAVY_IS_OBJECT_OF_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/oven/equals.hpp>
#include "./c_str.hpp"
#include "./class_name.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct op_is_object_of
    {
        typedef bool result_type;

        template<class CStringizable>
        bool operator()(window_ref wnd, CStringizable const& className) const
        {
            return oven::equals(class_name(wnd), c_str(className));
        }
    };


    PSTADE_CONSTANT(is_object_of, (op_is_object_of))


} } // namespace pstade::gravy


#endif
