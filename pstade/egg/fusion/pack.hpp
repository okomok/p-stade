#ifndef PSTADE_EGG_FUSION_PACK_HPP
#define PSTADE_EGG_FUSION_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy fusion_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/include/vector.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../detail/baby_pack.hpp"
#include "../nullary_result_of.hpp"


namespace pstade { namespace egg {


    namespace fusion_detail {
        #define PSTADE_EGG_DETAIL_PACK_TEMPLATE(N) boost::fusion::vector
        #define PSTADE_EGG_DETAIL_PACK_MAX_ARITY FUSION_MAX_VECTOR_SIZE
        #include PSTADE_EGG_DETAIL_BABY_PACK()
    }


    #define PSTADE_EGG_FUSION_PACK_INIT {{}}


    template<class Strategy = by_perfect>
    struct X_fusion_pack :
        function<fusion_detail::baby_pack, Strategy>
    { };


    typedef X_fusion_pack<>::function_type T_fusion_pack;
    PSTADE_POD_CONSTANT((T_fusion_pack), fusion_pack) = PSTADE_EGG_FUSION_PACK_INIT;


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_fusion_pack, (class))


#endif
