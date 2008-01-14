#ifndef PSTADE_LIME_XML_HPP
#define PSTADE_LIME_XML_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.w3.org/TR/2004/REC-xml-20040204/


#include <pstade/biscuit/action/null_action.hpp>
#include <pstade/biscuit/parser/actor.hpp>
#include <pstade/biscuit/parser/directive/lazy_actions.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include <pstade/biscuit/parser/primitive/bchseq.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/primitive/chset.hpp>
#include <pstade/biscuit/parser/minus.hpp>
#include <pstade/biscuit/parser/not.hpp>
#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include <pstade/biscuit/parser/star_before.hpp>
#include <pstade/biscuit/parser/star_until.hpp>
#include <pstade/ustring.hpp> // ucs4_t


namespace pstade { namespace lime { namespace xml {


    struct Char :
        biscuit::or_<
            biscuit::bchseq<ucs4_t, 0x9>,
            biscuit::bchseq<ucs4_t, 0xA>,
            biscuit::bchseq<ucs4_t, 0xD>,
            biscuit::bchrng<ucs4_t, 0x20, 0xD7FF>,
            biscuit::bchrng<ucs4_t, 0xE000, 0xFFFD>,
            biscuit::bchrng<ucs4_t, 0x10000, 0x10FFFF>
        >
    { };


    struct CharData :
        biscuit::minus<
            biscuit::star<
                biscuit::not_< biscuit::chset<'<','&'> >
            >,
            biscuit::seq<
                biscuit::star_until<
                    biscuit::not_< biscuit::chset<'<','&'> >,
                    biscuit::chseq<']',']','>'>
                >,
                biscuit::star<
                    biscuit::not_< biscuit::chset<'<','&'> > 
                >
            >
        >
    { };


    struct Comment :
        biscuit::seq<
            biscuit::chseq<'<','!','-','-'>,
            biscuit::star<
                biscuit::or_<
                    biscuit::minus<
                        Char,
                        biscuit::chseq<'-'>
                    >,
                    biscuit::seq<
                        biscuit::chseq<'-'>,
                        biscuit::minus<
                            Char,
                            biscuit::chseq<'-'>
                        >
                    >
                >
            >,
            biscuit::chseq<'-','-','>'>
        >
    { };


    struct S :
        biscuit::plus< biscuit::chset<0x20,0x9,0xD,0xA> >
    { };


    struct Digit :
        biscuit::or_<
            biscuit::bchrng<ucs4_t, 0x0030, 0x0039>,
            biscuit::bchrng<ucs4_t, 0x0660, 0x0669>

            // todo
            //

        >
    { };


    struct BaseChar :
        biscuit::or_<
            biscuit::bchrng<ucs4_t, 0x0041, 0x005A>,
            biscuit::bchrng<ucs4_t, 0x0061, 0x007A>
        >
    { };


    struct Ideographic :
        biscuit::or_<
            biscuit::bchrng<ucs4_t, 0x4E00, 0x9FA5>,
            biscuit::bchseq<ucs4_t, 0x3007>,
            biscuit::bchrng<ucs4_t, 0x3021, 0x3029>
        >
    { };


    struct CombiningChar :
        biscuit::or_<
            biscuit::bchrng<ucs4_t, 0x0300, 0x0345>,
            biscuit::bchrng<ucs4_t, 0x0360, 0x0361>

            // todo
            //

        >
    { };


    struct Extender :
        biscuit::or_<
            biscuit::bchseq<ucs4_t, 0x00B7>, biscuit::bchseq<ucs4_t, 0x02D0>,
            biscuit::bchseq<ucs4_t, 0x02D1>, biscuit::bchseq<ucs4_t, 0x0387>

            // todo
            //

        >
    { };


    struct Letter:
        biscuit::or_<
            BaseChar,
            Ideographic
        >
    { };


    struct NameChar :
        biscuit::or_<
            Letter,
            Digit,
            biscuit::chseq<'.'>, biscuit::chseq<'-'>,
            biscuit::chseq<'_'>, biscuit::chseq<':'>,
            CombiningChar,
            Extender
        >
    { };


    struct Name :
        biscuit::seq<
            biscuit::or_<
                Letter,
                biscuit::chseq<'_'>,
                biscuit::chseq<':'>
            >,
            biscuit::star<
                NameChar
            >
        >
    { };


    struct Eq :
        biscuit::seq<
            biscuit::opt<S>,
            biscuit::chseq<'='>,
            biscuit::opt<S>
        >
    { };


    struct PITarget :
        biscuit::minus<
            Name,
            biscuit::seq<
                biscuit::or_< biscuit::chseq<'X'>, biscuit::chseq<'x'> >,
                biscuit::or_< biscuit::chseq<'M'>, biscuit::chseq<'m'> >,
                biscuit::or_< biscuit::chseq<'L'>, biscuit::chseq<'l'> >
            >
        >
    { };


    struct PI :
        biscuit::seq<
            biscuit::chseq<'<','?'>,
            PITarget,
            biscuit::opt<
                biscuit::seq<
                    S,
                    biscuit::star_before<
                        Char,
                        biscuit::chseq<'?','>'>
                    > 
                >
            >,
            biscuit::chseq<'?','>'>
        >
    { };


    struct CDStart :
        biscuit::chseq<'<','!','[','C','D','A','T','A','['>
    { };


    struct CData :
        biscuit::star_before<
            Char,
            biscuit::chseq<']',']','>'>
        >
    { };


    struct CDEnd :
        biscuit::chseq<']',']','>'>
    { };


    struct CDSect :
        biscuit::seq<CDStart, CData, CDEnd>
    { };


    struct doctypedecl :
        biscuit::seq<
            biscuit::chseq<'<','!','D','O','C','T','Y','P','E'>,
            biscuit::star_until<
                Char,
                biscuit::chseq<'>'>
            >
        >
    { };


    struct XMLDecl :
        biscuit::seq<
            biscuit::chseq<'<','?','x','m','l'>,
            biscuit::star_until<
                Char,
                biscuit::chseq<'?','>'>
            >
        >
    { };


    struct Misc :
        biscuit::or_<Comment, PI, S>
    { };


    struct prolog :
        biscuit::seq<
            biscuit::opt<XMLDecl>,
            biscuit::star<Misc>,
            biscuit::opt<
                biscuit::seq<doctypedecl, Misc>
            >
        >
    { };


    struct CharRef :
        biscuit::or_<
            biscuit::seq<
                biscuit::chseq<'&','#'>,
                biscuit::plus< biscuit::chrng<'0','9'> >,
                biscuit::chseq<';'>
            >,
            biscuit::seq<
                biscuit::chseq<'&','#','x'>,
                biscuit::plus<
                    biscuit::or_<
                        biscuit::chrng<'0','9'>,
                        biscuit::chrng<'a','f'>,
                        biscuit::chrng<'A','F'>
                    >
                >,
                biscuit::chseq<';'>
            >
        >
    { };


    struct EntityRef :
        biscuit::seq<
            biscuit::chseq<'&'>,
            Name,
            biscuit::chseq<';'>
        >
    { };


    struct Reference :
        biscuit::or_<EntityRef, CharRef>
    { };


    struct AttValue :
        biscuit::or_<
            biscuit::seq<
                biscuit::chseq<'"'>,
                biscuit::star<
                    biscuit::or_<
                        biscuit::not_< biscuit::chset<'<','&','"'> >,
                        Reference
                    >
                >,
                biscuit::chseq<'"'>
            >,
            biscuit::seq<
                biscuit::chseq<'\''>,
                biscuit::star<
                    biscuit::or_<
                        biscuit::not_< biscuit::chset<'<','&','\''> >,
                        Reference
                    >
                >,
                biscuit::chseq<'\''>
            >
        >
    { };


    template<
        class On_AttName,
        class On_AttValue
    >
    struct Attribute :
        biscuit::seq<
            biscuit::actor< Name, On_AttName >,
            Eq,
            biscuit::actor< AttValue, On_AttValue >
        >
    { };


    template<
        class On_TagName,
        class On_AttName,
        class On_AttValue
    >
    struct EmptyElemTag :
        biscuit::seq<
            biscuit::chseq<'<'>,
            biscuit::actor< Name, On_TagName >,
            biscuit::star<
                biscuit::seq<
                    S,
                    Attribute<On_AttName, On_AttValue>
                >
            >,
            biscuit::opt<S>,
            biscuit::chseq<'/','>'>
        >
    { };


    template<
        class On_TagName,
        class On_AttName,
        class On_AttValue
    >
    struct STag :
        biscuit::seq<
            biscuit::chseq<'<'>,
            biscuit::actor< Name, On_TagName >,
            biscuit::star<
                biscuit::seq<
                    S,
                    Attribute<On_AttName, On_AttValue>
                >
            >,
            biscuit::opt<S>,
            biscuit::chseq<'>'>
        >
    { };


    struct ETag:
        biscuit::seq<
            biscuit::chseq<'<','/'>,
            Name,
            biscuit::opt<S>,
            biscuit::chseq<'>'>
        >
    { };


    template<
        class content_,
        class On_TagName,
        class On_AttName,
        class On_AttValue,
        class On_ETag,
        class On_CharData,
        class On_Rerefence
    >
    struct element :
        biscuit::or_<
            biscuit::lazy_actions<
                biscuit::seq<
                    EmptyElemTag<On_TagName, On_AttName, On_AttValue>,
                    biscuit::actor< biscuit::eps, On_ETag >
                >
            >,
            biscuit::seq<
                STag<On_TagName, On_AttName, On_AttValue>,
                content_,
                biscuit::actor< ETag, On_ETag >
            >
        >
    { };


    template<
        class element_,
        class On_CharData,
        class On_Reference
    >
    struct content :
        biscuit::seq<
            biscuit::opt<
                biscuit::actor< CharData, On_CharData >
            >,
            biscuit::star<
                biscuit::seq<
                    biscuit::or_<
                        element_, // the magical recursion!
                        biscuit::actor< Reference, On_Reference >,
                        CDSect,
                        PI,
                        Comment
                    >,
                    biscuit::opt<
                        biscuit::actor< CharData, On_CharData >
                    >
                >
            >
        >
    { };


    template<
        class element_
    >
    struct document :
        biscuit::seq<
            prolog,
            element_,
            biscuit::star<Misc>
        >
    { };


    template<
        class On_TagName    = biscuit::null_action,
        class On_AttName    = biscuit::null_action,
        class On_AttValue   = biscuit::null_action,
        class On_ETag       = biscuit::null_action,
        class On_CharData   = biscuit::null_action,
        class On_Reference  = biscuit::null_action
    >
    struct parser
    {
        struct element_ : element<
            content<element_, On_CharData, On_Reference>,
            On_TagName, On_AttName, On_AttValue, On_ETag,
            On_CharData, On_Reference
        >
        { };

        typedef document<element_> type;
    };


} } } // namespace pstade::lime::xml


#endif
