#include <boost/egg/pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/fuse.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/noncopyable.hpp>
#include <boost/egg/tuple/pack.hpp>
#include <boost/egg/pstade/unused.hpp>


int my_plus(int x, int y, int z)
{
    return x + y + z;
}

int my_two()
{
    return 2;
}


struct nc :
    private boost::noncopyable
{ };

int take_nc(nc&)
{
    return 3;
}

struct my_f
{
    typedef int result_type;
    int operator()(int, int) const { return 1; }
};


void pstade_minimal_test()
{
    using namespace pstade::egg;

    {
        BOOST_CHECK(
            fuse(&::my_plus)(boost::make_tuple(5, 7, 2)) == 14
        );
    }
    {
        BOOST_CHECK(
            fuse(&::my_two)(boost::make_tuple()) == 2
        );
    }
    {
        ::nc x;
        BOOST_CHECK( fuse(&::take_nc)(pstade::egg::tuple_pack(x)) == 3 );
    }
    {
        ::my_f f0;
        result_of_fuse< ::my_f >::type f1 = BOOST_EGG_FUSE_L f0 BOOST_EGG_FUSE_R;
        result_of_fuse< ::my_f >::type f2 = BOOST_EGG_FUSE({});
        pstade::unused(f1, f2);
    }
}
