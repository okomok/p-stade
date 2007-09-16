#ifndef PSTADE_EGG_DETAIL_FUSION_PACK_HPP
#define PSTADE_EGG_DETAIL_FUSION_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy fusion_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/container/vector.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../by_ref.hpp"
#include "./baby_pack.hpp"


namespace pstade { namespace egg { namespace detail {

    namespace fusion_detail {
        #define PSTADE_EGG_DETAIL_PACK_TEMPLATE(N) boost::fusion::vector
        #define PSTADE_EGG_DETAIL_PACK_MAX_ARITY FUSION_MAX_VECTOR_SIZE
        #include PSTADE_EGG_DETAIL_BABY_PACK()
    }

    #define PSTADE_EGG_FUSION_PACK_INIT {{}}

    typedef function<fusion_detail::baby_pack, by_perfect> op_fusion_pack;
    PSTADE_POD_CONSTANT((op_fusion_pack), fusion_pack) = PSTADE_EGG_FUSION_PACK_INIT;

    typedef function<fusion_detail::baby_pack, by_ref> op_fusion_pack_by_ref;
    PSTADE_POD_CONSTANT((op_fusion_pack_by_ref), fusion_pack_by_ref) = PSTADE_EGG_FUSION_PACK_INIT;


} } } // namespace pstade::egg::detail


#endif
