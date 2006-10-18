#ifndef PSTADE_RADISH_SAFE_BOOL_HPP
#define PSTADE_RADISH_SAFE_BOOL_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.artima.com/cppsource/safebool.html
// http://www.pdc.kth.se/training/Talks/C++/boost/libs/utility/operators.htm#safe_bool_note
// http://lists.boost.org/Archives/boost/2003/11/56857.php
// <boost/spirit/core/safe_bool.hpp>


#include <pstade/instance.hpp>
#include <pstade/nullptr.hpp>


namespace pstade { namespace radish {


namespace safe_bool_detail {

    struct box { int true_; };

}


typedef int safe_bool_detail::box:: *
safe_bool;


// delay evaluation using template to suppress VC++ warning.
template< class Expr > inline
safe_bool make_safe_bool(Expr const& b)
{
    return b ? &safe_bool_detail::box::true_ : PSTADE_NULLPTR;
}


// slightly slower.
PSTADE_INSTANCE(safe_bool const, safe_true,  (&safe_bool_detail::box::true_))
PSTADE_INSTANCE(safe_bool const, safe_false, (PSTADE_NULLPTR))


} } // namespace pstade::radish


#endif
