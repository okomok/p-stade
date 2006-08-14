#ifndef PSTADE_RADISH_SAFE_BOOL_HPP
#define PSTADE_RADISH_SAFE_BOOL_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'safe_bool'
//
// at <boost/spirit/core/safe_bool.hpp>


#include <pstade/instance.hpp>
#include <pstade/nullptr.hpp>


namespace pstade { namespace radish {


namespace safe_bool_detail {

    struct aux { int true_; };

} // namespace safe_bool_detail


typedef int safe_bool_detail::aux::*safe_bool;

PSTADE_INSTANCE(safe_bool const, safe_true,  (&safe_bool_detail::aux::true_))
PSTADE_INSTANCE(safe_bool const, safe_false, (PSTADE_NULLPTR))


} } // namespace pstade::radish


#endif
