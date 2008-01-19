#ifndef PSTADE_EGG_INFIX_HPP
#define PSTADE_EGG_INFIX_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
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


#include <pstade/result_of.hpp>
#include "./forward.hpp"


namespace pstade { namespace egg {


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


    namespace infix_by_perfect {


        template<class Function, class Left> inline
        infix_detail::thingy<Function, Left&>
        operator^(Left& left, Function fun)
        {
            return infix_detail::thingy<Function, Left&>(fun, left);
        }

        template<class Function, class Left> inline
        infix_detail::thingy<Function, Left const&>
        operator^(Left const& left, Function fun)
        {
            return infix_detail::thingy<Function, Left const&>(fun, left);
        }

        template<class Function, class Left, class Right> inline
        typename result_of<Function(Left&, Right&)>::type
        operator^(infix_detail::thingy<Function, Left&> x, Right& right)
        {
            return x.m_fun(x.m_left, right);
        }

        template<class Function, class Left, class Right> inline
        typename result_of<Function(Left&, Right const&)>::type
        operator^(infix_detail::thingy<Function, Left&> x, Right const& right)
        {
            return x.m_fun(x.m_left, right);
        }


    } // namespace infix_by_perfect


    namespace infix = infix_by_perfect;


    namespace infix_by_value {


        template<class Function, class Left> inline
        infix_detail::thingy<Function, Left>
        operator^(Left left, Function fun)
        {
            return infix_detail::thingy<Function, Left>(fun, left);
        }

        template<class Function, class Left, class Right> inline
        typename result_of<Function(Left, Right)>::type
        operator^(infix_detail::thingy<Function, Left> x, Right right)
        {
            return x.m_fun(egg::forward<by_value>(x.m_left), egg::forward<by_value>(right));
        }


    } // namespace infix_by_value


} } // namespace pstade::egg


#endif
