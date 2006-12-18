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
#include <pstade/fuse.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
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
            typename boost::result_of<op_fuse(Function const&)>::type,
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
    typedef zip_with_range type;
    typedef RangeTuple range_tuple_type;

private:
    typedef typename zip_with_range_detail::super_<RangeTuple, Function, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;

public:
    zip_with_range(RangeTuple& tup, Function const& fun) :
        super_t(base_t(tup), pstade::fuse(fun))
    { }
};


PSTADE_OBJECT_GENERATOR(make_zip_with_range,
    (zip_with_range< deduce<_1, to_qualified>, deduce<_2, to_value> >) const)
PSTADE_PIPABLE(zipped_with, (op_make_zip_with_range))


} } // namespace pstade::oven


#endif
