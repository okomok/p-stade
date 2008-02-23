

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/implicit.hpp>
#include <boost/lexical_cast.hpp>


#include "./egg_example.hpp"


//[code_example_implicit
template<class To>
struct X_lexical_cast
{
    typedef To result_type;

    template<class From>
    To operator()(From from) const
    {
        return boost::lexical_cast<To>(from);
    }
};

typedef
    implicit< X_lexical_cast<boost::mpl::_> >::type
T_lexical;

T_lexical const lexical = BOOST_EGG_IMPLICIT();

void egg_example()
{
    std::string str = lexical(20);
    BOOST_CHECK( str == "20" );
}
//]
