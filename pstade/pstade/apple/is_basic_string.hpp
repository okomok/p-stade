#ifndef PSTADE_APPLE_IS_BASIC_STRING_HPP
#define PSTADE_APPLE_IS_BASIC_STRING_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/remove_rcv.hpp>
#include "./basic_string_fwd.hpp"


namespace pstade { namespace apple {


namespace is_basic_string_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class CharT, class Traits, class Alloc >
    struct aux< std::basic_string<CharT, Traits, Alloc> > :
        boost::mpl::true_
    { };


} // namespace is_basic_string_detail


template< class T >
struct is_basic_string :
    is_basic_string_detail::aux<
        typename remove_rcv<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
