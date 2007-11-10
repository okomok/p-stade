#ifndef PSTADE_OVEN_INDEXING_HPP
#define PSTADE_OVEN_INDEXING_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/by_value.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./counting.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct pod_of_indexing
{
    struct baby
    {
        template< class Myself, class Incrementable1, class Incrementable2, class UnaryFun >
        struct apply :
            result_of<
                X_make_transformed<Reference, Value>(
                    typename result_of<T_counting(Incrementable1&, Incrementable2&)>::type,
                    UnaryFun&
                )
            >
        { };

        template< class Result, class Incrementable1, class Incrementable2, class UnaryFun >
        Result call(Incrementable1 i, Incrementable2 j, UnaryFun fun) const
        {
            return
                X_make_transformed<Reference, Value>()(
                    counting(i, j),
                    fun
                );
        }
    };

    typedef egg::function<baby, egg::by_value> type;
};


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct X_indexing :
    pod_of_indexing<Reference, Value>::type
{ };


typedef pod_of_indexing<>::type T_indexing;
PSTADE_POD_CONSTANT((T_indexing), indexing) = {{}};


} } // namespace pstade::oven


#endif
