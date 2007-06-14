#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/move_to_auto_ptr.hpp>


#include <pstade/enable_if.hpp>
#include <pstade/new_delete.hpp>
#include <pstade/test.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/ptr_container/detail/static_move_ptr.hpp>


using namespace pstade;


PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), op_move_to_auto_ptr<int>(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), op_move_to_auto_ptr<int>(std::auto_ptr<int>))


struct B { virtual ~B() { } };
struct D : B { };

PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<B>), op_move_to_auto_ptr<B>(std::auto_ptr<D>))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<B>), op_move_to_auto_ptr<B>(boost::ptr_container_detail::static_move_ptr<D>))



void test()
{
    {
        BOOST_CHECK( *op_move_to_auto_ptr<int>()(std::auto_ptr<int>(new int(3))) == 3 );
        BOOST_CHECK( *op_move_to_auto_ptr<int>()(boost::ptr_container_detail::static_move_ptr<int>(new int(5))) == 5 );
    }
    {
        BOOST_CHECK( *pstade::move_to_auto_ptr<int>(std::auto_ptr<int>(new int(3))) == 3 );
        BOOST_CHECK( *pstade::move_to_auto_ptr<int>(boost::ptr_container_detail::static_move_ptr<int>(new int(5))) == 5 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
