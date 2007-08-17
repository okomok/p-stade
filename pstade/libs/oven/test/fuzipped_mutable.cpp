#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/fuzipped.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/egg/tuple/pack.hpp> // tuple_pack
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copied.hpp>


#include <boost/fusion/sequence/adapted/boost_tuple.hpp>
#include <boost/fusion/sequence/comparison.hpp> // DON'T FORGET for Readable test
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/generation/vector_tie.hpp>


template<class Iterator>
void check_mutable(Iterator it)
{
    BOOST_MPL_ASSERT((boost::is_same<typename boost::iterator_reference<Iterator>::type, int>));
}


void pstade_minimal_test()
{
    using namespace pstade::oven;

    {
        // tuple contains value.
        std::string src0;
        std::vector<int> src1;

        boost::fusion::vector< std::string, std::vector<int> > z(src0, src1);
        ::check_mutable(make_fuzipped(z).begin());

        BOOST_FOREACH (
            PSTADE_UNPARENTHESIZE((boost::fusion::vector2<char&, int&>)) t,
            z|fuzipped
        ) {
        }
    }
}
