#ifndef BOOST_EGG_INFIX_HPP
#define BOOST_EGG_INFIX_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://sourceforge.net/projects/fcpp/
//
// foo(x, y)
// x ^foo^ y
// (x ^ foo) ^ y
//
// foo(x, y)
// x ^=foo^= y
// x ^= (foo ^= y)


#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace infix_detail {


        template<class Function, class Left>
        struct thingy
        {
            Function m_fun;
            Left m_left;

            thingy(Function fun, Left left) :
                m_fun(fun), m_left(left)
            { }
        };


    } // namespace infix_detail


    namespace infix {


        template<class Function, class Left> inline
        infix_detail::thingy<Function, Left &>
        operator^(Left &left, Function fun)
        {
            return infix_detail::thingy<Function, Left &>(fun, left);
        }

        template<class Function, class Left> inline
        infix_detail::thingy<Function, Left const &>
        operator^(Left const &left, Function fun)
        {
            return infix_detail::thingy<Function, Left const &>(fun, left);
        }

        template<class Function, class Left, class Right> inline
        typename result_of_<Function(Left &, Right &)>::type
        operator^(infix_detail::thingy<Function, Left &> x, Right &right)
        {
            return x.m_fun(x.m_left, right);
        }

        template<class Function, class Left, class Right> inline
        typename result_of_<Function(Left &, Right const &)>::type
        operator^(infix_detail::thingy<Function, Left &> x, Right const &right)
        {
            return x.m_fun(x.m_left, right);
        }


    } // namespace infix


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
