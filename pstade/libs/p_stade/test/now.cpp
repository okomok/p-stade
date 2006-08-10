#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>


#define PP_OBJECT(Type, Var, ArgSeq, Statement) \
    Type Var; \
    BOOST_PP_CAT(construct_, Type)(&Var, BOOST_PP_SEQ_ENUM(ArgSeq)); \
    Statement \
    BOOST_PP_CAT(destruct_, Type)(&Var); \
/**/



typedef memory *void;

void construct_memory(void ** pp, std::size_t sz)
{
    *pp = std::malloc(sz);
}

void destruct_memory(void **p)
{
    std::free(p);
}


struct string
{
    char *p;
};


void construct_string(string *p, char *psz)
{
}

void destruct_string(string *p)
{
}


void test()
{
    PP_OBJECT(memory, x, (35),
    PP_OBJECT(string, y, ("xyz"),
    PP_OBJECT(string, z, ("xyz"),
        int a;
        hello();
        goodbye();

    )))
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
