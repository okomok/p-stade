#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/curry.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/egg/tuple/pack.hpp>
#include <pstade/unused.hpp>


struct my_identity
{
    template<class Signature>
    struct result;

    template<class Self, class Int1>
    struct result<Self(Int1)>
    {
        typedef int type;
    };

    int operator()(int x) const
    {
        return x;
    }
};

struct my_plus2
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2>
    struct result<Self(Int1, Int2)>
    {
        typedef int type;
    };

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

struct my_plus3
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3>
    struct result<Self(Int1, Int2, Int3)>
    {
        typedef int type;
    };

    int operator()(int x, int y, int z) const
    {
        return x + y + z;
    }
};

struct my_plus4
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4>
    struct result<Self(Int1, Int2, Int3, Int4)>
    {
        typedef int type;
    };

    int operator()(int x, int y, int z, int q) const
    {
        return x + y + z + q;
    }
};

struct my_plus5
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4, class Int5>
    struct result<Self(Int1, Int2, Int3, Int4, Int5)>
    {
        typedef int type;
    };

    int operator()(int x, int y, int z, int q, int r) const
    {
        return x + y + z + q + r;
    }
};


void pstade_minimal_test()
{
    using namespace pstade::egg;

    {
        BOOST_CHECK(
            curry1(::my_identity())(3) == 3
        );
    }
    {
        BOOST_CHECK(
            detail::bind1(::my_plus2(), 5)(7) == 12
        );
    }
    {
        BOOST_CHECK(
            curry2(::my_plus2())(5)(7) == 12
        );
    }
    {
        BOOST_CHECK(
            detail::bind2(::my_plus3(), 5, 7)(2) == 14
        );
    }
    {
        BOOST_CHECK(
            curry3(::my_plus3())(5)(7)(2) == 14
        );
    }
    {
        BOOST_CHECK(
            curry4(::my_plus4())(5)(7)(2)(3) == 17
        );
    }
    {
        BOOST_CHECK(
            curry5(::my_plus5())(5)(7)(2)(3)(4) == 21
        );
    }
}
