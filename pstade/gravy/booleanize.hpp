#ifndef PSTADE_GRAVY_BOOLEANIZE_HPP
#define PSTADE_GRAVY_BOOLEANIZE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/automatic.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/pod_constant.hpp>
#include "./boolean_cast.hpp"


namespace pstade { namespace gravy {


    namespace booleanize_detail {
        typedef egg::automatic< xp_boolean_cast<boost::mpl::_> >::type op;
    }


    typedef
        egg::result_of_auxiliary0<
            booleanize_detail::op
        >::type
    op_booleanize;


    PSTADE_POD_CONSTANT((op_booleanize), booleanize)
        = PSTADE_EGG_AUXILIARY(PSTADE_EGG_AUTOMATIC_TYPE)();


} } // namespace pstade::gravy


#endif
