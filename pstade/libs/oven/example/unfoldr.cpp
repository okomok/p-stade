#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//unfoldr      :: (b -> Maybe (a, b)) -> b -> [a]
//unfoldr f b  =
//  case f b of
//   Just (a,new_b) -> a : unfoldr f new_b
//   Nothing        -> []


#include <iostream>
#include <utility>
#include <pstade/oven/in_block.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/foreach.hpp>
#include <pstade/result_of.hpp>
#include <boost/optional.hpp>


using namespace pstade::oven;
using pstade::result_of;


template<typename A, typename B, typename F>
struct unfoldr_block
{
    B m_b;
    F m_f;

    typedef A yield_type;

    template<typename Yield>
    void operator()(Yield yield) // const
    {
        for (;;) {
            boost::optional< std::pair<A, B> > p = m_f(m_b);

            if (!p)
                break;

            yield(p->first);
            m_b = p->second;
        }
    }
};


template<typename A, typename B, typename F>
typename result_of<op_in_block(unfoldr_block<A, B, F>&)>::type
unfoldr(F f, B b)
{
    unfoldr_block<A, B, F> r = { b, f };
    return in_block(r);
}


boost::optional< std::pair <int, std::pair<int, int> > >
fib_aux(std::pair<int, int> x_y)
{
    return std::make_pair(x_y.first, std::make_pair(x_y.second, x_y.first + x_y.second));
}


void pstade_minimal_test()
{
    BOOST_FOREACH (int x, ::unfoldr<int>(&fib_aux, std::make_pair(1, 1))|taken(50))
        std::cout << x << ',';
}
