#ifndef PSTADE_HAMBURGER_DETAIL_OPTIONAL_ZERO_HPP
#define PSTADE_HAMBURGER_DETAIL_OPTIONAL_ZERO_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lexicalize.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger { namespace detail {


    template< class Target, class Node >
    void optional_zero(Target& x, Node& node, ustring const& Name)
    {
        try {
            Target opt = node%Name|egg::lexicalize();
            if (opt != 0)
                x = opt;
        }
        catch (boost::bad_lexical_cast const&) {
        }
    }


} } } // namespace pstade::hamburger::detail


#endif
