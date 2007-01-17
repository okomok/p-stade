#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/jointed.hpp>


#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/as_single.hpp>
#include <pstade/oven/reversed.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int src0[] = { 2,1,4 };
        int src1[] = { 6,5,9 };
        int src2[] = { 8,3,7 };
        int const ans[] = { 2,1,4,6,5,9,8,3,7 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(src0|jointed(src1)|jointed(src2), expected) );
    }
    {
        std::string src0;
        std::string src1;
        std::string src2;
        BOOST_CHECK( oven::test_empty(src0|jointed(src1)|jointed(src2)) );
    }

    std::string ans ("01234567");
    std::string ansr("76543210");
    {
        std::string rng1("0123");
        std::string rng2("4567");
        
        BOOST_CHECK(( oven::equals(
            oven::make_jointed(rng1, rng2), ans
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

#if 0 // no longer a public class template
        joint_range<std::string, std::string> con1(rng1, rng2);
        joint_range< joint_range<std::string, std::string>, std::string > con2(con1, rng3);
        BOOST_CHECK(( oven::equals(con2, ans) ));
#endif

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
            oven::make_jointed(
                oven::make_jointed(std::string("01"), std::string("2")),
                oven::make_jointed(std::string("3"), std::string("45"))
            ) | jointed(std::string("67"))
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(ans,
            oven::make_jointed(
                oven::make_jointed(std::string("01"), std::string("2")),
                oven::make_jointed(
                    oven::make_jointed(std::string("3"), std::string("4")),
                    oven::make_jointed(std::string("56"), std::string("7"))
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
            make_as_single('x')|jointed(std::string("yz")), std::string("xyz")
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(
            std::string("xy")|jointed(make_as_single('z')), std::string("xyz")
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
