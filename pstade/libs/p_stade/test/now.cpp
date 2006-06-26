#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <string>
#include <boost/lambda/lambda.hpp>
#include <boost/iterator/zip_iterator.hpp> // tuple_impl_specific
#include <boost/tuple/tuple.hpp>


void test()
{
    namespace bdt = boost::detail::tuple_impl_specific;
    namespace bll = boost::lambda;

    boost::tuple<int, std::string, double> t(5, "hello, fusion!", 4.5);
    bdt::tuple_for_each(t, std::cout << bll::_1 << '\n');
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}

