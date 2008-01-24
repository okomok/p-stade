#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/boost_workaround.hpp>
#if BOOST_WORKAROUND(__GNUC__, == 3) // needs deduced_from.
int main() {}
#else


#include <pstade/egg/variadic.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/tuple/tuple.hpp>
#include <pstade/egg/make_function.hpp>
#include <sstream>
#include <string>


#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/lambda/core.hpp>
    #include <boost/lambda/lambda.hpp>
    #include <boost/fusion/include/for_each.hpp>
    #include <pstade/egg/bll/placeholders.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;

#if defined(PSTADE_EGG_HAS_FUSIONS)

//[code_variadic_print
struct little_print
{
    template<class Me, class Args>
    struct apply
    {
        typedef void type;
    };

    template<class Re, class Args>
    void call(Args& args) const
    {
        boost::fusion::for_each(args, std::cout << bll_1);
    }
};

typedef variadic<little_print>::type T_print;
T_print const print = PSTADE_EGG_VARIADIC({});

void test()
{
    print(1, '2', 3, std::string("4"));
}
//]

#else

struct little_print
{
    template<class Me, class Args>
    struct apply
    {
        typedef void type;
    };

    template<class Re, class Args>
    void call(Args& args) const
    {
        std::cout << args.get_head();
        make_function(*this)(args.get_tail());
    }

    template<class Re>
    void call(boost::tuples::null_type) const
    {}
};

typedef variadic<little_print>::type T_print;
T_print const print = PSTADE_EGG_VARIADIC({});

void test()
{
    ::print(1, '2', 3, std::string("4"));
}

#endif


void pstade_minimal_test()
{
    ::test();
}

#endif
