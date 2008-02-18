#ifndef BOOST_EGG_TO_VALUE_HPP
#define BOOST_EGG_TO_VALUE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    namespace to_value_detail {


        struct little
        {
            template<class Me, class A>
            struct apply
            {
                typedef A type;
            };

            template<class Re, class A>
            Re call(A a) const
            {
                return a;
            }
        };


    } // namespace to_value_detail


    typedef result_of_ambi0<function<to_value_detail::little, by_value>, by_value>::type T_to_value;
    BOOST_EGG_CONST((T_to_value), to_value) = BOOST_EGG_AMBI({{}});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
