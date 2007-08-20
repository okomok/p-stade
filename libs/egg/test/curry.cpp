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
#include <pstade/egg/to_string.hpp>
#include <pstade/pod_constant.hpp>

using pstade::egg::to_string;


struct my_plus2
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2>
    struct result<Self(Int1, Int2)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y) const
    {
        return to_string(x) + to_string(y);
    }
};

typedef pstade::egg::result_of_curry2<my_plus2>::type op_curried_plus2;
PSTADE_POD_CONSTANT((op_curried_plus2), curried_plus2) = PSTADE_EGG_CURRY2({} BOOST_PP_EMPTY)();


struct my_plus3
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3>
    struct result<Self(Int1, Int2, Int3)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z) const
    {
        return to_string(x) + to_string(y) + to_string(z);
    }
};

typedef pstade::egg::result_of_curry3<my_plus3>::type op_curried_plus3;
PSTADE_POD_CONSTANT((op_curried_plus3), curried_plus3) = PSTADE_EGG_CURRY3({} BOOST_PP_EMPTY)();


struct my_plus4
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4>
    struct result<Self(Int1, Int2, Int3, Int4)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z, int q) const
    {
        return to_string(x) + to_string(y) + to_string(z) + to_string(q);
    }
};

typedef pstade::egg::result_of_curry4<my_plus4>::type op_curried_plus4;
PSTADE_POD_CONSTANT((op_curried_plus4), curried_plus4) = PSTADE_EGG_CURRY4({} BOOST_PP_EMPTY)();


struct my_plus5
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4, class Int5>
    struct result<Self(Int1, Int2, Int3, Int4, Int5)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z, int q, int r) const
    {
        return to_string(x) + to_string(y) + to_string(z) + to_string(q) + to_string(r);
    }

    int dummy1, dummy2; // for checking braced initialization.
};

#define INIT_my_plus5() {1,2}
typedef pstade::egg::result_of_curry5<my_plus5>::type op_curried_plus5;
PSTADE_POD_CONSTANT((op_curried_plus5), curried_plus5) = PSTADE_EGG_CURRY5(INIT_my_plus5)();


template<class F>
void ref_check(F f, int& i)
{
    i = 7;
    BOOST_CHECK(f(3)(4) == "57234");
}

struct nc1_t : boost::noncopyable { };
struct nc2_t : boost::noncopyable { };
struct nc3_t : boost::noncopyable { };


struct foo3
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3>
    struct result<Self(Int1, Int2, Int3)>
    {
        typedef int type;
    };

    template<class Int1, class Int2, class Int3>
    int operator()(Int1&, Int2&, Int3&) const
    {
        return 10;
    }
};


void pstade_minimal_test()
{
    using namespace pstade::egg;

    {
        BOOST_CHECK(
            detail::bind1(::my_plus2(), 5)(7) == "57"
        );
    }
    {
        BOOST_CHECK(
            curry2(::my_plus2())(5)(7) == "57"
        );
    }
    {
        BOOST_CHECK(
            curried_plus2(5)(7) == "57"
        );
    }
    {
        BOOST_CHECK(
            detail::bind2(::my_plus3(), 5, 7)(2) == "572"
        );
    }
    {
        BOOST_CHECK(
            curry3(::my_plus3())(5)(7)(2) == "572"
        );
    }
    {
        BOOST_CHECK(
            curried_plus3(5)(7)(2) == "572"
        );
    }
    {
        BOOST_CHECK(
            curry4(::my_plus4())(5)(7)(2)(3) == "5723"
        );
    }
    {
        BOOST_CHECK(
            curried_plus4(5)(7)(2)(3) == "5723"
        );
    }
    {
        BOOST_CHECK(
            curry5(::my_plus5())(5)(7)(2)(3)(4) == "57234"
        );
    }
    {
        BOOST_CHECK(
            curried_plus5(5)(7)(2)(3)(4) == "57234"
        );
    }
    {
        nc1_t nc1;
        nc2_t nc2;
        nc3_t nc3;
        curry3(::foo3())(boost::ref(nc1))(boost::ref(nc2))(boost::ref(nc3));
    }
    {
        int i = 2;
        BOOST_CHECK(
            curried_plus5(5)(7)(boost::ref(i))(3)(4) == "57234"
        );

        ::ref_check(curried_plus5(5)(boost::ref(i))(2), i);
    }
}
