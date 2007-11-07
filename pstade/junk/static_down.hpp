#ifndef PSTADE_EGG_STATIC_DOWN_HPP
#define PSTADE_EGG_STATIC_DOWN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./static_downcast.hpp"
#include "./automatic_ref.hpp"
#include "./auxiliary.hpp"


namespace pstade { namespace egg {


#if 1
    typedef
        result_of_auxiliary0<
            automatic_ref< X_static_downcast<boost::mpl::_> >::type
        >::type
    T_static_down;

    PSTADE_POD_CONSTANT((T_static_down), static_down)
        = PSTADE_EGG_AUXILIARY_L PSTADE_EGG_AUTOMATIC_REF PSTADE_EGG_AUXILIARY_R;
#else
    typedef automatic_ref< X_static_downcast<boost::mpl::_> >::type T_static_down;
    PSTADE_POD_CONSTANT((T_static_down), static_down)  = PSTADE_EGG_AUTOMATIC_REF;
#endif


} } // namespace pstade::egg


#endif
