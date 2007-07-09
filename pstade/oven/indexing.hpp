#ifndef PSTADE_OVEN_INDEXING_HPP
#define PSTADE_OVEN_INDEXING_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./counting.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct tp_indexing
{
    struct baby
    {
        template< class Myself, class Incrementable1, class Incrementable2, class UnaryFun >
        struct apply :
            result_of<
                xp_make_transformed<Reference, Value>(
                    typename result_of<op_counting(Incrementable1&, Incrementable2&)>::type,
                    UnaryFun&
                )
            >
        { };

        template< class Result, class Incrementable1, class Incrementable2, class UnaryFun >
        Result call(Incrementable1& i, Incrementable2& j, UnaryFun& fun) const
        {
            return
                xp_make_transformed<Reference, Value>()(
                    counting(i, j),
                    fun
                );
        }
    };

    typedef egg::function<baby> type;
};


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct xp_indexing :
    tp_indexing<Reference, Value>::type
{ };


typedef tp_indexing<>::type op_indexing;
PSTADE_POD_CONSTANT((op_indexing), indexing) = {{}};


} } // namespace pstade::oven


#endif
