#ifndef PSTADE_OVEN_ADAPTOR_APPLIER_HPP
#define PSTADE_OVEN_ADAPTOR_APPLIER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/generator.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/adaptor_output_iterator.hpp"


namespace pstade { namespace oven {


typedef
    egg::generator<
        detail::adaptor_output_iterator<
            egg::deduce<boost::mpl::_1, egg::as_value>,
            egg::deduce<boost::mpl::_2, egg::as_value>
        >
    >::type
T_adaptor_applier;


PSTADE_POD_CONSTANT((T_adaptor_applier), adaptor_applier) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif
