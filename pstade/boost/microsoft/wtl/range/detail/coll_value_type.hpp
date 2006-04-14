#ifndef BOOST_MICROSOFT_WTL_RANGE_DETAIL_COLL_VALUE_TYPE_HPP
#define BOOST_MICROSOFT_WTL_RANGE_DETAIL_COLL_VALUE_TYPE_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/detail/range/coll_value_type_fwd.hpp>
#include <boost/microsoft/wtl/ctrlw_fwd.hpp> // CSimpleStack
#include <boost/mpl/identity.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class T >
struct coll_value< WTL::CSimpleStack<T> > :
    mpl::identity<T>
{ };


} } } } // namespace boost::microsoft::detail::range


#endif
