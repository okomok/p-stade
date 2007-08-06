#ifndef PSTADE_EGG_INFIX_HPP
#define PSTADE_EGG_INFIX_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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


#include <pstade/result_of.hpp>


namespace pstade { namespace egg {


    namespace infix_detail {


        template<class Left, class Function>
        struct thingy
        {
            thingy(Left& left, Function fun) :
                m_left(left), m_fun(fun)
            { }

            Left& m_left;
            Function m_fun;
        };


    } // namespace infix_detail


    namespace infix {


        template<class Left, class Function> inline
        infix_detail::thingy<Left, Function>
        operator^(Left& left, Function fun)
        {
            return infix_detail::thingy<Left, Function>(left, fun);
        }

        template<class Left, class Function> inline
        infix_detail::thingy<Left const, Function>
        operator^(Left const& left, Function fun)
        {
            return infix_detail::thingy<Left const, Function>(left, fun);
        }


        template<class Left, class Function, class Right> inline
        typename result_of<Function(Left&, Right&)>::type
        operator^(infix_detail::thingy<Left, Function> x, Right& right)
        {
            return x.m_fun(x.m_left, right);
        }

        template<class Left, class Function, class Right> inline
        typename result_of<Function(Left&, Right const&)>::type
        operator^(infix_detail::thingy<Left, Function> x, Right const& right)
        {
            return x.m_fun(x.m_left, right);
        }


    } // namespace infix


} } // namespace pstade::egg


#endif
