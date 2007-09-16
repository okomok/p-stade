#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/keyword.hpp>
#include <pstade/egg/named.hpp>
#include <pstade/minimal_test.hpp>


#include <sstream>
#include <string>


namespace egg = pstade::egg;
using namespace egg;


struct op_foo1
{
    typedef std::stringstream& result_type;

    template<class In, class Out>
    Out& operator()(In& in, Out& out) const
    {
        std::string str;
        in >> str;
        out << str;
        return out;
    }
};

result_of_named2<op_foo1>::type const named_foo1 = PSTADE_EGG_NAMED_L {} PSTADE_EGG_NAMED_R;


pstade::egg::keyword<0> const _in = PSTADE_EGG_KEYWORD;
pstade::egg::keyword<1> const _out = PSTADE_EGG_KEYWORD;


void pstade_minimal_test()
{
    std::stringstream sin, sout;
    sin << "hello";

    BOOST_CHECK( named_foo1(_out = sout, _in = sin).str() == "hello" );
}
