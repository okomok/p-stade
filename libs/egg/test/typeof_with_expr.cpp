

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/expr.hpp>
#include "./egg_test.hpp"


#include <boost/egg/result_of.hpp>
#include <boost/egg/function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/egg/get.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/egg/detail/fake.hpp>


#include "./using_egg.hpp"


struct little_second
{
    template<class Me, class Args>
    struct apply :
        boost::egg::result_of_<X_get_c<1>(Args&)>
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
    typedef BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, egg::expr<int(char, int)>(unfuse(details::fake<F&>())));
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


void egg_test()
{
    BOOST_CHECK( 9 == ::test_type()('a', 9) );
    BOOST_CHECK( 9 == ::test_tpl(fused_second)('a', 9) );
}
