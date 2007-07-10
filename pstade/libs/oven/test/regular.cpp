#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/regular.hpp>
#include <pstade/oven/shared_regular.hpp>
#include <pstade/unit_test.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <pstade/egg/less.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/filtered.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <boost/noncopyable.hpp>


template< class F >
void regular_check(F const f)
{
    F f1(f);
    F f2;
    f2 = f1;
}


struct not_equal_to_c :
    private boost::noncopyable
{
    typedef bool result_type;

    bool operator()(char ch)
    {
        return ch != 'c';
    }
};


void pstade_unit_test()
{
    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        ::regular_check(regular(lambda::_1 != 'c'));
        ::regular_check(regular(lambda::_1 += 1));
        ::regular_check(regular_c(pstade::egg::op_less()));
        ::regular_check(regular_ref(pstade::egg::less));
    }
    {
        std::string rng("abcABc12c");
        std::vector<char> expected = std::string("abAB12")|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular(lambda::_1 != 'c')),
            expected
        ) );

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular_c(lambda::_1 != 'c')),
            expected
        ) );


        ::not_equal_to_c nonC;
        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(regular_ref(nonC)),
            expected
        ) );

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            rng|filtered(shared_regular(new ::not_equal_to_c())),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcdefg")
                | filtered(regular(lambda::_1 != 'c'))
                | filtered(regular(lambda::_1 != 'f')),
            std::string("abdeg")
        ) );
    }
}

