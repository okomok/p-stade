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
#include <pstade/egg/use_deduced_form.hpp>


#if defined(PSTADE_EGG_HAS_FUSIONS)
    #include <boost/lambda/core.hpp>
    #include <boost/lambda/lambda.hpp>
    #include <boost/fusion/include/for_each.hpp>
    #include <pstade/egg/bll/placeholders.hpp>
#endif


namespace egg = pstade::egg;
using namespace egg;

std::stringstream g_sout;


#if defined(PSTADE_EGG_HAS_FUSIONS)

    struct little_print
    {
        template<class Me, class Args>
        struct apply
        {
            typedef void type;
        };

        template<class Re, class Args>
        void call(Args const& args) const
        {
            boost::fusion::for_each(args, g_sout << bll_1);
        }
    };

#else

    struct little_print
    {
        typedef little_print use_deduced_form;

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

#endif

typedef variadic<little_print>::type T_print;
PSTADE_EGG_CONST((T_print), print) = PSTADE_EGG_VARIADIC({});

void pstade_minimal_test()
{
    print(1,2,3,4,5);
    BOOST_CHECK(g_sout.str() == "12345");
}
