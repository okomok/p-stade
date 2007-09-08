#ifndef PSTADE_EGG_TO_VALUE_HPP
#define PSTADE_EGG_TO_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_value.hpp"


namespace pstade { namespace egg {


    namespace to_value_detail_ {


        struct baby
        {
            typedef
                function<baby, by_value>
            nullary_result_type;

            template<class Result>
            Result call() const
            {
                Result result = {{}};
                return result;
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


        typedef function<baby, by_value> op;


        template<class A> inline
        A operator|(A a, op)
        {
            return a;
        }


    } // namespace to_value_detail_


    typedef to_value_detail_::op op_to_value;
    PSTADE_POD_CONSTANT((op_to_value), to_value) = {{}};


} } // namespace pstade::egg


#endif
