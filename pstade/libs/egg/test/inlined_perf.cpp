#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/inlined.hpp>
#include <pstade/egg/return.hpp>
#include <pstade/egg/free.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/timer.hpp>
#include <boost/bind.hpp>


inline
long plus(long x, long y)
{
    return x + y;
}


long g_repeats = 100000000;


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

double test_static(long& k)
{
    static pstade::egg::result_of_return<long(*)(long, long), boost::use_default,
        pstade::egg::by_value>::type const
        static_plus = PSTADE_EGG_RETURN(&plus);

    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind<long>(static_plus, _1, i)(i);
        }

        measured = t.elapsed();
    }

    return measured;
}


double test_free(long& k)
{
    static pstade::egg::result_of_free<long(*)(long, long)>::type const
        freed_plus = PSTADE_EGG_FREE(&plus);

    double measured = 0;
    {
        boost::timer t;
        for (long i = 0; i < g_repeats; ++i) {
            k += boost::bind<long>(freed_plus, _1, i)(i);
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
    double m3 = ::test_static(k);
    double m4 = ::test_free(k);

    {
        std::stringstream sout;
        sout << BOOST_COMPILER << " result = "
            << m1 << " : " << m2 << " : " << m3 << " : " << m4 << std::endl;

        std::cout << sout.str();
        std::ofstream fout("inlined_perf_result.txt", std::ios::out|std::ios::app);
        fout << sout.str();
    }

    return m1 + m3 < m2 + k;
}
