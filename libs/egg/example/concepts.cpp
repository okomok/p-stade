

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <algorithm>
#include <boost/type_traits/remove_const.hpp>
#include <cctype>


#include "./egg_example.hpp"


namespace lexically_typed_object {
//[code_concepts_lexically_typed_object
typedef int T_a;
T_a a;

typedef int TT_1;
TT_1 _1;
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

    int maybeA = 'a'|to_upper();
    BOOST_CHECK(maybeA == 'A');

    int maybeB = to_upper()|='b';
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
struct T_is_alpha
{
    typedef int result_type;

    result_type operator()(int ch) const
    {
        return std::isalpha(ch);
    }
};

T_is_alpha const is_alpha = {};
//]
}

namespace little_function {
//[code_concepts_little_function
struct little_identity
{
    template<class Self, class T>
    struct apply
    {
        typedef T &type;
    };

    template<class Auto, class T>
    Auto call(T &x) const
    {
        return x;
    }
};
//]
}


void egg_example()
{
    pipable_function_object::test();
    ambi_function_object::test();
}
