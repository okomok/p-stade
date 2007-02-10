#ifndef PSTADE_AS_HPP
#define PSTADE_AS_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    namespace as_ref_detail {


        template<class X>
        struct baby
        {
            typedef X& result;

            result call(X& x)
            {
                return x;
            }
        };


        template<class X>
        struct cbaby
        {
            typedef X const& result;

            result call(X const& x)
            {
                return x;
            }
        };


        PSTADE_FUNCTION(normal,  (baby <_>))
        PSTADE_FUNCTION(cnormal, (cbaby<_>))


    } // namespace as_ref_detail


    PSTADE_AUXILIARY0(as_ref,  (as_ref_detail::op_normal))
    PSTADE_AUXILIARY0(as_cref, (as_ref_detail::op_cnormal))


    // Define 'as_value' without 'callable', 'function' nor 'auxiliary0'.
    // They would turn the argument into reference;
    // that's the dark-side of the language in the case of
    // function reference, which 'as_value' will work around.


    namespace as_value_detail {


        struct op
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
        A operator|(A a, op const&)
        {
            return a;
        }


    } // namespace as_value_detail


    typedef as_value_detail::op op_as_value;
    PSTADE_CONSTANT(as_value, (op_as_value))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE((pstade)(as_value_detail)(op))


#endif
