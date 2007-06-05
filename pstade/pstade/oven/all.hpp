#ifndef PSTADE_OVEN_ALL_HPP
#define PSTADE_OVEN_ALL_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Pavol Droba, all, Proposal for new string algorithms in TR2, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html
// [2] all, Boost.Wiki, 2004.
//     http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?STLAlgorithmExtensions/AllAlgorithm


#include <algorithm> // find_if
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // not_
#include "./concepts.hpp"


namespace pstade { namespace oven {


struct op_all
{
    typedef bool result_type;

    template< class Range, class UnaryPred >
    bool operator()(Range const& rng, UnaryPred pred) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return aux(boost::begin(rng), boost::end(rng), pred);
    }

    template< class Iterator, class UnaryPred >
    bool aux(Iterator first, Iterator last, UnaryPred pred) const
    {
        return std::find_if(first, last, not_(pred)) == last;
    }
};


PSTADE_CONSTANT(all, (op_all))


} } // namespace pstade::oven


#endif
