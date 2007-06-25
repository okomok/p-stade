#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_NEW_VECTOR_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_NEW_VECTOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prefix.hpp>
#include <algorithm> // for_each
#include <memory> // auto_ptr
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./push_back_new.hpp"


namespace pstade { namespace oven { namespace test {


template< class Clonable >
std::auto_ptr< boost::ptr_vector<Clonable> >
new_vector0()
{
    boost::ptr_vector<Clonable> pc;
    return pc.clone();
}


template< class Clonable, class Range >
std::auto_ptr< boost::ptr_vector<Clonable> >
new_vector(Range const& rng)
{
    boost::ptr_vector<Clonable> pc;
    std::for_each(boost::begin(rng), boost::end(rng), test::push_back_new<Clonable>(pc));
    return pc.clone();
}


} } } // namespace pstade::oven::test


#endif
