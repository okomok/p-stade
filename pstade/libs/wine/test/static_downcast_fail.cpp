#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_downcast.hpp>


#include <boost/noncopyable.hpp>


using namespace pstade;


struct polymorphic_base_t : boost::noncopyable { virtual ~polymorphic_base_t() { } };
struct polymorphic_derived_t : polymorphic_base_t { };
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t>));

void test()
{
    polymorphic_base_t B;
    polymorphic_base_t& rB = B;
    {
        polymorphic_derived_t& rD = pstade::static_downcast<polymorphic_derived_t>(rB);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
