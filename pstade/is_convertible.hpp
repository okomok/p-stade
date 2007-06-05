#ifndef PSTADE_IS_CONVERTIBLE_HPP
#define PSTADE_IS_CONVERTIBLE_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See the implementation of 'boost::enable_if_convertible'.
// VC7.1 occasionally fails regardless of SFINAE without this.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade {


    template<class From, class To>
    struct is_convertible :
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
        boost::mpl::or_<
            boost::is_same<From, To>,
            boost::is_convertible<From, To>
        >
#else
        boost::is_convertible<From, To>
#endif
    { };


} // namespace pstade


#endif
