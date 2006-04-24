#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_CHARACTER_EXCAPE_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_CHARACTER_EXCAPE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm>
#include <vector>
#include <boost/range.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/oven/copy.hpp>


namespace cpp_to_hatena {


using namespace pstade;
using namespace pstade::biscuit;


// actions
//

struct act_escape_amp
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&amp;", out); }
};

struct act_escape_lt
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&lt;", out); }
};

struct act_escape_gt
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&gt;", out); }
};

struct act_escape_quot
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&quot;", out); }
};

struct act_escape_lsb
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&#91;", out); }
};

struct act_escape_rsb
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&#93;", out); }
};

struct act_escape_ops
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&#40;&#40;", out); }
};

struct act_escape_cps
{
    template< class Range, class Out >
    void operator()(Range&, Out& out) const { oven::copy("&#41;&#41;", out); }
};


struct character_escape_ :
    or_<
        // xml
        actor< chseq<'&'>,      act_escape_amp >,
        actor< chseq<'<'>,      act_escape_lt >,
        actor< chseq<'>'>,      act_escape_gt >,
        actor< chseq<'"'>,      act_escape_quot >,

        // hatena specific
        actor< chseq<'['>,      act_escape_lsb >,
        actor< chseq<']'>,      act_escape_rsb >,
        actor< chseq<'(','('>,  act_escape_ops >,
        actor< chseq<')',')'>,  act_escape_cps >
    >
{ };


// program-size-optimization test
typedef no_captures<character_escape_> character_escape;


} // namespace cpp_to_hatena


#endif
