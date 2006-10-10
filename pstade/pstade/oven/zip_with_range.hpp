#ifndef PSTADE_OVEN_ZIP_WITH_RANGE_HPP
#define PSTADE_OVEN_ZIP_WITH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_base.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace zip_with_range_detail {


    template<
        class Range0, class Range1,
        class BinaryFun
    >
    struct with_fun
    {
        typedef typename range_reference<Range0>::type ref0_t;
        typedef typename range_reference<Range1>::type ref1_t;

        typedef typename boost::result_of<BinaryFun(ref0_t, ref1_t)>::type
        result_type;

        explicit with_fun() // must be DefaultConstructible to be ForwardIterator.
        { }

        explicit with_fun(BinaryFun const& fun) :
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


    template<
        class Range0, class Range1,
        class BinaryFun,
        class Reference,
        class Value
    >
    struct super_
    {
        typedef transform_range<
            zip_range<Range0, Range1> const,
            with_fun<Range0, Range1, BinaryFun>,
            Reference,
            Value
        > type;
    };


} // namespace zip_with_range_detail


template<
    class Range0, class Range1,
    class BinaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct zip_with_range :
    zip_with_range_detail::super_<Range0, Range1, BinaryFun, Reference, Value>::type,
    private as_lightweight_proxy< zip_with_range<Range0, Range1, BinaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range0>));
    PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
    typedef BinaryFun function_type;

private:
    typedef typename zip_with_range_detail::super_<Range0, Range1, BinaryFun, Reference, Value>::type super_t;
    typedef typename range_base<super_t>::type base_t;
    typedef typename super_t::function_type fun_t;

public:
    zip_with_range(Range0& rng0, Range1& rng1, BinaryFun const& fun) :
        super_t(base_t(rng0, rng1), fun_t(fun))
    { }

    typedef Range0 pstade_oven_range_base_type;
};


namespace zip_with_range_detail {


    struct baby_make
    {
        template< class Myself, class Range0, class Range1, class BinaryFun >
        struct apply
        {
            typedef typename pass_by_value<BinaryFun>::type fun_t;
            typedef zip_with_range<Range0, Range1, fun_t> const type;
        };

        template< class Result, class Range0, class Range1, class BinaryFun >
        Result call(Range0& rng0, Range1& rng1, BinaryFun& fun)
        {
            return Result(rng0, rng1, fun);
        }
    };


} // namespace zip_with_range_detail


PSTADE_EGG_FUNCTION(make_zip_with_range, zip_with_range_detail::baby_make)
PSTADE_EGG_PIPABLE(zipped_with, zip_with_range_detail::baby_make)


} } // namespace pstade::oven


#endif
