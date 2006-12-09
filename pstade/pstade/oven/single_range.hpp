#ifndef PSTADE_OVEN_SINGLE_RANGE_HPP
#define PSTADE_OVEN_SINGLE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The constant-iterator is the same as the mutable-iterator.
// Const-ness of this range muste be independent from
// const-ness of the 'Value'.


#include <boost/utility/addressof.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template< class Value >
struct single_range :
    iter_range<Value *>::type,
    private as_lightweight_proxy< single_range<Value> >
{
private:
    typedef typename iter_range<Value *>::type super_t;

public:
    explicit single_range(Value& v) :
        super_t(boost::addressof(v), boost::addressof(v) + 1)
    { }
};


struct op_make_single_range :
    callable<op_make_single_range>
{
    template< class Myself, class Value >
    struct apply
    {
        typedef single_range<Value> const type;
    };

    template< class Result, class Value >
    Result call(Value& v) const
    {
        return Result(v);
    }
};


PSTADE_CONSTANT(make_single_range, op_make_single_range)
PSTADE_PIPABLE(as_single, op_make_single_range)


} } // namespace pstade::oven


#endif
