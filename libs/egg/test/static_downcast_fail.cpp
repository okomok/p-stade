

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/static_downcast.hpp>
#include "./egg_test.hpp"


#include <boost/noncopyable.hpp>


#include "./using_egg.hpp"


struct polymorphic_base_t : boost::noncopyable { virtual ~polymorphic_base_t() { } };
struct polymorphic_derived_t : polymorphic_base_t { };
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t>));
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t const>));
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t volatile>));
BOOST_MPL_ASSERT((boost::is_polymorphic<polymorphic_base_t volatile const>));

void egg_test()
{
    polymorphic_base_t B;
    polymorphic_base_t const& rB = B;
    {
        polymorphic_derived_t const& rD = egg::static_downcast<polymorphic_derived_t>(rB);
        (void)rD;
    }
}
