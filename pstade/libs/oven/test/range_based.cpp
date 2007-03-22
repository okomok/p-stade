#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/range_based1.hpp>
#include <pstade/oven/range_based2.hpp>
#include <pstade/oven/detail/good_sig.hpp>


#include <algorithm>
#include <string>
#include <pstade/functional.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/numeric.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/algorithm.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/test.hpp>


struct do_nothing
{
    typedef void result_type;

    template< class A >
    void operator()(A const&) const
    {
    }
};

struct op_sort
{
    typedef void result_type;

    template< class Iter >
    void operator()(Iter f, Iter l) const
    {
        std::sort(f, l);
    }
};

struct op_sort2
{
    typedef void result_type;

    template< class Iter, class Iter_ >
    void operator()(Iter f, Iter l, Iter_ f_, Iter_ l_) const
    {
        std::sort(f, l);
        std::sort(f_, l_);
    }
};


struct nullary_sig
{
    template< class Sig >
    struct sig
    {
        typedef int type;
    };

    int operator()() const
    {
        return 10;
    }

    int operator()(int i) const
    {
        return i + 10;
    }
};


void test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("edcbagf");
        detail::good_sig_return_op<lambda::ll::for_each>()(boost::begin(rng)|pstade::as_ref, boost::end(rng)|pstade::as_ref, do_nothing()|pstade::as_ref);
        oven::range_based1(detail::good_sig(lambda::ll::for_each()))(rng, do_nothing());
        oven::range_based1(detail::good_sig_return_op<lambda::ll::for_each>())(rng, do_nothing());
        oven::range_based1(detail::good_sig_return_op<lambda::ll::sort>())(rng);
        oven::range_based1(detail::good_sig_return_op<lambda::ll::sort>())(rng, pstade::less);
        BOOST_CHECK( rng == "abcdefg" );
    }
    {
        std::string rng("edcbagf");
        oven::range_based1(::op_sort())(rng);
        BOOST_CHECK( rng == "abcdefg" );
    }
    {
        std::string rng("edcbagf");
        std::string rng_("542613");
        oven::range_based2(::op_sort2())(rng, rng_);
        BOOST_CHECK( rng == "abcdefg" );
        BOOST_CHECK( rng_ == "123456" );
    }
    { // big arity check
        std::string rng;
        bool never = false;
        if (never) {
            oven::range_based1(detail::good_sig_return_op<lambda::ll::inner_product>())(rng, boost::begin(rng), 'c', pstade::plus, pstade::plus);
            oven::range_based2(detail::good_sig_return_op<lambda::ll::merge>())(rng, rng, boost::begin(rng), pstade::less);
        }
    }
    { // nullary
        typedef boost::result_of<detail::op_good_nullary_sig(::nullary_sig)>::type good_t;
        PSTADE_TEST_IS_RESULT_OF((int), good_t(int))
        PSTADE_TEST_IS_RESULT_OF((int), good_t())
        int const i = 1;
        BOOST_CHECK( detail::good_nullary_sig(nullary_sig())() == 10 );
        BOOST_CHECK( detail::good_nullary_sig(nullary_sig())(i) == 11 );
        BOOST_CHECK( detail::good_sig(nullary_sig())(i) == 11 );
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
