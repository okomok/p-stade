#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_ACT_AS_IS_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_ACT_AS_IS_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/algorithm.hpp> // copy


namespace cpp_to_hatena {


using namespace pstade;
using namespace pstade::biscuit;


struct act_as_is
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy(rng, out);
    }
};


} // namespace cpp_to_hatena


#endif
