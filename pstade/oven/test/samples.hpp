#ifndef PSTADE_OVEN_TEST_SAMPLES_HPP
#define PSTADE_OVEN_TEST_SAMPLES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License)( Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include "../detail/prelude.hpp"
#include <memory> // auto_ptr
#include <string>
#include <vector>
#include <boost/assign/ptr_list_of.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "./nc_int.hpp"


namespace pstade { namespace oven { namespace test {


    inline
    std::vector<int> sample_ints()
    {
        int const src[15] = { 6,1,13,4,5,7,8,2,3,9,4,3,11,0,10 };
        return std::vector<int>(&src[0], &src[0] + 15);
    }


    inline
    std::string sample_string()
    {
        return "ASORTINGEXAMPLE";
    }


    inline
    std::auto_ptr< boost::ptr_vector<nc_int> > sample_nc_int_vector()
    {
        boost::ptr_vector<nc_int> v;
        v = boost::assign::ptr_list_of<nc_int>(7)(10)(6)(8)(5)(1)(2)(14)(15)(3)(13)(12)(9)(4)(11).to_container(v);
        return v.clone();
    }


    inline
    std::auto_ptr< boost::ptr_list<nc_int> > sample_nc_int_list()
    {
        boost::ptr_list<nc_int> v;
        v = boost::assign::ptr_list_of<nc_int>(7)(10)(6)(8)(5)(1)(2)(14)(15)(3)(13)(12)(9)(4)(11).to_container(v);
        return v.clone();
    }


} } } // namespace pstade::oven::test


#endif
