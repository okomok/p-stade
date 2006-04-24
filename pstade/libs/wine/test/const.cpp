#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/const.hpp>


#include <vector>
#include <boost/range.hpp>
#include <pstade/wine.hpp>


// See: http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf


template< class Fun, class T >
void apply(Fun f, T& x)
{
    f(x);
}


inline void reset(double& d) { d = 0.0; }
inline void resee(double ) { /*output value*/ }


void test()
{
    {
        typedef std::vector<int> vector_t;
        typedef vector_t::const_iterator citer_t;
        
        vector_t v;
        
        citer_t it0 = const_cast<vector_t const&>(v).begin();
        citer_t it1 = static_cast<citer_t>(v.begin());
        citer_t it2 = v.begin();
        
        citer_t it3 = boost::const_begin(v);
        citer_t it4 = pstade::const_(v).begin();
        citer_t it5 = boost::begin(pstade::const_(v));

        using namespace pstade;
        citer_t it6 = boost::begin((const_)(v)); // c-style cast? no! ADL buster!
    }

    {
        double d = 3;
        d = d*d;
        d = d/d;
        
        ::apply(::reset, d); // oops: resee intended
        BOOST_CHECK(d == 0.0);
    }

    {
        double d = 3;
        d = d*d;
        d = d/d;
        
        // ::apply(::reset, pstade::const_(d)); // error!
        ::apply(::resee, pstade::const_(d));
    }

    {
        double d = 3;
        d = d*d;
        d = d/d;
        // ::apply(::reset, d|pstade::const_qualified); // error!
        ::apply(::resee, d|pstade::const_qualified);
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
