#ifndef PSTADE_OVEN_SORTED_HPP
#define PSTADE_OVEN_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // sort
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./indirected.hpp"
#include "./outplaced.hpp"


namespace pstade { namespace oven {


struct op_make_sorted :
    callable<op_make_sorted>
{
    template< class Myself, class Range, class Compare = op_less const >
    struct apply :
        boost::result_of<
            op_make_indirected<>(
                typename boost::result_of<op_make_outplaced(Range&)>::type
            )
        >
    { };

    template< class Result, class Range, class Compare >
    Result call(Range& rng, Compare& comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        typename boost::result_of<op_make_outplaced(Range&)>::type its = make_outplaced(rng);
        std::sort(boost::begin(its), boost::end(its), boost::make_indirect_fun(comp));
        return make_indirected(its);
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_CONSTANT(make_sorted, (op_make_sorted))
PSTADE_PIPABLE(sorted, (op_make_sorted))


} } // namespace pstade::oven


#endif
