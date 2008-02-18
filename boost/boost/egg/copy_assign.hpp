#ifndef BOOST_EGG_COPY_ASSIGN_HPP
#define BOOST_EGG_COPY_ASSIGN_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ambiguity buster; call copy-assignment explicitly.


#include <boost/egg/ambi.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/copy.hpp>
#include <boost/egg/move_assign.hpp>


namespace boost { namespace egg {


    namespace copy_assign_detail {


        struct little
        {
            template<class Me, class To, class From>
            struct apply
            {
                typedef To &type;
            };

            template<class Re, class To, class From>
            Re call(To &to, From &from) const
            {
                move_assign(egg::copy<To>(from), to);
                return to;
            }
        };


    } // namespace copy_assign_detail


    typedef result_of_ambi1<function<copy_assign_detail::little>, by_perfect>::type T_copy_assign;
    BOOST_EGG_CONST((T_copy_assign), copy_assign) = BOOST_EGG_AMBI({{}});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
