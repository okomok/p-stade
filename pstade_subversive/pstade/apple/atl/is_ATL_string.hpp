#ifndef PSTADE_APPLE_ATL_IS_ATL_STRING_HPP
#define PSTADE_APPLE_ATL_IS_ATL_STRING_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <pstade/remove_cvr.hpp>
#include "./config.hpp"
#include "./cstringt_fwd.hpp" // CFixedStringT
#include "./simpstr_fwd.hpp" // CSimpleStringT
#include "./str_fwd.hpp" // CStringT


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

}

template< class T >
struct is_ATL_CFixedStringT :
    is_ATL_CFixedStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


namespace is_ATL_CSimpleStringT_detail {

    template< class T >
    struct aux :
        boost::mpl::false_
    { };

    template< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
    struct aux< ATL::CSimpleStringT< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > > :
        boost::mpl::true_
    { };

}

template< class T >
struct is_ATL_CSimpleStringT :
    is_ATL_CSimpleStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


namespace is_ATL_CStringT_detail {

    template< class T >
    struct aux :
        boost::mpl::false_
    { };

    template< class BaseType, class StringTraits >
    struct aux< ATL::CStringT<BaseType, StringTraits> > :
        boost::mpl::true_
    { };

}

template< class T >
struct is_ATL_CStringT :
    is_ATL_CStringT_detail::aux<
        typename remove_cvr<T>::type
    >
{ };


template< class T >
struct is_ATL_string :
    boost::mpl::or_<
        is_ATL_CFixedStringT<T>,
        is_ATL_CSimpleStringT<T>,
        is_ATL_CStringT<T>
    >
{ };


} } // namespace pstade::apple


#endif
