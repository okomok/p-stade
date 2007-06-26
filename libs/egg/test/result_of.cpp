#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_pod.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/placeholders.hpp>
#include <pstade/test.hpp>
#include <pstade/egg/detail/config.hpp>
#include <pstade/pod_constant.hpp>


// easily works.
//

struct op0
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef int type;
    };

    int operator()(int) const { return 0; }
};

PSTADE_TEST_IS_RESULT_OF((int), op0(int&))


template<class X>
struct op1
{
    typedef int result_type;

    int operator()(int) const { return 0; }
};

PSTADE_TEST_IS_RESULT_OF((int), op1<double>(int&))


// msvc dislikes pod.
//

template<class X>
struct op2
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef int type;
    };

    int operator()(int) const { return 0; }

#if defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD)
    op2() { }
#endif
};

PSTADE_TEST_IS_RESULT_OF((int), op2<double>(int&))


struct dummy_base { };

template<class X>
struct op3
#if defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD)
    : dummy_base
#endif
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef int type;
    };

    int operator()(int) const { return 0; }
};

PSTADE_TEST_IS_RESULT_OF((int), op3<double>(int&))


template<class X>
struct op4
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef X type;
    };

    X operator()(int) const { return 0; }
};

// Force instantiate before calling result_of.
// If X can be any type, this workaround, of course, cannot be used.
const op4<int> instantiate = { };
PSTADE_TEST_IS_RESULT_OF((int), op4<int>(int&))




struct nonpod
{
    nonpod() { }
};

template<class X>
struct op5
{
    template<class Sig>
    struct result;

    template<class F, class A0>
    struct result<F(A0)>
    {
        typedef X type;
    };

    X operator()(int) const { return 0; }

#if defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD)
    nonpod m_dummy;
#endif
};

PSTADE_TEST_IS_RESULT_OF((int), op5<int>(int&))



void pstade_minimal_test()
{
}
