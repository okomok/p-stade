#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/deduced_const.hpp>


#include <boost/utility/result_of.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/oven/begin_end.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_const.hpp>


namespace oven = pstade::oven;
using namespace oven;


template< class Range >
typename range_iterator<Range const>::type
algo1(Range const& rng)
{
    return begin(rng);
}

template< class Range >
typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type
algo2(Range const& rng)
{
    return begin(rng);
}

template< class Range >
typename boost::result_of<T_begin(PSTADE_DEDUCED_CONST(Range)&)>::type
algo3(Range const& rng)
{
    return begin(rng);
}

template< class X, class Range >
typename boost::result_of<T_begin(Range&)>::type
algo4(Range& rng)
{
    return begin(rng);
}

template< class X, class Range >
typename boost::result_of<T_begin(PSTADE_DEDUCED_CONST(Range)&)>::type
algo4(Range const& rng)
{
    return begin(rng);
}


template<class X>
struct my
{
    template<class FunCall>
    struct result;

    template<class Fun, class A>
    struct result<Fun(A&)>
    {
        BOOST_MPL_ASSERT((boost::is_const<A>));
        typedef int type;
    };

    template<class A>
    int operator()(A& ) const
    {
        return 10;
    }

    my() { } // for Boost v1.33
};

template< class X, class Range >
typename boost::result_of<my<X>(Range&)>::type
algo5(Range& rng PSTADE_CONST_OVERLOADED(Range))
{
    return my<X>()(rng);
}

template< class X, class Range >
typename boost::result_of<my<X>(PSTADE_DEDUCED_CONST(Range)&)>::type
algo5(Range const& rng)
{
    return my<X>()(rng);
}


struct base
{
    virtual ~base() { }
    virtual void foo() = 0;
};

struct derived : base
{
    virtual void foo() { }
};


void test()
{
    {
        int arr[] = { 1,2,3, };

        //::algo1(arr); error under VC7.1
        ::algo2(arr);
        ::algo3(arr);
        ::algo4<int>(arr);
    }
    {
        derived const d = derived();;
        int i = ::algo5<int>(d);
        (void)i;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
