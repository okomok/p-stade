#ifndef PSTADE_EGG_INTEGRALIZE_HPP
#define PSTADE_EGG_INTEGRALIZE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./automatic.hpp"
#include "./integral_cast.hpp"


namespace pstade { namespace egg {


    namespace integralize_detail {

        typedef automatic< X_integral_cast<boost::mpl::_1> >::type op;

    }


    typedef result_of_ambi0<integralize_detail::op>::type T_integralize;
    PSTADE_POD_CONSTANT((T_integralize), integralize) = PSTADE_EGG_AMBI_L PSTADE_EGG_AUTOMATIC PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
