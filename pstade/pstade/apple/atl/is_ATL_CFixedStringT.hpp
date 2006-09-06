#ifndef PSTADE_APPLE_ATL_IS_ATL_CFIXEDSTRINGT_HPP
#define PSTADE_APPLE_ATL_IS_ATL_CFIXEDSTRINGT_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/remove_cvr.hpp>
#include "./cstringt_fwd.hpp" // CFixedStringT


namespace pstade { namespace apple {


namespace is_ATL_CFixedStringT_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class StringType, int t_nChars >
    struct aux< ATL::CFixedStringT<StringType, t_nChars> > :
        boost::mpl::true_
    { };


} // namespace namespace is_ATL_CFixedStringT_detail


template< class T >
struct is_ATL_CFixedStringT :
    is_ATL_CFixedStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
