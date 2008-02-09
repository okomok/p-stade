#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/expr.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <boost/typeof/typeof.hpp>
#include <pstade/egg/get.hpp>
#include <pstade/egg/unfuse.hpp>
#include <pstade/unevaluated.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct little_second
{
    template<class Me, class Args>
    struct apply :
        pstade::result_of<X_get_c<1>(Args&)>
    { };

    template<class Re, class Args>
    Re call(Args& args) const
    {
        return X_get_c<1>()(args);
    }
};

typedef function<little_second> T_fused_second;
T_fused_second const fused_second = {{}};


BOOST_TYPEOF(egg::expr<int(char, int)>(unfuse(fused_second)))
test_type()
{
    {
        BOOST_AUTO(f, egg::expr<boost::use_default(char, int)>(unfuse(fused_second)));
        BOOST_CHECK(f('a', 9) == 9);
    }

    return egg::expr<int(char, int)>(unfuse(fused_second));
}


// GCC3.4 needs metafunction.
template<class F>
struct result_of_test_template
{
    typedef BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, egg::expr<int(char, int)>(unfuse(pstade::unevaluated<F&>())));
    typedef typename nested::type type;
};

template<class F>
typename ::result_of_test_template<F>::type
test_tpl(F ff)
{
    {
        BOOST_AUTO_TPL(f, egg::expr<boost::use_default(char, int)>(unfuse(ff)));
        BOOST_CHECK(f('a', 9) == 9);
    }

    return egg::expr<int(char, int)>(unfuse(ff));
}


void pstade_minimal_test()
{
    BOOST_CHECK( 9 == ::test_type()('a', 9) );
    BOOST_CHECK( 9 == ::test_tpl(fused_second)('a', 9) );
}
