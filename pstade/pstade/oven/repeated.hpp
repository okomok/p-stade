#ifndef PSTADE_OVEN_REPEATED_HPP
#define PSTADE_OVEN_REPEATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_single.hpp"
#include "./cycled.hpp"


namespace pstade { namespace oven {


struct op_make_repeated :
    callable<op_make_repeated>
{
    template< class Myself, class Value, class Incrementable = void >
    struct apply :
        boost::result_of<
            op_make_cycled(
                typename boost::result_of<op_as_single(Value&)>::type, int, Incrementable&)
        >
    { };

    template< class Result, class Value, class Incrementable >
    Result call(Value& v, Incrementable& n) const
    {
        return make_cycled(as_single(v), 0, n);
    }

    template< class Myself, class Value >
    struct apply<Myself, Value> :
        boost::result_of<
            op_make_cycled(typename boost::result_of<op_as_single(Value&)>::type)
        >
    { };

    template< class Result, class Value >
    Result call(Value& v) const
    {
        return make_cycled(as_single(v));
    }
};


PSTADE_CONSTANT(make_repeated, (op_make_repeated))
PSTADE_PIPABLE(repeated, (op_make_repeated))


} } // namespace pstade::oven


#endif
