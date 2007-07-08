#ifndef PSTADE_OVEN_MAP_VALUES_HPP
#define PSTADE_OVEN_MAP_VALUES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include "./detail/baby_to_adaptor.hpp"
#include "./elements.hpp"


namespace pstade { namespace oven {


PSTADE_OVEN_BABY_TO_ADAPTOR(map_values, (tp_make_elements< boost::mpl::int_<1> >::baby))


} } // namespace pstade::oven


#endif
