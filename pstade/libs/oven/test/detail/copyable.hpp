#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_COPYABLE_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_COPYABLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/prelude.hpp>
#include "./equality.hpp"

#if !defined(PSTADE_LIBS_OVEN_TEST_DETAIL_COPY_RANGE)
#include <pstade/oven/copy_range.hpp>
#endif

namespace pstade { namespace oven { namespace test {


template< class To, class From > inline
void copyable(From const& from)
{
    // CopyConstructible needs the normal 'operator&',
    // but some class doesn't have it...
    // PSTADE_CONCEPT_ASSERT((boost::CopyConstructible<To>));

#if !defined(PSTADE_LIBS_OVEN_TEST_DETAIL_COPY_RANGE)
    To to = oven::copy_range<To>(from);
    test::equality(from, to);
#else
    (void)from;
#endif
}


} } } // namespace pstade::oven::test


#endif
