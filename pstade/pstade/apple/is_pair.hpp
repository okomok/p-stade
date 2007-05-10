#ifndef PSTADE_APPLE_IS_PAIR_HPP
#define PSTADE_APPLE_IS_PAIR_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./pair_fwd.hpp"


namespace pstade { namespace apple {


namespace is_pair_detail {


    template< class X >
    struct aux :
        boost::mpl::false_
    { };


    template< class T, class U >
    struct aux< std::pair<T, U> > :
        boost::mpl::true_
    { };


} // namespace is_pair_detail


template< class X >
struct is_pair :
    is_pair_detail::aux<
        typename boost::remove_cv<X>::type
    >
{ };


} } // namespace pstade::apple


#endif
