#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/variadic.hpp>
#include <pstade/minimal_test.hpp>

#include <string>

#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/accumulate.hpp>
#include <pstade/egg/bll/placeholders.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/bll/result_of.hpp>
#include <pstade/egg/bll/string.hpp>


namespace bll = boost::lambda;
namespace egg = pstade::egg;
using namespace egg;


//[code_variadic_plus
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
T_vplus const vplus = PSTADE_EGG_VARIADIC_POLY();

void test()
{
    using std::string;

    BOOST_CHECK(
        boost::lexical_cast<string>(vplus(5, 6, 7))
        == vplus(string("1"), string("8")) );
}
//]


void pstade_minimal_test()
{
    ::test();
}
