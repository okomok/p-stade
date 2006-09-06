#ifndef PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_CPP_TOKEN_HPP
#define PSTADE_LIBS_BISCUIT_EXAMPLE_CPP_TO_HATENA_CPP_TOKEN_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>


namespace cpp_to_hatena { namespace cpp_token {


using namespace pstade;
using namespace pstade::biscuit;
using pstade::biscuit::plus; // VC8 bug workaround


namespace detail {


    struct keyword_aux0 :
        or_<
            chseq<'B','O','O','S','T','_','F','O','R','E','A','C','H'>,
            chseq<'a','n','d','_','e','q'>,
            chseq<'a','n','d'>,
            chseq<'a','s','m'>,
            chseq<'a','u','t','o'>,
            chseq<'b','i','t','a','n','d'>,
            chseq<'b','i','t','o','r'>,
            chseq<'b','o','o','l'>,
            chseq<'b','r','e','a','k'>,
            chseq<'c','a','s','e'>,
            chseq<'c','a','t','c','h'>,
            chseq<'c','h','a','r'>,
            chseq<'c','l','a','s','s'>,
            chseq<'c','o','m','p','l'>,
            chseq<'c','o','n','s','t','_','c','a','s','t'>,
            chseq<'c','o','n','s','t'>,
            chseq<'c','o','n','t','i','n','u','e'>,
            chseq<'d','e','f','a','u','l','t'>,
            chseq<'d','e','l','e','t','e'>,
            chseq<'d','o','u','b','l','e'>
        >
    { };

    struct keyword_aux1 :
        or_<
            chseq<'d','o'>,
            chseq<'d','y','n','a','m','i','c','_','c','a','s','t'>,
            chseq<'e','l','s','e'>,
            chseq<'e','n','u','m'>,
            chseq<'e','x','p','l','i','c','i','t'>,
            chseq<'e','x','p','o','r','t'>,
            chseq<'e','x','t','e','r','n'>,
            chseq<'f','a','l','s','e'>,
            chseq<'f','l','o','a','t'>,
            chseq<'f','o','r'>,
            chseq<'f','r','i','e','n','d'>,
            chseq<'g','o','t','o'>,
            chseq<'i','f'>,
            chseq<'i','n','l','i','n','e'>,
            chseq<'i','n','t'>,
            chseq<'l','o','n','g'>,
            chseq<'m','u','t','a','b','l','e'>,
            chseq<'n','a','m','e','s','p','a','c','e'>,
            chseq<'n','e','w'>,
            chseq<'n','o','t','_','e','q'>
        >
    { };

    struct keyword_aux2 :
        or_<
            chseq<'n','o','t'>,
            chseq<'o','p','e','r','a','t','o','r'>,
            chseq<'o','r','_','e','q'>,
            chseq<'o','r'>,
            chseq<'p','r','i','v','a','t','e'>,
            chseq<'p','r','o','t','e','c','t','e','d'>,
            chseq<'p','u','b','l','i','c'>,
            chseq<'r','e','g','i','s','t','e','r'>,
            chseq<'r','e','i','n','t','e','r','p','r','e','t','_','c','a','s','t'>,
            chseq<'r','e','t','u','r','n'>,
            chseq<'s','h','o','r','t'>,
            chseq<'s','i','g','n','e','d'>,
            chseq<'s','i','z','e','o','f'>,
            chseq<'s','t','a','t','i','c','_','c','a','s','t'>,
            chseq<'s','t','a','t','i','c'>,
            chseq<'s','t','r','u','c','t'>,
            chseq<'s','w','i','t','c','h'>,
            chseq<'t','e','m','p','l','a','t','e'>,
            chseq<'t','h','i','s'>,
            chseq<'t','h','r','o','w'>
        >
    { };

    struct keyword_aux3 :
        or_<
            chseq<'t','r','u','e'>,
            chseq<'t','r','y'>,
            chseq<'t','y','p','e','d','e','f'>,
            chseq<'t','y','p','e','i','d'>,
            chseq<'t','y','p','e','n','a','m','e'>,
            chseq<'u','n','i','o','n'>,
            chseq<'u','n','s','i','g','n','e','d'>,
            chseq<'u','s','i','n','g'>,
            chseq<'v','i','r','t','u','a','l'>,
            chseq<'v','o','i','d'>,
            chseq<'v','o','l','a','t','i','l','e'>,
            chseq<'w','c','h','a','r','_','t'>,
            chseq<'w','h','i','l','e'>,
            chseq<'x','o','r','_','e','q'>,
            chseq<'x','o','r'>
        >
    { };

    struct alnum_ :
        or_< alnum_com, chseq<'_'> >
    { };

    struct keyword_aux :
        or_< keyword_aux0, keyword_aux1, keyword_aux2, keyword_aux3 >
    { };


} // namespace detail


struct keyword :
    seq<
        // after< not_< alnum_ > > // 'after' parser is impossible for Biscuit, so 'identifier' is required.
        detail::keyword_aux,
        before< not_< detail::alnum_ > >
    >
{ };

struct cpp_comment :
    seq< chseq<'/','/'>, star_before< any, or_<eol> > >
{ };

struct c_comment :
    seq< chseq<'/','*'>, star_until< any, chseq<'*','/'> > >
{ };

struct comment :
    or_< c_comment, cpp_comment >
{ };

struct string_literal :
    seq<
        seq<
            chseq<'"'>,
            star<
                or_<
                    seq< chseq<'\\'>, any >,
                    not_< chseq<'"'> >
                >
            >
        >,
        chseq<'"'>
    >
{ };

struct character_literal :
    seq<
        seq<
            chseq<'\''>,
            star<
                or_<
                    seq< chseq<'\\'>, any >,
                    not_< chseq<'\''> >
                >
            >,
            chseq<'\''>
        >
    >
{ };

struct real_literal :
    seq<
        opt< chset<'+','-'> >,
        or_<
            seq< plus<digit_com>, chseq<'.'>, plus<digit_com> >,
            seq< plus<digit_com>, chseq<'.'> >,
            seq< chseq<'.'>, plus<digit_com> >,
            plus<digit_com>
        >,
        opt<
            seq<
                chset<'e','E'>,
                opt< chset<'+','-'> >,
                plus<digit_com>
            >
        >
    >
{ };

struct hex_literal :
    plus<
        or_< chrng<'0','9'>, chrng<'a','f'>, chrng<'A','F'> >
    >
{ };

struct oct_literal :
    plus<
        chrng<'0','7'>
    >
{ };

struct number_literal :
    seq<
        or_<
            seq< ichseq<'0','x'>, hex_literal >,
            seq< chseq<'0'>, oct_literal >,
            real_literal // must be last, can eat only '0'
        >,
        star< ichset<'u','l','f'> >
    >
{ };

struct identifier :
    seq<
        or_< alpha_com, chseq<'_'> >,
        star< or_< alnum_com, chseq<'_'> > >
    >
{ };

struct pp_directive :
    seq<
        chseq<'#'>,
        star<space_com>,
        identifier
    >
{ };

struct pp_include_directive :
    seq<
        chseq<'#'>,
        star<space_com>,
        chseq<'i','n','c','l','u','d','e'>
    >
{ };

struct pp_include_path :
    or_<
        seq< chseq<'"'>, star_until< any, chseq<'"'> > >,
        seq< chseq<'<'>, star_until< any, chseq<'>'> > >
    >
{ };

struct pp_null_directive :
    seq<
        chseq<'#'>,
        star_before< space_com, or_< eol, chseq<'/'> > >
    >
{ };


struct pp_special :
    chseq<'#','#'>
{ };


} } // namespace cpp_to_hatena::cpp_token


#endif
