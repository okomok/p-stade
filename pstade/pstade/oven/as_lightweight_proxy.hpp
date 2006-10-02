#ifndef PSTADE_OVEN_AS_LIGHTWEIGHT_PROXY_HPP
#define PSTADE_OVEN_AS_LIGHTWEIGHT_PROXY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp> // foreach::tag
#include <boost/mpl/bool.hpp>
#include <boost/mpl/empty_base.hpp>


namespace pstade { namespace oven {


// Workaround:
// VC7.1 complains about 'empty_base'
// if class hierarchy has two or more 'private' base of this.
// So the liner hierarchy optimization is given up.
//
template< class Range /*, class Base = boost::mpl::empty_base*/ >
struct as_lightweight_proxy 
    // : Base
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
