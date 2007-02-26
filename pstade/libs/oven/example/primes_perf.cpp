#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/oven.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <pstade/used.hpp>

namespace oven = pstade::oven;
using namespace oven;


typedef
    any_range<int, boost::single_pass_traversal_tag>
range;


struct rem_not_equal_to_0
{
    typedef bool result_type;

    explicit rem_not_equal_to_0(int v) :
        m_v(v)
    { }

    bool operator()(int i) const
    {
        return i % m_v != 0;
    }

private:
    int m_v;

private:
    std::string s1;
    std::string s2;
    std::string s3;
    std::string s4;
    std::string s5;
};


namespace heap {

    range sieve(range rng)
    {
        rem_not_equal_to_0 f(front(rng));
        boost::function<bool(int)> f_(f);
        return rng|dropped(1)|filtered(f_);
    }

    range primes( iteration(range(counting_from(2)), &sieve)|transformed(front) );

}


namespace small {

    range sieve(range rng)
    {
        rem_not_equal_to_0 f(front(rng));
        boost::function<bool(int)> f_(regular_c(f));
        return rng|dropped(1)|filtered(f_);
    }

    range primes( iteration(range(counting_from(2)), &sieve)|transformed(front) );

}


int main()
{
    {
        boost::timer t;
        BOOST_FOREACH (int i, (heap::primes|taken(2000))) {
            pstade::used(i);
        }
        std::cout << t.elapsed();
    }
    std::cout << std::endl;
    {
        boost::timer t;
        BOOST_FOREACH (int i, (small::primes|taken(2000))) {
            pstade::used(i);
        }
        std::cout << t.elapsed();
    }
}
