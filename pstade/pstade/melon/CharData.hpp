#ifndef PSTADE_MELON_CHARDATA_HPP
#define PSTADE_MELON_CHARDATA_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/minus.hpp>
#include <pstade/biscuit/parser/not.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include <pstade/biscuit/parser/star_until.hpp>
#include <pstade/biscuit/parser/primitive/chset.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>


namespace pstade { namespace melon {


template<
    class = void
>
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


} } // namespace pstade::melon


#endif
