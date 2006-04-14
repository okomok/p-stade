#ifndef BOOST_MICROSOFT_DETAIL_RANGE_CUSTOMIZE_FWD_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_CUSTOMIZE_FWD_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


namespace boost { namespace microsoft { namespace range_customize {


// customization points
//
template< class T >
struct tag;


template< class Tag, class T >
struct metafunctions;


template< class Tag >
struct functions;


} } } // namespace boost::microsoft::range_customize


#endif
