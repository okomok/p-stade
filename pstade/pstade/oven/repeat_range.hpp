#ifndef PSTADE_OVEN_REPEAT_RANGE_HPP
#define PSTADE_OVEN_REPEAT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <pstade/base_from.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./cycle_range.hpp"
#include "./single_range.hpp"


namespace pstade { namespace oven {


namespace repeat_range_detail {


    template< class Value >
    struct init_single :
        base_from< single_range<Value> >
    { };


    template< class Value, class Size >
    struct super_
    {
        typedef cycle_range< single_range<Value>, Size > type;
    };


} // namespace repeat_range_detail


template<
    class Value,
    class Size = std::size_t
>
struct repeat_range :
    private repeat_range_detail::init_single<Value>::type,
    repeat_range_detail::super_<Value, Size>::type,
    private as_lightweight_proxy< repeat_range<Value, Size> >
{
private:
    typedef typename repeat_range_detail::init_single<Value>::type init_t;
    typedef typename init_t::member_type single_t;
    typedef typename repeat_range_detail::super_<Value, Size>::type super_t;

public:
    repeat_range(Value& v, Size sz) :
        init_t(single_t(v)),
        super_t(init_t::member, sz)
    { }
};


namespace repeat_range_detail {


    struct baby_make
    {
        template< class Myself, class Value, class Size >
        struct apply
        {
            typedef typename pass_by_value<Size>::type sz_t;
            typedef repeat_range<Value, sz_t> const type;
        };

        template< class Result, class Value, class Size >
        Result call(Value& v, Size sz)
        {
            return Result(v, sz);
        }
    };


} // namespace repeat_range_detail


PSTADE_EGG_FUNCTION(make_repeat_range, repeat_range_detail::baby_make)
PSTADE_EGG_PIPABLE(repeated, repeat_range_detail::baby_make)


} } // namespace pstade::oven


#endif
