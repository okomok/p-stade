

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/inlined.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/bind.hpp>


struct klass {

    virtual ~klass() {}

    long plus(long x, long y)
    {
        return x + y;
    }
};


long g_repeats = 100000000;


double test_pointer(long& k)
{
    klass obj;;

    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind(&klass::plus, obj, _1, i)(i);
        }

        measured = t.elapsed();
    }

    return measured;
}

double test_inlined(long& k)
{
    klass obj;

    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind<long>(BOOST_EGG_INLINE(&klass::plus), obj, _1, i)(i);
        }

        measured = t.elapsed();
    }

    return measured;
}


int main()
{
    long k  = 0;
    double m1 = ::test_pointer(k);
    double m2 = ::test_inlined(k);

    {
        std::stringstream sout;
        sout << BOOST_COMPILER << " result = "
            << m1 << " : " << m2 << std::endl;

        std::cout << sout.str();
        std::ofstream fout("inlined_perf_result.txt", std::ios::out|std::ios::app);
        fout << sout.str();
    }

    return m1 < m2 + k;
}
