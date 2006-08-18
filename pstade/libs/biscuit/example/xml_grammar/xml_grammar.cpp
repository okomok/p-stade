#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// works only under UTF8 files.


#include <iostream> // for cout
#include <iterator> // for back_inserter
#include <string>
#include <vector>
#include <boost/config.hpp> // BOOST_NO_STD_WSTRING
#include <boost/cstdint.hpp> // for uintXXX_t
#include <boost/range.hpp>


#include <pstade/biscuit.hpp>
#include <pstade/oven.hpp>
#include <pstade/require.hpp>


namespace xml_grammar
{
    using namespace pstade;
    using namespace biscuit;
    using biscuit::minus; // VC workaround
    using biscuit::plus;  // VC workaround

    typedef boost::uint32_t ucs4_t;

    struct Char :
        or_<
            bchseq<ucs4_t,0x9>, bchseq<ucs4_t,0xA>, bchseq<ucs4_t,0xD>,
            bchrng<ucs4_t,0x20,0xD7FF>,
            bchrng<ucs4_t,0xE000,0xFFFD>,
            bchrng<ucs4_t,0x10000,0x10FFFF>
        >
    { };

    struct CharData :
        minus<
            star< not_< chset<'<','&'> > >,
            seq<
                star_until< not_< chset<'<','&'> >, chseq<']',']','>'> >,
                star< not_< chset<'<','&'> > >
            >
        >
    { };

    // semantic action
    struct comment_action
    {
        template< class Range >
        void operator()(Range& rng, null_state_type)
        {
#if !defined(BOOST_NO_STD_WSTRING)
            std::wcout
                << "XML Comment: "
                << oven::copy_range<std::wstring>(rng)
                << std::endl;
#else
            pstade::unused(rng);
#endif
        }
    };

    struct Comment :
        actor<
            seq<
                chseq<'<','!','-','-'>,
                star<
                    or_<
                        minus< Char, chseq<'-'> >,
                        seq<
                            chseq<'-'>,
                            minus< Char, chseq<'-'> >
                        >
                    >
                >,
                chseq<'-','-','>'>
            >,
            comment_action
        >
    { };

    struct S :
        plus< chset<0x20,0x9,0xD,0xA> >
    { };

    struct Digit :
        or_<
            bchrng<ucs4_t,0x0030,0x0039>, bchrng<ucs4_t,0x0660,0x0669>
            // too many
        >
    { };

    struct BaseChar :
        or_<
            bchrng<ucs4_t,0x0041,0x005A>, bchrng<ucs4_t,0x0061,0x007A>
        >
    { };

    struct Ideographic :
        or_<
            bchrng<ucs4_t,0x4E00,0x9FA5>, bchseq<ucs4_t,0x3007>,
            bchrng<ucs4_t,0x3021,0x3029>
        >
    { };

    struct CombiningChar :
        or_<
            bchrng<ucs4_t,0x0300,0x0345>, bchrng<ucs4_t,0x0360,0x0361>
            // too many
        >
    { };

    struct Extender :
        or_<
            bchseq<ucs4_t,0x00B7>, bchseq<ucs4_t,0x02D0>, bchseq<ucs4_t,0x02D1>, bchseq<ucs4_t,0x0387>
            // many
        >
    { };

    struct Letter :
        or_< BaseChar, Ideographic >
    { };

    struct NameChar :
        or_<
            Letter, Digit, chseq<'.'>, chseq<'-'>, chseq<'_'>, chseq<':'>,
            CombiningChar, Extender
        >
    { };

    struct Name :
        seq<
            or_< Letter, chseq<'_'>, chseq<':'> >,
            star< NameChar >
        >
    { };

    struct Eq :
        seq< opt<S>, chseq<'='>, opt<S> >
    { };

    struct PITarget :
        minus<
            Name,
            seq<
                or_< chseq<'X'>, chseq<'x'> >,
                or_< chseq<'M'>, chseq<'m'> >,
                or_< chseq<'L'>, chseq<'l'> >
            >
        >
    { };
        
    struct PI :
        seq<
            chseq<'<','?'>,
            PITarget,
            opt<
                seq< S, star_before< Char, chseq<'?','>'> > >
            >,
            chseq<'?','>'>
        >
    { };

    struct CDStart :
        chseq<'<','!','[','C','D','A','T','A','['>
    { };

    struct CData :
        star_before< Char, chseq<']',']','>'> >
    { };

    struct CDEnd :
        chseq<']',']','>'>
    { };

    struct CDSect :
        seq< CDStart, CData, CDEnd >
    { };

    struct doctypedecl :
        seq<
            chseq<'<','!','D','O','C','T','Y','P','E'>,
            star_until< Char, chseq<'>'> >
        >
    { };

    struct XMLDecl :
        seq<
            chseq<'<','?','x','m','l'>,
            star_until< Char, chseq<'?','>'> >
        >
    { };

    struct Misc :
        or_< Comment, PI, S >
    { };

    struct prolog :
        seq<
            opt<XMLDecl>,
            star<Misc>,
            opt< seq< doctypedecl, star<Misc> > >
        >
    { };

    struct CharRef :
        or_<
            seq<
                chseq<'&','#'>,
                plus< chrng<'0','9'> >,
                chseq<';'>
            >,
            seq<
                chseq<'&','#','x'>,
                plus< or_< chrng<'0','9'>, chrng<'a','f'>, chrng<'A','F'> > >,
                chseq<';'>
            >
        >
    { };

    struct EntityRef :
        seq< chseq<'&'>, Name, chseq<';'> >
    { };

    struct Reference :
        or_<EntityRef, CharRef>
    { };

    struct AttValue :
        or_<
            seq<
                chseq<'"'>,
                star<
                    or_<
                        not_< chset<'<','&','"'> >,
                        Reference
                    >
                >,
                chseq<'"'>
            >,
            seq<
                chseq<'\''>,
                star<
                    or_<
                        not_< chset<'<','&','\''> >,
                        Reference
                    >
                >,
                chseq<'\''>
            >
        >
    { };

    struct Attribute :
        seq< Name, Eq, AttValue >
    { };

    struct EmptyElemTag :
        seq<
            chseq<'<'>,
            Name,
            star< seq<S,Attribute> >,
            opt<S>,
            chseq<'/','>'>
        >
    { };

    struct STag :
        seq<
            chseq<'<'>,
            Name,
            star< seq<S,Attribute> >,
            opt<S>,
            chseq<'>'>
        >
    { };

    struct ETag :
        seq<
            chseq<'<','/'>,
            Name,
            opt<S>,
            chseq<'>'>
        >
    { };
    
    struct element;

    struct content :
        seq<
            opt<CharData>,
            star<
                seq<
                    or_<
                        element, // the magical recursion!
                        Reference,
                        CDSect,
                        PI,
                        Comment
                    >,
                    opt<CharData>
                >
            >
        >
    { };

    struct element :
        or_<
            EmptyElemTag, 
            seq<STag, content, ETag>
        >
    { };

    struct document :
        seq<
            prolog,
            element,
            star<Misc>
        >
    { };

    struct start : document
    { };
}


int main(int argc, char *argv[])
{
    using namespace pstade;

    BOOST_FOREACH (int i, oven::one_to(argc)) {

        PSTADE_REQUIRE((
            biscuit::match<xml_grammar::start>(
                oven::file_range<boost::uint8_t>(argv[i]) |
                    oven::utf8_decoded<>()
            )
        ));

    }

    std::cout << "...parsing is end, press any key."; std::cin.ignore();

    return 0;
}
