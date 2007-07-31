#ifndef PSTADE_OVEN_PARALLEL_REDUCE_HPP
#define PSTADE_OVEN_PARALLEL_REDUCE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See acfunanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric> // accumulate
#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // next
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./detail/simple_parallel.hpp"
#include "./range_value.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace parallel_reduce_detail {


    template< class Value, class BinaryFun >
    struct algo
    {
        template< class Difference, class Iterator >
        algo make_right(Difference grain, Iterator firstR, Iterator lastR) const
        {
            unused(grain, lastR);
            return algo(read(firstR), m_fun);
        }

        template< class Iterator >
        void before_join(Iterator first, Iterator last)
        {
            BOOST_ASSERT(first != last);
            m_value = std::accumulate(boost::next(first), last, m_value, m_fun);
        }

        template< class Iterator >
        void after_join(Iterator first, Iterator last, Iterator firstR, Iterator lastR, algo const& right)
        {
            unused(first, last, firstR, lastR);
            m_value = m_fun(m_value, right.value());
        }

        algo(Value init, BinaryFun fun) :
            m_value(init), m_fun(fun)
        { }

        Value value() const
        {
            return m_value;
        }

    private:
        Value m_value;
        BinaryFun m_fun;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class BinaryFun = egg::op_plus const >
        struct apply :
            range_value<Range>
        { };

        template< class Result, class Difference, class Range, class BinaryFun >
        Result call(Difference grain, Range& rng, BinaryFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(!boost::empty(rng));
            return detail::simple_parallel(grain, rng,
                algo<typename range_value<Range>::type, BinaryFun>(read(boost::begin(rng)), fun)
            ).algo().value();
        }

        template< class Result, class Difference, class Range >
        Result call(Difference grain, Range& rng) const
        {
            return egg::make_function(*this)(grain, rng, egg::plus);
        }
    };


} // namespace parallel_reduce_detail


typedef egg::function<parallel_reduce_detail::baby> op_parallel_reduce;
PSTADE_POD_CONSTANT((op_parallel_reduce), parallel_reduce) = {{}};


} } // namespace pstade::oven


#endif
