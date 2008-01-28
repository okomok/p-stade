#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/inlined.hpp>


#include <fstream>
#include <boost/timer.hpp>
#include <boost/bind.hpp>


inline
long plus(long x, long y)
{
    return x + y;
}


#if defined(NDEBUG)
long g_repeats = 1000000000;
#else
long g_repeats = 100000;
#endif


double test_pointer(long& k)
{
    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind(&plus, _1, i)(i);
        }

        measured = t.elapsed();
    }

    return measured;
}

double test_inlined(long& k)
{
    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind<long>(PSTADE_EGG_INLINE(&plus), _1, i)(i);
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
        std::ofstream fout("inlined_perf_result.txt", std::ios::out|std::ios::app);
        fout << BOOST_COMPILER << " result = " << m1 << " : " << m2 << std::endl;
    }

    return m1 < m2 + k;
}
