#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/oven/in_block.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/foreach.hpp>
#include <boost/range/empty.hpp>


using namespace pstade::oven;


struct power
{
    int m_number, m_exponent;

    power(int number, int exponent) :
        m_number(number), m_exponent(exponent)
    { }

    typedef int yield_type;

    template<typename Yield>
    void operator()(Yield yield) const
    {
        if (m_number < 0)
            yield.break_();

        int counter = 0;
        int result = 1;
        while (counter++ < m_exponent) {
            result = result * m_number;
            yield.return_(result);
        }
    }
};


void pstade_minimal_test()
{
    BOOST_FOREACH (int x, in_block(power(2, 8)))
        std::cout << x << ',';

    int a[] = { 2,4,8,16,32,64,128,256 };
    BOOST_CHECK( equals(in_block(power(2, 8)), a) );

    BOOST_CHECK( boost::empty(in_block(power(-1, 8))) );
}
