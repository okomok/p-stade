#ifndef PSTADE_APPLE_ATL_IS_ATL_CSTRINGT_HPP
#define PSTADE_APPLE_ATL_IS_ATL_CSTRINGT_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/remove_cvr.hpp>
#include "./str_fwd.hpp" // CStringT


namespace pstade { namespace apple {


namespace is_ATL_CStringT_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


    template< class BaseType, class StringTraits >
    struct aux< ATL::CStringT<BaseType, StringTraits> > :
        boost::mpl::true_
    { };


} // namespace namespace is_ATL_CStringT_detail


template< class T >
struct is_ATL_CStringT :
    is_ATL_CStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
