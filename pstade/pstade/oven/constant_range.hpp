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
#include <pstade/egg/function.hpp>
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
            identity_fun,
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


namespace constant_range_detail {


    struct baby_make
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


} // namespace constant_range_detail


PSTADE_EGG_FUNCTION(make_constant_range, constant_range_detail::baby_make)
PSTADE_PIPABLE(constants, make_constant_range_fun)


} } // namespace pstade::oven


#endif
