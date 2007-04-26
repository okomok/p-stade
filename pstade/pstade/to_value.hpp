#ifndef PSTADE_TO_VALUE_HPP
#define PSTADE_TO_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    // Define 'to_value' without 'callable', 'function' nor 'auxiliary0'.
    // They would turn the argument into reference;
    // that's the dark-side of the language in the case of
    // function reference, which 'to_value' will work around.


    namespace to_value_detail_ {


        struct op :
            provide_sig
        {
            typedef // for callable macro
                op const&
            nullary_result_type;

            op const& operator()() const
            {
                return *this;
            }

            template<class FunCall>
            struct result
            { };

            template<class Fun, class A>
            struct result<Fun(A)> :
                pass_by_value<A>
            { };

            template< class A >
            A operator()(A a) const
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
