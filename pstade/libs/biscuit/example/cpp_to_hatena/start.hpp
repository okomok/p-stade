#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_START_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_START_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/oven.hpp>
#include <pstade/unused.hpp>

#include "./act_as_is.hpp"
#include "./cpp_token.hpp"
#include "./line_escape.hpp"


namespace cpp_to_hatena {


using namespace pstade;
using namespace pstade::biscuit;


// actions
//
struct act_keyword
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_keyword\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};

struct act_string_literal
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_string_literal\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};

struct act_number_literal
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_number_literal\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};

struct act_identifier
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        pstade::unused(out);
        // oven::copy("<span class=\"cpp_identifier\">", out);
        act_line_escape()(rng, out);
        // oven::copy("</span>", out);
    }
};

struct act_comment
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_comment\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};

struct act_pp_directive
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_pp_directive\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};

struct act_pp_include_path
{
    template< class Range, class Out >
    void operator()(Range& rng, Out& out) const
    {
        oven::copy("<span class=\"cpp_pp_include_path\">", out);
        act_line_escape()(rng, out);
        oven::copy("</span>", out);
    }
};


// parsers
//
using namespace pstade::biscuit;

struct non_blanks : // suppress buffer overrun of VC7.1 compiler
    star< not_<blank_com> >
{ };

struct preprocessor :
    or_<
        actor< cpp_token::pp_special,                   act_line_escape >,    
        seq<
            actor< cpp_token::pp_include_directive,     act_pp_directive >,
            actor< star<space_com>,                     act_as_is >,
            actor< cpp_token::pp_include_path,          act_pp_include_path >
        >,
        seq<
            actor< cpp_token::pp_directive,             act_pp_directive >,
            actor< star_before<any, eol>,               act_line_escape >
        >,
        actor< cpp_token::pp_null_directive,            act_pp_directive >
    >
{ };

struct identifier_ :
    seq<
        or_< alpha_com, chseq<'_'> >,
        star< or_< any, chseq<'_'> > >
    >
{ };

struct start_ :
    or_<
        preprocessor,
        // add anything you want
        actor< cpp_token::comment,                      act_comment >,
        actor< cpp_token::keyword,                      act_keyword >,
        actor< cpp_token::string_literal,               act_string_literal >,
        actor< cpp_token::character_literal,            act_string_literal >,
        actor< cpp_token::number_literal,               act_number_literal >, 
        actor< cpp_token::identifier,                   act_identifier > // must be after keyword
    >
{ };


// program-size-optimization test
typedef no_captures<start_> start;


} // namespace cpp_to_hatena


#endif
