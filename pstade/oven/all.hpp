#ifndef PSTADE_OVEN_ALL_HPP
#define PSTADE_OVEN_ALL_HPP
#include "./detail/prefix.hpp"


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
#include <pstade/egg/not.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"


namespace pstade { namespace oven {


struct T_all
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
        return std::find_if(first, last, egg::not_(pred)) == last;
    }
};


PSTADE_POD_CONSTANT((T_all), all) = {};


} } // namespace pstade::oven


#endif
