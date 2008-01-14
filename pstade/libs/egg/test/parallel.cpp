#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/parallel.hpp>
#include <pstade/egg/memoize.hpp>
#include <pstade/unit_test.hpp>


#if defined(PSTADE_EGG_HAS_THREADS)
#include <boost/thread/thread.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;


struct fib_block
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }

    template<class Fixed>
    int operator()(Fixed f, std::string) const
    {
        return 1;
    }
};

struct T_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};


int const job_answer = 165580141;

template<class F>
struct job
{
    F f;
    mutable int res;

    void operator()() const
    {
        res = f(40);
    }
};


void pstade_unit_test()
{
    {
        BOOST_CHECK(parallel(T_my_plus())(1, 2) == 3);
    }
#if defined(PSTADE_EGG_HAS_THREADS)
    {
        typedef pstade::result_of<T_memoize(fib_block)>::type mef_t;
        mef_t mef = memoize(fib_block());
        typedef pstade::result_of<T_parallel(mef_t)>::type paf_t;
        paf_t paf = parallel(mef);

#if 1
        job<paf_t> job1 = { paf };
        job<paf_t> job2 = { paf };
        job<paf_t> job3 = { paf };
        job<paf_t> job4 = { paf };
#else
        job<mef_t> job1 = { mef };
        job<mef_t> job2 = { mef };
        job<mef_t> job3 = { mef };
        job<mef_t> job4 = { mef };
#endif

        boost::thread thrd1(boost::ref(job1));
        boost::thread thrd2(boost::ref(job2));
        boost::thread thrd3(boost::ref(job3));
        boost::thread thrd4(boost::ref(job4));

        thrd1.join();
        thrd2.join();
        thrd3.join();
        thrd4.join();

        BOOST_CHECK_EQUAL(job1.res, job_answer);
        BOOST_CHECK_EQUAL(job2.res, job_answer);
        BOOST_CHECK_EQUAL(job3.res, job_answer);
        BOOST_CHECK_EQUAL(job4.res, job_answer);
    }
#endif
}
