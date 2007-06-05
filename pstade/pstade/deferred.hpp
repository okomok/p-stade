#ifndef PSTADE_DEFERRED_HPP
#define PSTADE_DEFERRED_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a bug that 'boost::result_of<const function-pointer(..)>' doesn't work.
// If a function object 'F' may be a const pointer, use 'PSTADE_DEFERRED(F)'.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>


#if 1
    #define PSTADE_DEFERRED typename PSTADE_DEFERRED_TYPE
    #define PSTADE_DEFERRED_TYPE(F) pstade::deferred_detail::aux< F >::type
#else
    // Someday...
    #define PSTADE_DEFERRED(F) F
    #define PSTADE_DEFERRED_TYPE(F) F
#endif


namespace pstade { namespace deferred_detail {


    template<class T>
    struct is_pointer :
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
        boost::is_pointer<typename boost::remove_const<T>::type>
#else
        boost::is_pointer<T>
#endif
    { };


    template<class F>
    struct aux :
        boost::mpl::eval_if< is_pointer<F>,
            boost::remove_const<F>,
            boost::mpl::identity<F>
        >
    { };


} } // namespace pstade::deferred_detail


#endif
