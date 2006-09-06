#ifndef PSTADE_APPLE_ATL_IS_ATL_CSIMPLESTRINGT_HPP
#define PSTADE_APPLE_ATL_IS_ATL_CSIMPLESTRINGT_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/remove_cvr.hpp>
#include "./config.hpp" // ATL_HAS_OLD_SIMPLE_STRING
#include "./simpstr_fwd.hpp"


namespace pstade { namespace apple {


namespace is_ATL_CSimpleStringT_detail {


    template< class T >
    struct aux :
        boost::mpl::false_
    { };


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLESTRING)

    template< class BaseType, bool t_bMFCDLL >
    struct aux< ATL::CSimpleStringT<BaseType, t_bMFCDLL> > :
        boost::mpl::true_
    { };

#else

    template< class BaseType >
    struct aux< ATL::CSimpleStringT<BaseType> > :
        boost::mpl::true_
    { };

#endif


} // namespace namespace is_ATL_CSimpleStringT_detail


template< class T >
struct is_ATL_CSimpleStringT :
    is_ATL_CSimpleStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
