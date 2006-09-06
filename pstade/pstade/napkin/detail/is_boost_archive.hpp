#ifndef PSTADE_NAPKIN_DETAIL_IS_BOOST_ARCHIVE_HPP
#define PSTADE_NAPKIN_DETAIL_IS_BOOST_ARCHIVE_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <pstade/has_xxx.hpp>


namespace pstade { namespace napkin { namespace detail {


PSTADE_HAS_TYPE(is_saving)
PSTADE_HAS_TYPE(is_loading)


template< class T >
struct is_boost_archive :
    boost::mpl::and_<
        has_is_saving<T>,
        has_is_loading<T>
    >
{ };


} } } // namespace pstade::napkin::detail


#endif
