#ifndef PSTADE_IS_RETURNABLE_HPP
#define PSTADE_IS_RETURNABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Detects whether 'To foo() { return from; }' is safe or not.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    namespace is_returnable_detail {


        template< class From, class To >
        struct is_convertible :
        #if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
            // See the implementation of 'boost::enable_if_convertible'.
            // Just to be safe; 'is_returnable' is often used in 'enable_if'.
            boost::mpl::or_<
                boost::is_same<From, To>,
                boost::is_convertible<From, To>
            >
        #else
            boost::is_convertible<From, To>
        #endif
        { };


        template< class P, class Q >
        struct implies :
            boost::mpl::or_<boost::mpl::not_<P>, Q>
        { };


        template< class To >
        struct is_not_reference :
            boost::mpl::not_<
                boost::mpl::or_<
                    boost::is_pointer<To>,
                    boost::is_reference<To>
                >
            >
        { };


        template< class X >
        struct plain :
            remove_cvr<
                typename boost::remove_pointer<X>::type
            >
        { };


        template< class X, class Y >
        struct is_same_or_base_of :
            boost::mpl::or_<
                boost::is_same<
                    typename plain<X>::type,
                    typename plain<Y>::type
                >,
                boost::is_base_of<
                    typename plain<X>::type,
                    typename plain<Y>::type
                >
            >
        { };


    } // namespace is_returnable_detail


    template< class From, class To >
    struct is_returnable :
        boost::mpl::and_<
            is_returnable_detail::is_convertible<From, To>,
            boost::mpl::or_<
                is_returnable_detail::is_not_reference<To>,
                boost::mpl::and_<
                    is_returnable_detail::implies< boost::is_pointer<To>, boost::is_pointer<From> >,
                    is_returnable_detail::implies< boost::is_reference<To>, boost::is_reference<From> >,
                    is_returnable_detail::is_same_or_base_of<To, From>
                >
            >
        >
    { };


} // namespace pstade


#endif
