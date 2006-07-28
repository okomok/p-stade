#ifndef PSTADE_OVEN_LIGHTWEIGHT_PROXY_HPP
#define PSTADE_OVEN_LIGHTWEIGHT_PROXY_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp> // foreach::tag
#include <boost/mpl/bool.hpp>


namespace pstade { namespace oven {


template< class Range >
struct lightweight_proxy
{
    friend
    boost::mpl::true_ *
    boost_foreach_is_lightweight_proxy(Range *&, boost::foreach::tag)
    {
        return 0;
    }
};


} } // namespace pstade::oven


#endif
