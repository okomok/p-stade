#ifndef PSTADE_OVEN_ZIP_WITH_RANGE_HPP
#define PSTADE_OVEN_ZIP_WITH_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace zip_with_range_detail {


    template< class Range0, class Range1, class BinaryFun >
    struct transformer
    {
        typedef typename range_reference<Range0>::type ref0_t;
        typedef typename range_reference<Range1>::type ref1_t;

        typedef typename boost::result_of<BinaryFun(ref0_t, ref1_t)>::type
        result_type;

        explicit transformer(BinaryFun fun) :
            m_fun(fun)
        { }

        result_type operator()(boost::tuples::tuple<ref0_t, ref1_t> const& tup) const
        {
            using namespace boost;
            return m_fun(tuples::get<0>(tup), tuples::get<1>(tup));
        }

    private:
        BinaryFun m_fun;
    };


    template< class Range0, class Range1, class BinaryFun >
    struct super_
    {
        typedef transform_range<
            zip_range<Range0, Range1> const,
            transformer<Range0, Range1, BinaryFun>
        > type;
    };


} // namespace zip_with_range_detail


template< class Range0, class Range1, class BinaryFun >
struct zip_with_range :
    zip_with_range_detail::super_<Range0, Range1, BinaryFun>::type,
    private as_lightweight_proxy< zip_with_range<Range0, Range1, BinaryFun> >
{
    typedef Range0 pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range0, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range1, SinglePassRangeConcept);
    typedef typename zip_with_range_detail::super_<Range0, Range1, BinaryFun>::type super_t;

public:
    zip_with_range(Range0& rng0, Range1& rng1, BinaryFun fun) :
        super_t(
            zip_range<Range0, Range1>(rng0, rng1),
            zip_with_range_detail::transformer<Range0, Range1, BinaryFun>(fun)
        )
    { }
};


namespace zip_with_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range0, class Range1, class BinaryFun >
        struct result
        {
            typedef typename egg::decay_function<BinaryFun>::type fun_t;
            typedef zip_with_range<Range0, Range1, fun_t> const type;
        };

        template< class Result, class Range0, class Range1, class BinaryFun >
        Result call(Range0& rng0, Range1& rng1, BinaryFun fun)
        {
            return Result(rng0, rng1, fun);
        }
    };


} // namespace zip_with_range_detail


PSTADE_EGG_FUNCTION(make_zip_with_range, zip_with_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(zipped_with, zip_with_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
