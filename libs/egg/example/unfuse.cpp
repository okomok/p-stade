

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/config.hpp>
#if defined(BOOST_EGG_HAS_FUSIONS)


#include <boost/egg/unfuse.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <iostream>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_unfuse
struct fused_print
{
    typedef void result_type;

    template<class Args>
    void operator()(Args const &args) const
    {
        boost::fusion::for_each(args, std::cout << bll::_1);
    }
};

result_of_unfuse<fused_print>::type const print = BOOST_EGG_UNFUSE({});

void egg_example()
{
    print(1, '2', "34");
}
//]


#else

int main() {}

#endif
