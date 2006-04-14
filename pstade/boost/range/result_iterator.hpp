// Fixed by MB 2006

// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_RESULT_ITERATOR_HPP
#define BOOST_RANGE_RESULT_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/range/config.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_extent.hpp>

#include <boost/mpl/assert.hpp>

namespace boost {


    namespace range_result_iterator_detail {


        template< class T >
        struct array_iterator :
            add_pointer< typename remove_extent<T>::type >
        { };


        template< class T >
        struct iterator :
            mpl::eval_if< is_const<T>,
                range_const_iterator< typename remove_cv<T>::type >,
                range_iterator< typename remove_cv<T>::type >
            >
        { };


    } // namespace range_result_iterator_detail


#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)


    template< class T >
    struct range_result_iterator :
        range_result_iterator_detail::iterator<T>
    { };


#else // is_const for array is broken under VC7.1


    template< class T >
    struct range_result_iterator :
        mpl::eval_if< mpl::not_< is_array< T > >,
            range_result_iterator_detail::iterator<T>,
            range_result_iterator_detail::array_iterator<T>
        >
    { };


#endif // !BOOST_WORKAROUND(BOOST_MSVC, == 1310)


} // namespace boost


#endif
