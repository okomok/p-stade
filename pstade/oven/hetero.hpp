#ifndef PSTADE_OVEN_HETERO_HPP
#define PSTADE_OVEN_HETERO_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/egg/tuple/size.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./detail/hetero_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Reference, class Value = boost::use_default >
struct tp_hetero
{
    struct baby
    {
        template< class Myself, class Tuple >
        struct apply
        {
            typedef
                detail::hetero_iterator<
                    Tuple,
                    Reference,
                    typename eval_if_use_default< Value, remove_cvr<Reference> >::type
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Tuple >
        Result call(Tuple& tup) const
        {
            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(tup, 0),
                iter_t(tup, egg::tuple_size<Tuple>::value)
            );
        }
    };

    typedef egg::function<baby> type;
};


template< class Reference, class Value = boost::use_default >
struct xp_hetero :
    tp_hetero<Reference, Value>::type
{ };


PSTADE_EGG_SPECIFIED1(hetero, xp_hetero, (class))


} } // namespace pstade::oven


#endif
