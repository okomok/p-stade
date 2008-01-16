#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/variadic.hpp>
#include <pstade/minimal_test.hpp>

#include <boost/tuple/tuple.hpp>
#include <pstade/egg/const.hpp>
#include <pstade/egg/make_function.hpp>
#include <sstream>
#include <pstade/egg/deduced_form.hpp>

namespace egg = pstade::egg;
using namespace egg;

std::stringstream g_sout;

struct little_print
{
    typedef deduced_form call_strategy;

    template<class Me, class Args>
    struct apply
    {
        typedef void type;
    };

    template<class Re, class Args>
    void call(boost::type<Re>, Args const& args) const
    {
        g_sout << args.get_head();
        X_make_function<by_variadic>()(*this)(args.get_tail());
    }

    template<class Re>
    void call(boost::type<Re>, boost::tuples::null_type const&) const
    {}
};

typedef variadic<little_print>::type T_print;
PSTADE_EGG_CONST((T_print), print) = PSTADE_EGG_VARIADIC({});

void pstade_minimal_test()
{
    print(1,2,3,4,5);
    BOOST_CHECK(g_sout.str() == "12345");
}
