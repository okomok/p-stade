#ifndef PSTADE_OVEN_GENERATE_RANGE_HPP
#define PSTADE_OVEN_GENERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'Range' traversal category can be changed to SinglePass ?


#include <boost/utility/result_of.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace generate_range_detail {


    template< class Generator >
    struct ignore_fun
    {
        typedef typename boost::result_of<Generator()>::type
        result_type;

        template< class T >
        result_type operator()(T const&) const
        {
            return m_gen();
        }

        explicit ignore_fun(Generator const& gen) :
            m_gen(gen)
        { }

    private:
        Generator m_gen;
    };


    template< class Range, class Generator >
    struct super_
    {
        typedef transform_range<
            Range, ignore_fun<Generator>
        > type;
    };


} // namespace generate_range_detail


template< class Range, class Generator >
struct generate_range :
    generate_range_detail::super_<Range, Generator>::type,
    private as_lightweight_proxy< generate_range<Range, Generator> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename generate_range_detail::super_<Range, Generator>::type super_t;

public:
    generate_range(Range& rng, Generator const& gen) :
        super_t(rng, generate_range_detail::ignore_fun<Generator>(gen))
    { }
};


namespace generate_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class Generator >
        struct result
        {
            typedef typename egg::by_value<Generator>::type gen_t;
            typedef generate_range<Range, gen_t> const type;
        };

        template< class Result, class Range, class Generator >
        Result call(Range& rng, Generator& gen)
        {
            return Result(rng, gen);
        }
    };


} // namespace generate_range_detail


PSTADE_EGG_FUNCTION(make_generate_range, generate_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(generated, generate_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
