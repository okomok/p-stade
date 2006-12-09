#ifndef PSTADE_OVEN_ZIP_WITH_RANGE_HPP
#define PSTADE_OVEN_ZIP_WITH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// If you have a function taking a tuple,
// you can use of course 'rng|zipped|transformed(f)'.


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/tupled.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_base.hpp"
#include "./transform_range.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace zip_with_range_detail {


    template<
        class RangeTuple,
        class Function,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef transform_range<
            zip_range<RangeTuple> const,
            typename boost::result_of<op_tupled(Function const&)>::type,
            Reference,
            Value
        > type;
    };


} // namespace zip_with_range_detail


template<
    class RangeTuple,
    class Function,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct zip_with_range :
    zip_with_range_detail::super_<RangeTuple, Function, Reference, Value>::type,
    private as_lightweight_proxy< zip_with_range<RangeTuple, Function, Reference, Value> >
{
    typedef RangeTuple range_tuple_type;

private:
    typedef typename zip_with_range_detail::super_<RangeTuple, Function, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;

public:
    zip_with_range(RangeTuple& tup, Function const& fun) :
        super_t(base_t(tup), pstade::tupled(fun))
    { }
};


struct op_make_zip_with_range :
    callable<op_make_zip_with_range>
{
    template< class Myself, class RangeTuple, class Function >
    struct apply
    {
        typedef typename pass_by_value<Function>::type fun_t;
        typedef zip_with_range<RangeTuple, fun_t> const type;
    };

    template< class Result, class RangeTuple, class Function >
    Result call(RangeTuple& tup, Function& fun) const
    {
        return Result(tup, fun);
    }
};


PSTADE_CONSTANT(make_zip_with_range, op_make_zip_with_range)
PSTADE_PIPABLE(zipped_with, op_make_zip_with_range)


} } // namespace pstade::oven


#endif
