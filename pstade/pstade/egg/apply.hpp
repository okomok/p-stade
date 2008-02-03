#ifndef PSTADE_EGG_APPLY_HPP
#define PSTADE_EGG_APPLY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./fuse.hpp"
#include "./fusion/drop1.hpp"
#include "./fusion/get.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace apply_detail {


        struct little
        {
            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<
                        T_fuse(typename result_of<X_fusion_get_c<0>(Args&)>::type)
                    >::type(typename result_of<T_fusion_drop1(Args&)>::type)
                >
            { };

            template<class Re, class Args>
            Re call(Args& args) const
            {
                return fuse(X_fusion_get_c<0>()(args))(fusion_drop1(args));
            }
        };


    } // namespace apply_detail


    template<class Strategy = by_perfect>
    struct X_apply :
        variadic<apply_detail::little, Strategy>::type
    { };

    typedef X_apply<>::function_type T_apply;
PSTADE_ADL_BARRIER(apply) {
    PSTADE_POD_CONSTANT((T_apply), apply) = PSTADE_EGG_VARIADIC({});
}


} } // namespace pstade::egg


#endif
