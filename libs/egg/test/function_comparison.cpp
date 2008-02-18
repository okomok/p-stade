#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_comparison.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_ref.hpp>


namespace my {

    struct little
    {
        template<class _, class A>
        struct apply
        {
            typedef A &type;
        };

        template<class _, class A>
        _ call(A &a) const
        {
            return a;
        }

        int m_int;
    };

    struct little_
    {
        template<class _, class A>
        struct apply
        {
            typedef A &type;
        };

        template<class _, class A>
        _ call(A &a) const
        {
            return a;
        }

        int m_int;
    };

    bool operator==(little const& left, little_ const &right)
    {
        return left.m_int == right.m_int;
    }

    bool operator>=(little const& left, little_ const &right)
    {
        return left.m_int >= right.m_int;
    }

}


namespace egg = pstade::egg;
using namespace egg;

typedef function<my::little, by_perfect> T_pmajor;
typedef function<my::little_, by_ref> T_rmajor;


void pstade_minimal_test()
{
    using namespace pstade;

    T_pmajor const pm0 = {{0}};
    T_pmajor const pm1 = {{1}};

    T_rmajor const rm0 = {{0}};
    T_rmajor const rm1 = {{1}};

    {
        BOOST_CHECK(pm0 == rm0);
        BOOST_CHECK(pm1 >= rm1);
        BOOST_CHECK(pm1 >= rm0);
    }
}
