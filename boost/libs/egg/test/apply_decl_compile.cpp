

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/apply_decl.hpp>
#include "./egg_test.hpp"


#include <boost/egg/config.hpp>


struct little
{
    template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, B)>
    struct BOOST_EGG_APPLY_DECL;
};


void egg_test()
{
}
