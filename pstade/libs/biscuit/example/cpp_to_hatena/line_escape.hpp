#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_LINE_ESCAPE_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_LINE_ESCAPE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range.hpp>

#include <pstade/biscuit/action.hpp>
#include <pstade/biscuit/algorithm.hpp>
#include <pstade/biscuit/parser.hpp>

#include "./act_as_is.hpp"
#include "./character_escape.hpp"
#include "./hatena_mode.hpp"


namespace cpp_to_hatena {


using namespace pstade;
using namespace pstade::biscuit;
using pstade::biscuit::plus; // workaround for VC8


// program-size-optimization test
typedef no_captures< star< space_com > > spaces;


struct act_wrap_line
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        if (biscuit::match< spaces >(rng)) {
            biscuit::match< iteration<character_escape, act_as_is> >(rng, out);
            return;
        }

        if (is_hatena_mode())
            oven::copy("[]", out);

        biscuit::match< iteration<character_escape, act_as_is> >(rng, out);

        if (is_hatena_mode())
            oven::copy("[]", out);
    }
};


// line_escape
//
struct line_escape_ :
    seq<
        actor<line, act_wrap_line>,
        actor<eol, act_as_is >
    >
{ };


// program-size-optimization test
typedef no_captures<line_escape_> line_escape;


// act_line_escape
//
struct act_line_escape
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        biscuit::match< iteration<line_escape, pigs_fly> >(rng, out);
    }
};


} // namespace poost


#endif
