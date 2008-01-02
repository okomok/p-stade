#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lightweight_test.hpp>


#include <algorithm>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <cctype>


namespace lexically_typed_object {
//[code_concepts_lexically_typed_object
typedef int T_x;
T_x x;

typedef int TT_1;
TT_1 _1;
//]
}


namespace bindable_function_object {
//[code_concepts_bindable_function_object
struct bindable
{
    template<class Args>
    struct sig :
        boost::remove_const<
            typename boost::tuples::element<3, Args>::type
        >
    { };

    template<class A, class C>
    C operator()(A a, A b, C c) const
    {
        return std::for_each(a, b, c);
    }
};
//]
}


namespace pipable_function_object {
//[code_concepts_pipable_function_object
struct pipable
{
    pipable operator()() const
    {
        return *this;
    }
};

int operator|(int ch, pipable)
{
    return std::toupper(ch);
}

int operator|=(pipable, int ch)
{
    return std::toupper(ch);
}

void test()
{
    pipable const to_upper = {};

    int maybeA = 'a'|to_upper;
    BOOST_CHECK(maybeA == 'A');

    int maybeB = to_upper|='b';
    BOOST_CHECK(maybeB == 'B');
}
//]
}


namespace ambi_function_object {
//[code_concepts_ambi_function_object
struct ambi
{
    int operator()(int ch) const
    {
        return std::tolower(ch);
    }

    ambi operator()() const
    {
        return *this;
    }
};

int operator|(int ch, ambi)
{
    return std::tolower(ch);
}

int operator|=(ambi, int ch)
{
    return std::tolower(ch);
}

void test()
{
    ambi const to_lower = {};

    int maybei = 'I'|to_lower();
    BOOST_CHECK(maybei == 'i');

    int maybej = to_lower('J');
    BOOST_CHECK(maybej == 'j');
}
//]
}


namespace static_function_object {
//[code_concepts_static_function_object
typedef int (*T_is_alpha)(int ch);
T_is_alpha const is_alpha = &std::isalpha;
//]
}

namespace baby_function {
//[code_concepts_baby_function
struct baby_identity
{
    template<class _, class T>
    struct apply
    {
        typedef T &type;
    };

    template<class _, class T>
    _ call(T &x) const
    {
        return x;
    }
};
//]
}


void pstade_lightweight_test()
{
    pipable_function_object::test();
    ambi_function_object::test();
}
