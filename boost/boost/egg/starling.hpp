#ifndef BOOST_EGG_STARLING_HPP
#define BOOST_EGG_STARLING_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/curry.hpp> // curry3
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace starling_detail {


        // starling a b c = a c (b c)

        struct little_uncurried
        {
            template<class Me, class A, class B, class C>
            struct apply :
                result_of_<
                    typename result_of_<A(C &)>::type(
                        typename result_of_<B(C &)>::type
                    )
                >
            { };

            template<class Re, class A, class B, class C>
            Re call(A &a, B &b, C &c) const
            {
                return a(c)(b(c));
            }
        };

        typedef function<little_uncurried, by_perfect> uncurried;


    } // namespace starling_detail


    typedef result_of_curry3<starling_detail::uncurried>::type T_starling;
    BOOST_EGG_CONST((T_starling), starling) = BOOST_EGG_CURRY3({{}});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
