#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>


int func(int a)
{
    return a+2;
}


struct func_t
{
    int operator()(int a) const
    {
        return a+2;
    }
};


template<typename TFunc>
int sum_aux(TFunc& f, unsigned int a)
{
    int acum=0;
    for(unsigned int i=0; i<a; i++)
    {
        acum+=f(i);
    }
    
    return acum;
}


template<typename TFunc>
int sum(TFunc const& f, unsigned int a)
{
    return ::sum_aux(f, a);
}


template<typename TFunc>
int sum(TFunc& f, unsigned int a)
{
    return ::sum_aux(f, a);
}


void test()
{
    ::sum(::func, 1000);
    ::sum(&::func, 1000);
    ::sum(::func_t(), 1000);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
