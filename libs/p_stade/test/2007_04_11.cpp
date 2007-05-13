#include <pstade/vodka/drink.hpp>


// PStade.p_stade;
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/junk/eval_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>


using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;

typedef mpl::lambda< mpl::plus<_, _> >::type plus;
typedef mpl::lambda< mpl::minus<_, _> >::type minus;


typedef
    pstade::eval_of<
        plus(
            plus(mpl::int_<2>, minus(mpl::int_<3>, mpl::int_<1>)),
            plus(mpl::int_<5>, mpl::int_<10>)
        )
    >::type
result;


int main()
{
    BOOST_STATIC_ASSERT(( result::value == 19 ));
}
