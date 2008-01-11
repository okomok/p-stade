#ifndef PSTADE_GRAVY_BOOLEANIZE_HPP
#define PSTADE_GRAVY_BOOLEANIZE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ambi.hpp>
#include <pstade/egg/automatic.hpp>
#include <pstade/pod_constant.hpp>
#include "./boolean_cast.hpp"


namespace pstade { namespace gravy {


    namespace booleanize_detail {

        typedef egg::automatic< X_boolean_cast<boost::mpl::_> >::type base;

    }


    typedef
        egg::result_of_ambi0<
            booleanize_detail::base
        >::type
    T_booleanize;


    PSTADE_POD_CONSTANT((T_booleanize), booleanize)
        = PSTADE_EGG_AMBI_L PSTADE_EGG_AUTOMATIC() PSTADE_EGG_AMBI_R;


} } // namespace pstade::gravy


#endif
