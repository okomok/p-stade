#ifndef PSTADE_OVEN_TEST_SAMPLE_NCINT_VECTOR_HPP
#define PSTADE_OVEN_TEST_SAMPLE_NCINT_VECTOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <memory> // auto_ptr
#include <boost/assign/ptr_list_of.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "./ncint.hpp"


namespace pstade { namespace oven { namespace test {


inline
std::auto_ptr< boost::ptr_vector<ncint> > sample_ncint_vector()
{
    boost::ptr_vector<ncint> v;
    v = boost::assign::ptr_list_of<ncint>(7)(10)(6)(8)(5)(1)(2)(14)(15)(3)(13)(12)(9)(4)(11).to_container(v);
    return v.clone();
}


} } } // namespace pstade::oven::test


#endif
