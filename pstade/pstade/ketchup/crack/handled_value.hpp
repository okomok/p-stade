#ifndef PSTADE_KETCHUP_CRACK_HANDLED_VALUE_HPP
#define PSTADE_KETCHUP_CRACK_HANDLED_VALUE_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade { namespace ketchup {


typedef boost::mpl::true_
handled;


typedef boost::mpl::false_
not_handled;


} } // namespace pstade::ketchup


#endif
