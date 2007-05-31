#ifndef PSTADE_OVEN_TEST_SAMPLE_INT_LIST_HPP
#define PSTADE_OVEN_TEST_SAMPLE_INT_LIST_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <memory> // auto_ptr
#include "./nclist.hpp"


namespace pstade { namespace oven { namespace test {


inline
std::auto_ptr< nclist<int> > sample_int_list()
{
    int const src[15] = { 6,1,13,4,5,7,8,2,3,9,4,3,11,0,10 };
    return std::auto_ptr< nclist<int> >(new nclist<int>(&src[0], &src[0] + 15));
}


} } } // namespace pstade::oven::test


#endif
