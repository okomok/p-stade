#ifndef PSTADE_OVEN_SCANNED_HPP
#define PSTADE_OVEN_SCANNED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // plus
#include <pstade/pipable.hpp>
#include "./as_single.hpp"
#include "./begin_end.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./scan_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_scanned :
    callable<op_make_scanned>
{
    // Prefer const-qualified 'State';
    // It's common that 'rng' is constant but 'init' isn't 'const'.
    // As 'scan_iterator' is constant, 'make_jointed' won't work in such case.
    template< class Myself, class Range, class State, class BinaryFun = op_plus const >
    struct apply :
        boost::result_of<
            op_make_jointed(
                typename boost::result_of<
                    op_as_shared_single(State const *)
                >::type,
                typename boost::result_of<
                    op_make_iter_range(
                        typename boost::result_of<
                            op_make_scan_iterator(typename boost::result_of<op_begin(Range&)>::type, State const&, BinaryFun&)
                        >::type,
                        typename boost::result_of<
                            op_make_scan_iterator(typename boost::result_of<op_end(Range&)>::type, State const&, BinaryFun&)
                        >::type
                    )
                >::type
            )
        >
    { };

    template< class Result, class Range, class State, class BinaryFun >
    Result call(Range& rng, State const& init, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        return
            make_jointed(
                as_shared_single(new State const(init)),
                make_iter_range(
                    make_scan_iterator(begin(rng), init, fun),
                    make_scan_iterator(end(rng), init, fun)
                )
            );
    }

    template< class Result, class Range, class State >
    Result call(Range& rng, State& init) const
    {
        return (*this)(rng, init, plus);
    }
};


PSTADE_CONSTANT(make_scanned, (op_make_scanned))
PSTADE_PIPABLE(scanned, (op_make_scanned))


} } // namespace pstade::oven


#endif
