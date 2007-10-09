#ifndef PSTADE_EGG_TUPLE_PACK_HPP
#define PSTADE_EGG_TUPLE_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <pstade/pod_constant.hpp>
#include "../detail/baby_pack.hpp"
#include "../by_perfect.hpp"
#include "../by_ref.hpp"
#include "./config.hpp"


namespace pstade { namespace egg {

    namespace tuple_detail {
        #define PSTADE_EGG_DETAIL_PACK_TEMPLATE(N) boost::tuples::tuple
        #define PSTADE_EGG_DETAIL_PACK_MAX_ARITY PSTADE_EGG_TUPLE_MAX_SIZE
        #include PSTADE_EGG_DETAIL_BABY_PACK()
    }

    #define PSTADE_EGG_TUPLE_PACK_INIT {{}}

    typedef function<tuple_detail::baby_pack, by_perfect> T_tuple_pack;
    PSTADE_POD_CONSTANT((T_tuple_pack), tuple_pack) = PSTADE_EGG_TUPLE_PACK_INIT;

    typedef function<tuple_detail::baby_pack, by_ref> T_tuple_pack_by_ref;
    PSTADE_POD_CONSTANT((T_tuple_pack_by_ref), tuple_pack_by_ref) = PSTADE_EGG_TUPLE_PACK_INIT;


} } // namespace pstade::egg


#endif
