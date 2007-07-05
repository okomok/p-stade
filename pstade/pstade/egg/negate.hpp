#ifndef PSTADE_EGG_NEGATE_HPP
#define PSTADE_EGG_NEGATE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_const.hpp>
#include <pstade/adl_barrier.hpp>
#include "./function.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    namespace negate_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply :
                boost::remove_const<X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                return -x;
            }
        };


    } // negate_detail


    typedef function<negate_detail::baby> op_negate;
    PSTADE_ADL_BARRIER(negate) { // for 'std'
        PSTADE_EGG_OBJECT((op_negate), negate) = { {} };
    }


} } // namespace pstade::egg


#endif
