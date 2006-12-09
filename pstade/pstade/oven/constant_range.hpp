#ifndef PSTADE_OVEN_CONSTANT_RANGE_HPP
#define PSTADE_OVEN_CONSTANT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Should 'constant_range< std::vector<int> > crng(f,l);' be supported?


#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/constant_reference.hpp"
#include "./transform_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace constant_range_detail {


    template< class Range >
    struct super_
    {
        typedef transform_range<
            Range,
            op_identity,
            typename detail::constant_reference<
                typename range_iterator<Range>::type
            >::type
        > type;
    };


} // namespace constant_range_detail


template< class Range >
struct constant_range :
    constant_range_detail::super_<Range>::type,
    private as_lightweight_proxy< constant_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename constant_range_detail::super_<Range>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit constant_range(Range& rng) :
        super_t(rng, fun_t())
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_constant_range :
    callable<op_make_constant_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef constant_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_constant_range, op_make_constant_range)
PSTADE_PIPABLE(constants, op_make_constant_range)


} } // namespace pstade::oven


#endif
