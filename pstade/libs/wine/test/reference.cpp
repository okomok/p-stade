#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/range.hpp>
#include <pstade/wine.hpp>
#include <pstade/reference.hpp>


template< class T >
void foo(T& )
{ }


void test()
{
    using namespace pstade;

    ::foo(pstade::reference(1));
    ::foo(1|to_reference);
}


template< class Fun, class T >
void apply(Fun f, T& x)
{
    f(x);
}


inline void reset(double& d) { d = 0.0; }
inline void resee(double ) { /*output value*/ }


void ctest()
{
    {
        typedef std::vector<int> vector_t;
        typedef vector_t::const_iterator citer_t;
        
        vector_t v;
        
        citer_t it0 = const_cast<vector_t const&>(v).begin();
        citer_t it1 = static_cast<citer_t>(v.begin());
        citer_t it2 = v.begin();
        
        citer_t it3 = boost::const_begin(v);
        citer_t it4 = pstade::const_reference(v).begin();
        citer_t it5 = boost::begin(pstade::const_reference(v));

        using namespace pstade;
        citer_t it6 = boost::begin((const_reference)(v)); // c-style cast? no! ADL buster!
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
        
        // ::apply(::reset, pstade::const_reference(d)); // error!
        ::apply(::resee, pstade::const_reference(d));
    }

#if 0
    {
        double d = 3;
        d = d*d;
        d = d/d;
        // ::apply(::reset, d|pstade::to_const_reference); // error!
        ::apply(::resee, d|pstade::to_const_reference);
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    ::ctest();
    return 0;
}
