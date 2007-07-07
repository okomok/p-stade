#include <pstade/unit_test.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/clone_ptr.hpp>


#include <algorithm>
#include <memory>
#include <sstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/optional.hpp>
#include <pstade/oven/indirected.hpp>
#include <pstade/egg/new_auto.hpp>


struct xxx
{
    explicit xxx(int i)
        : m_i(i)
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


struct no_ass
{
private:
    no_ass operator=(no_ass const&);
};


inline
bool operator<(::xxx const& x1, ::xxx const& x2)
{
    return x1.m_i < x2.m_i;
}


template< class T >
void check_clone_ptr(T x)
{
    T y(x);
    y = x;
}


template< class T >
void check_regular(T x)
{
    ::check_clone_ptr(x);
    T y;
}


void pstade_unit_test()
{
    using namespace pstade;
    using egg::xp_new_auto;

    ::xxx x(3);

    {
        typedef clone_ptr< ::xxx > val_t;
        std::vector< val_t > xs;

        val_t v1(xp_new_auto< ::xxx>()(3));
        val_t v2(xp_new_auto< ::yyy>()(5));
        xs.push_back( v1 );
        xs.push_back( v2 );
        xs.push_back( val_t(xp_new_auto< ::xxx>()(9)) );
        xs.push_back( val_t(v1) );
        xs.push_back( val_t(xp_new_auto< ::yyy>()(6)) );
        xs.push_back( val_t(xp_new_auto< ::xxx>()(7)) );
        xs.push_back( val_t(xp_new_auto< ::xxx>()(12)) );
        xs.push_back( val_t(v2) );

        std::sort(xs.begin(), xs.end());

        BOOST_FOREACH (::xxx& x, xs|oven::indirected) {
            (void)x;
        }
    }

    {
        clone_ptr< ::xxx > ax(xp_new_auto< ::xxx>()(5));
        *ax;
        ax->m_i;
        ::check_clone_ptr(ax);
        ::check_regular(ax);
    }

    {
        clone_ptr< ::zzz > az(xp_new_auto< ::zzz>()(3));
    }

    {
        clone_ptr< char > ac, bc;
        // std::stringstream ss;
        // ss << ac; // rejected
        get_pointer(ac);
        swap(ac, bc);
        ac = xp_new_auto<char>()('a');
        ac.release();
    }

    {
        clone_ptr< ::no_ass > a;
        ::check_clone_ptr(a);
    }

    {
        {
            // from pointer
            clone_ptr< ::xxx > pxx(new ::xxx(10));
            clone_ptr< ::xxx > pxy(new ::yyy(10));
        }
        {
            // from auto_ptr
            clone_ptr< ::xxx > pxx(xp_new_auto< ::xxx >()(10));
            clone_ptr< ::xxx > pxy = xp_new_auto< ::yyy >()(10); // convertible
            pxx = xp_new_auto< ::xxx >()(10);
            pxy = xp_new_auto< ::yyy> ()(10);
        }
        {
            // from convertible
            clone_ptr< ::yyy > pyy(new ::yyy(10));
            clone_ptr< ::xxx > pxy(pyy);
            pxy = pyy;
        }
    }
}
