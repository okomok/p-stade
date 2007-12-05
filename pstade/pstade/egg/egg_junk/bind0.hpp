#ifndef PSTADE_EGG_DETAIL_BIND0_HPP
#define PSTADE_EGG_DETAIL_BIND0_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind0(f)(a1)
//   is equivalent to f(a1).
// This is for syntax consistency.


#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "../function.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct baby_bind0_result
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

        template<class Myself, class A0>
        struct apply :
            result_of<Base const(A0&)>
        { };

        template<class Result, class A0>
        Result call(A0& a0) const
        {
            return m_base(a0);
        }
    };


    struct baby_bind0
    {
        template<class Myself, class Base>
        struct apply
        {
            typedef
                function<
                    baby_bind0_result<
                        typename pass_by_value<Base>::type
                    >
                >
            type;
        };

        template<class Result, class Base, class Arg>
        Result call(Base& base) const
        {
            Result r = { { base } };
            return r;
        }
    };

    typedef function<baby_bind0> op_bind0;
    PSTADE_POD_CONSTANT((op_bind0), bind0) = {{}};


} } } // namespace pstade::egg::detail


#endif
