#ifndef BOOST_EGG_INFIX_HPP
#define BOOST_EGG_INFIX_HPP
#include "./detail/prefix.hpp"


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


#include <boost/egg/pstade/result_of.hpp>


namespace pstade { namespace egg {


    namespace infix_detail {


        template<class Function, class Arg>
        struct thingy
        {
            thingy(Function fun, Arg& arg) :
                m_fun(fun), m_arg(arg)
            { }

            Function m_fun;
            Arg& m_arg;
        };


    } // namespace infix_detail


    namespace infix {


        // operator^
        //

        template<class Function, class Arg> inline
        infix_detail::thingy<Function, Arg>
        operator^(Arg& arg, Function fun)
        {
            return infix_detail::thingy<Function, Arg>(fun, arg);
        }

        template<class Function, class Arg> inline
        infix_detail::thingy<Function, Arg const>
        operator^(Arg const& arg, Function fun)
        {
            return infix_detail::thingy<Function, Arg const>(fun, arg);
        }

        template<class Function, class Arg, class Right> inline
        typename result_of<Function(Arg&, Right&)>::type
        operator^(infix_detail::thingy<Function, Arg> x, Right& right)
        {
            return x.m_fun(x.m_arg, right);
        }

        template<class Function, class Arg, class Right> inline
        typename result_of<Function(Arg&, Right const&)>::type
        operator^(infix_detail::thingy<Function, Arg> x, Right const& right)
        {
            return x.m_fun(x.m_arg, right);
        }


        // operator=>>, operator<<=
        //

        template<class Function, class Arg> inline
        infix_detail::thingy<Function, Arg>
        operator^=(Function fun, Arg& arg)
        {
            return infix_detail::thingy<Function, Arg>(fun, arg);
        }

        template<class Function, class Arg> inline
        infix_detail::thingy<Function, Arg const>
        operator^=(Function fun, Arg const& arg)
        {
            return infix_detail::thingy<Function, Arg const>(fun, arg);
        }

        template<class Function, class Arg, class Left> inline
        typename result_of<Function(Left&, Arg&)>::type
        operator^=(Left& left, infix_detail::thingy<Function, Arg> x)
        {
            return x.m_fun(left, x.m_arg);
        }

        template<class Function, class Arg, class Left> inline
        typename result_of<Function(Left const&, Arg&)>::type
        operator^=(Left const& left, infix_detail::thingy<Function, Arg> x)
        {
            return x.m_fun(left, x.m_arg);
        }


    } // namespace infix


} } // namespace pstade::egg


#endif
