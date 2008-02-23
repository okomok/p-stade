

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/variadic.hpp>
#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/accumulate.hpp>
#include <boost/egg/bll/placeholders.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/bll/result_of.hpp>
#include <boost/egg/bll/string.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_variadic
template<class Args>
struct mono_vplus
{
    typedef typename
        boost::remove_cv<
            typename boost::remove_reference<
                typename Args::head_type
            >::type
        >::type
    result_type;

    result_type operator()(Args &args) const
    {
        return boost::fusion::accumulate(
            args.get_tail(), boost::get<0>(args), bll::_2 + bll::_1 );
    }
};

typedef variadic_poly< mono_vplus<boost::mpl::_1> >::type T_vplus;
T_vplus const vplus = BOOST_EGG_VARIADIC_POLY();

void egg_example()
{
    using std::string;

    BOOST_CHECK(
        boost::lexical_cast<string>(vplus(5, 6, 7))
        == vplus(string("1"), string("8")) );
}
//]
