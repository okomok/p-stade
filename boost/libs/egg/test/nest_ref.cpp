

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include "./egg_test.hpp"


#include <boost/utility/addressof.hpp>
#include <string>


struct T_second
{
    typedef std::string &result_type;

    template<class A2>
    result_type operator()(int, A2 &k, int) const
    {
        k.size();
        return k;
    }
};

T_second const second = {};


void egg_test()
{
    using BOOST_EGG_NEST_NAMES;
    using boost::egg::details::unwrap_ref;
    using boost::egg::details::wrap_ref;

    std::string s("abc");
    int i1 = 1;

    {
        // \x -> second(x, ref(s), 1)
        BOOST_CHECK( boost::addressof( nest1(second)(_0_(_1), ref1(s), 1)(i1) ) == &s );
    }
    {
        // Rs = ref(s);
        // \x -> (\y -> second(x, unwrap_ref(Rs), y)
        BOOST_CHECK( boost::addressof( nest2(second)(_0_(_1), ref2(s), _1_(_1))(i1)(i1) ) == &s );
        BOOST_CHECK( boost::addressof( nest2(second)(_0_(_1), nest2(unwrap_ref)(wrap_ref(s)), _1_(_1))(i1)(i1) ) == &s );
    }
    {
        // \x -> (\y -> (\z -> second(x, ref(i), z))
        BOOST_CHECK( boost::addressof( nest3(second)(_0_(_1), ref3(s), _2_(_1))(i1)(i1)(i1) ) == &s );
    }
    {
        BOOST_CHECK(boost::addressof(ref0(s)) == &s);
    }
}
