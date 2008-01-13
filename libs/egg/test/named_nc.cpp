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


#include <pstade/pod_constant.hpp>
#include <sstream>
#include <string>


namespace egg = pstade::egg;
using namespace egg;


struct T_foo1
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

typedef result_of_named2<T_foo1>::type T_named_foo1;
T_named_foo1 const named_foo1 = PSTADE_EGG_NAMED_L {} PSTADE_EGG_NAMED_R;


PSTADE_POD_CONSTANT((pstade::egg::keyword<0>), _in) = PSTADE_EGG_KEYWORD();
PSTADE_POD_CONSTANT((pstade::egg::keyword<1>), _out) = PSTADE_EGG_KEYWORD();


void pstade_minimal_test()
{
    {
        std::stringstream sin, sout;
        sin << "hello";
        BOOST_CHECK( named_foo1(_out = sout, _in = sin).str() == "hello" );
    }

    {
        std::stringstream sin, sout;
        sin << "hello";
        pstade::result_of<
            T_named_foo1(
                pstade::result_of<keyword<1>(std::stringstream&)>::type,
                pstade::result_of<keyword<0>(std::stringstream&)>::type
            )
        >::type r = named_foo1(_out(sout), _in(sin));

        BOOST_CHECK( r.str() == "hello" );
    }
}
