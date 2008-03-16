

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_value.hpp>
#include <boost/egg/function.hpp>


#include "./egg_example.hpp"


//[code_forwarding_strategies_by_value
struct little_id;
typedef function<little_id, by_value> T_id; /*< Takes arguments by value. >*/

struct little_id
{
    template<class Me, class V>
    struct apply
    {
        typedef V type;
    };

    template<class Re, class V>
    Re call(V v) const /*< `Re call(V &v) const` is allowed, but unrecommended. >*/
    {
        return v;
    }
};
//]

T_id const id = {{}};


void egg_example()
{
    BOOST_CHECK(id(10) == 10);
}
