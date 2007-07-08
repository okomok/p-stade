#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/test.hpp>
#include <pstade/detail/as_mpl_lambda.hpp>


#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/oven.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


namespace pstade { namespace oven {
namespace counting_from_detail {


    template< class Incrementable >
    struct baby
    {
        typedef typename
            pass_by_value<Incrementable>::type
        inc_t;

        typedef typename
            boost::result_of<
                op_counting(Incrementable&, inc_t)
            >::type
        result_type;

        result_type operator()(Incrementable& i) const
        {
            return counting(i, (std::numeric_limits<inc_t>::max)());
        }
    };


} // namespace counting_from_detail

PSTADE_FUNCTION(counting_from, (counting_from_detail::baby<_>))
} } // namespace pstade::oven


template< class Lambda >
struct base_op_front :
    pstade::callable< base_op_front<Lambda> >
{
    template< class Myself, class Range >
    struct apply :
        boost::mpl::apply1<Lambda, Range>
    { };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return *boost::begin(rng);
    }
};

PSTADE_AUXILIARY(0, my_value_front, (::base_op_front<PSTADE_DETAIL_AS_MPL_LAMBDA((pstade::oven::range_value<boost::mpl::_>))>))


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


typedef
    any_range<int, boost::single_pass_traversal_tag>
range;

range sieve(range rng)
{
    return rng|dropped(1)|filtered(regular(lambda::_1 % ::my_value_front(rng) != 0));
}

range primes( iteration(range(counting_from(2)), &::sieve)|transformed(::my_value_front) );


void test()
{
    (primes|taken(200));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
