#ifndef PSTADE_OVEN_DETAIL_DECAY_FUNCTOR_HPP
#define PSTADE_OVEN_DETAIL_DECAY_FUNCTOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace oven { namespace detail {


template< class T >
struct decay_functor :
    boost::decay<
        typename boost::remove_cv<T>::type
    >
{ };


} } } // namespace pstade::oven::detail


#endif
