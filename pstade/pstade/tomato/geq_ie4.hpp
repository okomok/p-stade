#ifndef PSTADE_TOMATO_GEQ_IE4_HPP
#define PSTADE_TOMATO_GEQ_IE4_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/long.hpp>


namespace pstade { namespace tomato {


struct geq_ie4 :
    boost::mpl::greater_equal<
        boost::mpl::long_< _WIN32_IE >,
        boost::mpl::long_< 0x0400 >
    >
{ };


} } // namespace pstade::tomato


#endif
