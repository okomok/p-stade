#ifndef PSTADE_MELON_DETAIL_IF_DEFAULT_HPP
#define PSTADE_MELON_DETAIL_IF_DEFAULT_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include "../default.hpp"


namespace pstade { namespace melon { namespace detail {


template<
    class DefaultT,
    class T
>
struct if_default :
    boost::mpl::if_< boost::is_same<default_, T>,
        DefaultT,
        T
    >
{ };


} } } // namespace pstade::melon::detail


#endif
