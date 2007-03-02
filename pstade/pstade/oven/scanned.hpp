#ifndef PSTADE_OVEN_SCANNED_HPP
#define PSTADE_OVEN_SCANNED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_single.hpp"
#include "./concepts.hpp"
#include "./dropped.hpp"
#include "./front_back.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./range_iterator.hpp"
#include "./scan_iterator.hpp"


namespace pstade { namespace oven {


namespace scanned_detail {


    struct op_make :
        callable<op_make>
    {
        template< class Myself, class Range, class State, class BinaryFun >
        struct apply
        {
            typedef
                scan_iterator<
                    typename range_iterator<Range>::type,
                    typename pass_by_value<State>::type,
                    typename pass_by_value<BinaryFun>::type
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range, class State, class BinaryFun >
        Result call(Range& rng, State& init, BinaryFun& fun) const
        {
            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng), init, fun),
                iter_t(boost::end(rng),   init, fun)
            );
        }
    };


} // namespace scanned_detail


struct op_make_scanned :
    callable<op_make_scanned>
{
    template< class Myself, class Range, class State, class BinaryFun = void >
    struct apply :
        boost::result_of<
            op_make_jointed(
                typename boost::result_of<op_as_shared_single(State const *)>::type,
                typename boost::result_of<scanned_detail::op_make(Range&, State&, BinaryFun&)>::type
            )
        >
    { };

    template< class Result, class Range, class State, class BinaryFun >
    Result call(Range& rng, State const& init, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        // Prefer const-qualified 'State';
        // It's common that 'rng' is constant but 'init' isn't 'const'.
        // As 'scan_iterator' is constant, 'make_jointed' won't work in such case.
        return make_jointed(
            as_shared_single(new State const(init)),
            scanned_detail::op_make()(rng, init, fun)
        );
    }

    template< class Myself, class Range, class BinaryFun >
    struct apply<Myself, Range, BinaryFun> :
        boost::result_of<
            op_make_scanned(
                typename boost::result_of<op_make_dropped(Range&, int)>::type,
                typename boost::result_of<op_value_front(Range&)>::type,
                BinaryFun&
            )
        >
    { };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        BOOST_ASSERT(!boost::empty(rng));
        return (*this)(make_dropped(rng, 1), value_front(rng), fun);
    }
};


PSTADE_CONSTANT(make_scanned, (op_make_scanned))
PSTADE_PIPABLE(scanned, (op_make_scanned))


} } // namespace pstade::oven


#endif
