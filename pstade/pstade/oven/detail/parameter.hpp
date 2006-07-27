#ifndef PSTADE_OVEN_DETAIL_PARAMETER_HPP
#define PSTADE_OVEN_DETAIL_PARAMETER_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'detail::call_param'
//
// at Boost.Fusion-v2


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace oven { namespace detail {


template< class T >
struct parameter :
    boost::mpl::eval_if< boost::is_reference<T>,
        boost::mpl::identity<T>,
        boost::add_reference<
            typename boost::add_const<
                typename boost::remove_cv<T>::type
            >::type
        >
    >
{ };


} } } // namespace pstade::oven::detail


#endif
