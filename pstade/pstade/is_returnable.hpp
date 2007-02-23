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
// Returns true iif 'To foo() { return from; }' is well-defined.
// Precondition: 'To' is a reference or CopyConstructible.


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/version.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    namespace is_returnable_detail {


        template<class X, class Y>
        struct is_base_of :
        #if BOOST_VERSION < 103400
            // This is the TR1 behavior.
            boost::mpl::or_<
                boost::is_same<X, Y>,
                boost::is_base_of<X, Y>
            >
        #else
            boost::is_base_of<X, Y>
        #endif
        { };


        template<class From, class To>
        struct not_return_reference_to_temporary :
            boost::mpl::or_<
                boost::mpl::not_< boost::is_reference<To> >,
                boost::mpl::and_<
                    boost::is_reference<From>,
                    is_base_of<
                        typename remove_cvr<To>::type,
                        typename remove_cvr<From>::type
                    >
                >
            >
        { };


    } // namespace is_returnable_detail


    template<class From, class To>
    struct is_returnable :
        boost::mpl::and_<
            is_convertible_in_enable_if<From, To>,
            is_returnable_detail::not_return_reference_to_temporary<From, To>
        >
    { };


} // namespace pstade


#endif
