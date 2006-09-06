#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/joint_range.hpp>


#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/single_range.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        typedef joint_range< std::string, std::string > rng_t;
        boost::function_requires< boost::RandomAccessRangeConcept<rng_t> >();
    }

    std::string ans ("01234567");
    std::string ansr("76543210");
    {
        std::string rng1("0123");
        std::string rng2("4567");
        
        BOOST_CHECK(( oven::equals(
            oven::make_joint_range(rng1, rng2), ans
        ) ));

        BOOST_CHECK(( oven::equals(
            rng1|jointed(rng2), ans
        ) ));

        BOOST_CHECK(( oven::equals(
            std::string("abc")|jointed(std::string("")), std::string("abc")
        ) ));

        BOOST_CHECK(( oven::equals(
            rng1|jointed(rng2)|reversed, ansr
        ) ));

        std::vector<char> vec = oven::copy_range< std::vector<char> >(rng1|jointed(rng2));
        BOOST_CHECK(( oven::equals(
            vec, ans
        ) ));

        std::cout << oven::copy_range<std::string>(rng1|jointed(rng2)) << std::endl;
        std::cout << oven::copy_range<std::string>(rng1|jointed(rng2)|reversed) << std::endl;
    }


    {
        std::string rng1("012");
        std::string rng2("345");
        std::string rng3("67");

        joint_range<std::string, std::string> con1(rng1, rng2);
        joint_range< joint_range<std::string, std::string>, std::string > con2(con1, rng3);
        BOOST_CHECK(( oven::equals(con2, ans) ));


        BOOST_CHECK(( oven::equals(ans,
            rng1|jointed(rng2)|jointed(rng3)
        ) ));

        BOOST_CHECK(( 8 ==
            oven::distance( rng1|jointed(rng2)|jointed(rng3) )
        ));

        std::cout << oven::copy_range<std::string>(rng1|jointed(rng2)|jointed(rng3)) << std::endl;
    }

    {
        BOOST_CHECK(( oven::equals(ans,
            oven::make_joint_range(
                oven::make_joint_range(std::string("01"), std::string("2")),
                oven::make_joint_range(std::string("3"), std::string("45"))
            ) | jointed(std::string("67"))
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(ans,
            oven::make_joint_range(
                oven::make_joint_range(std::string("01"), std::string("2")),
                oven::make_joint_range(
                    oven::make_joint_range(std::string("3"), std::string("4")),
                    oven::make_joint_range(std::string("56"), std::string("7"))
                )
            )
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(ans,
                (std::string("01")|jointed(std::string("23"))) |
                    jointed(std::string("45")|jointed(std::string("67")))
        ) ));
    }

    {
        const std::string rng1("0123");
        std::string rng2("4567");
        
        BOOST_CHECK(( oven::equals(
            rng1|jointed(rng2), ans
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(
            make_single_range('x')|jointed(std::string("yz")), std::string("xyz")
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(
            std::string("xy")|jointed(make_single_range('z')), std::string("xyz")
        ) ));
    }


    {
        std::string src("xyz");
        BOOST_CHECK(( oven::equals(
            src|jointed(src)|jointed(src), std::string("xyzxyzxyz")
        ) ));

        BOOST_CHECK(( oven::equals(
            src|jointed(src)|jointed(src)|reversed, std::string("zyxzyxzyx")
        ) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
