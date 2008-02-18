#ifndef BOOST_EGG_STRONG_ASSIGN_HPP
#define BOOST_EGG_STRONG_ASSIGN_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/do_swap.hpp>
#include <boost/egg/function.hpp>


namespace boost { namespace egg {


    namespace strong_assign_detail {


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
                To tmp = from;
                do_swap(to, tmp);
                return to;
            }
        };


    } // namespace strong_assign_detail


    typedef result_of_ambi1< function<strong_assign_detail::little> >::type T_strong_assign;
    BOOST_EGG_CONST((T_strong_assign), strong_assign) = BOOST_EGG_AMBI({{}});


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
