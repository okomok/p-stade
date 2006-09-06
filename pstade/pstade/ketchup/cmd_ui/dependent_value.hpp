#ifndef PSTADE_KETCHUP_CMD_UI_DEPENDENT_VALUE_HPP
#define PSTADE_KETCHUP_CMD_UI_DEPENDENT_VALUE_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>


namespace pstade { namespace ketchup {


typedef boost::mpl::int_<0>
default_;


typedef boost::mpl::int_<1>
dependent;


typedef boost::mpl::int_<2>
independent;


} } // namespace pstade::ketchup


#endif
