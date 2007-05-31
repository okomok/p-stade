#ifndef PSTADE_OVEN_TEST_SAMPLE_STRING_HPP
#define PSTADE_OVEN_TEST_SAMPLE_STRING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <memory> // auto_ptr
#include "./ncstring.hpp"


namespace pstade { namespace oven { namespace test {


inline
std::auto_ptr<ncstring> sample_string()
{
    return std::auto_ptr<ncstring>(new ncstring("ASORTINGEXAMPLE"));
}


} } } // namespace pstade::oven::test


#endif
