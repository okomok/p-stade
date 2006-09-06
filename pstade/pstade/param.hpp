#ifndef PSTADE_PARAM_HPP
#define PSTADE_PARAM_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
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


namespace pstade {


template< class T >
struct param :
    boost::mpl::eval_if< boost::is_reference<T>,
        boost::mpl::identity<T>,
        boost::add_reference<
            typename boost::add_const<
                typename boost::remove_cv<T>::type
            >::type
        >
    >
{ };


} // namespace pstade


#endif
