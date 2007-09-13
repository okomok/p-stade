#ifndef PSTADE_EGG_TUPLE_PACK_HPP
#define PSTADE_EGG_TUPLE_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../by_ref.hpp"
#include "./detail/baby_pack.hpp"


namespace pstade { namespace egg {


    #define PSTADE_EGG_TUPLE_PACK_INIT {{}}

    typedef function<tuple_detail::baby_pack, by_perfect> op_tuple_pack;
    PSTADE_POD_CONSTANT((op_tuple_pack), tuple_pack) = PSTADE_EGG_TUPLE_PACK_INIT;

    typedef function<tuple_detail::baby_pack, by_ref> op_tuple_pack_by_ref;
    PSTADE_POD_CONSTANT((op_tuple_pack_by_ref), tuple_pack_by_ref) = PSTADE_EGG_TUPLE_PACK_INIT;


} } // namespace pstade::egg


#endif
