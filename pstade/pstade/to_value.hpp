#ifndef PSTADE_TO_VALUE_HPP
#define PSTADE_TO_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable_by_value.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    namespace to_value_detail_ {


        struct op :
            callable_by_value<op, op const&>
        {
            template<class Result>
            Result call() const
            {
                return *this;
            }

            template<class Myself, class A>
            struct apply
            {
                typedef A type;
            };

            template<class Result, class A>
            Result call(A a) const
            {
                return a;
            }
        };


        template< class A > inline
        A operator|(A a, op)
        {
            return a;
        }


    } // namespace to_value_detail_


    typedef to_value_detail_::op op_to_value;
    PSTADE_CONSTANT(to_value, (op_to_value))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE(pstade::to_value_detail_::op)


#endif
