#ifndef PSTADE_EGG_NEGATE_HPP
#define PSTADE_EGG_NEGATE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_cref.hpp"


namespace pstade { namespace egg {


    namespace negate_detail {


        struct little
        {
            template<class Myself, class X>
            struct apply :
                boost::remove_cv<X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                return -x;
            }
        };


    } // negate_detail


    typedef function<negate_detail::little, by_cref> T_negate;

    PSTADE_ADL_BARRIER(negate) { // for 'std'
        PSTADE_POD_CONSTANT((T_negate), negate) = {{}};
    }


} } // namespace pstade::egg


#endif
