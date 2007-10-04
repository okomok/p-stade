// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  (C) Copyright Dave Abrahams, Steve Cleary, Beman Dawes, Howard
//  Hinnant & John Maddock 2000.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).


#ifndef BOOST_RANGE_DETAIL_VC7_1_RANGE_ITERATOR_HPP
#define BOOST_RANGE_DETAIL_VC7_1_RANGE_ITERATOR_HPP


#include <cstddef> // size_t
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/config.hpp> // BOOST_TT_DECL
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/mutable_iterator.hpp>


namespace boost {
    
    
    namespace range_detail_vc7_1 {


        // instantiated only in broken-array context
        template<class Array>
        struct array_iterator
        {
            // For some reason,
            // if `Array` is `T[N]`, `type` is `const T * const`, which is convertible to `T *`.
            // else if `Array` is `T const[N], `type` is `T * const`.
            typedef Array type;
        };

        // normal context
        template<class T, std::size_t N>
        struct array_iterator<T[N]>
        {
            typedef T *type;
        };


        // A "legacy" is_array must be used.
        // Partial-specialization system is broken at this point.
        template<class T>
        struct is_array
        {
            template<class T> struct wrap {};

            template<class T> static T(* is_array_tester1(wrap<T>) )(wrap<T>);
            char static BOOST_TT_DECL is_array_tester1(...);

            template<class T> static type_traits::no_type is_array_tester2(T(*)(wrap<T>));
            type_traits::yes_type static BOOST_TT_DECL is_array_tester2(...);

            static bool const value = sizeof(is_array_tester2(is_array_tester1(wrap<T>()))) == 1;
        };


        template<class Range, bool IsArray = is_array<Range>::value>
        struct range_iterator_aux;

        template<class Range>
        struct range_iterator_aux<Range, false> :
            mpl::eval_if< is_const<Range>,
                range_const_iterator<typename remove_const<Range>::type>,
                range_mutable_iterator<Range>
            >
        {};

        template<class Range>
        struct range_iterator_aux<Range, true> :
            array_iterator<Range>
        {};


    } // namespace range_detail_vc7_1


    template<class Range>
    struct vc7_1_range_iterator :
        range_detail_vc7_1::range_iterator_aux<Range>
    {};


} // namespace boost


#endif
