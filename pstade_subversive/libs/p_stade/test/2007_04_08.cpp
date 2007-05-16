#include <pstade/vodka/drink.hpp>


// PStade.p_stade;
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <pstade/value_convert.hpp>

template<class T>
void foo(T const&)
{
    BOOST_MPL_ASSERT((boost::is_volatile<T>));
}

int main()
{
    int i = boost::numeric_cast<int>(10);
}
