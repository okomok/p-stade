#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_WINE_TEST_MINIMAL
#endif

#if !defined(PSTADE_WINE_TEST_MINIMAL)
    #include <boost/test/test_tools.hpp>
    #define BOOST_LIB_NAME boost_test_exec_monitor
    #include <boost/config/auto_link.hpp>
#else
    #include <boost/test/minimal.hpp>
#endif


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/assignable.hpp>


#include <algorithm>
#include <memory>
#include <sstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/optional.hpp>
#include <pstade/oven/indirect_range.hpp>
#include <pstade/nonassignable.hpp>


struct xxx
{
    explicit xxx(int i) :
        m_i(i)
    { }

    int m_i;
};


struct yyy : xxx
{
    explicit yyy(int i) :
        xxx(i)
    { }
};


// has no relational operators.
struct zzz
{
    explicit zzz(int )
    { }
};


struct no_ass :
    private pstade::nonassignable
{ };


inline
bool operator<(::xxx const& x1, ::xxx const& x2)
{
    return x1.m_i < x2.m_i;
}


template< class T >
void check_assignable(T x)
{
    T y(x);
    y = x;
}


template< class T >
void check_regular(T x)
{
    ::check_assignable(x);
    T y;
}


void test()
{
    using namespace boost;
    using namespace pstade;

    ::xxx x(3);

    {
        typedef assignable< ::xxx > val_t;
        std::vector< val_t > xs;

        val_t v1(::xxx(3));
        val_t v2(::yyy(5));
        xs.push_back( v1 );
        xs.push_back( v2 );
        xs.push_back( val_t(::xxx(9)) );
        xs.push_back( val_t(v1) );
        xs.push_back( val_t(::yyy(6)) );
        xs.push_back( val_t(::xxx(7)) );
        xs.push_back( val_t(::xxx(12)) );
        xs.push_back( val_t(v2) );

        std::sort(xs.begin(), xs.end());

        BOOST_FOREACH( ::xxx& x, xs|oven::indirected) {
            (void)x;
        }
    }

    {
        ::check_assignable(pstade::make_assignable(::xxx(10)));
        ::check_assignable(pstade::make_assignable(lambda::_1 == 'x'));
    }

    {
        assignable< ::xxx > ax(::xxx(5));
        *ax;
        ax->m_i;
        ::check_assignable(ax);
        boost::optional< assignable< ::xxx > > ox;
        ::check_regular(ox);
    }

    {
        assignable< ::zzz > az(::zzz(3));
    }

    {
        assignable< char > ac, bc;
        std::stringstream ss;
        ss << ac;
        get_pointer(ac);
        swap(ac, bc);
    }

    {
        assignable< ::no_ass > a;
        ::check_assignable(a);
    }
}


#if !defined(PSTADE_WINE_TEST_MINIMAL)

    #include <boost/test/unit_test.hpp>
    using boost::unit_test::test_suite;

    test_suite *
    init_unit_test_suite(int argc, char *argv[])
    {
        test_suite *test = BOOST_TEST_SUITE("Oven Test Suite");
        test->add(BOOST_TEST_CASE(&::test));

        (void)argc, (void)argv; // unused
        return test;
    }

#else

    int test_main(int, char*[])
    {
        ::test();
        return 0;
    }

#endif
