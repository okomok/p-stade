

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/shared_new_array.hpp>
#include "./egg_unit_test.hpp"


#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


struct udt
{
};


CHECK_IS_RESULT_OF(boost::shared_array<int>, X_shared_new_array<int>(int))
CHECK_IS_RESULT_OF(boost::shared_array<int>, X_shared_new_array<int>(int))


CHECK_IS_RESULT_OF(boost::shared_array<udt>, X_shared_new_array<udt>(int))
CHECK_IS_RESULT_OF(boost::shared_array<udt const>, X_shared_new_array<udt const>(int))


void egg_unit_test()
{
    {
        boost::shared_array<udt> p = X_shared_new_array<udt>()(12);
        (void)p;
    }
}
