#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/jointed.hpp>
#include <pstade/unit_test.hpp>
#include <pstade/oven/test/test.hpp>


#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <deque>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/reversed.hpp>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::vector<int> em;

    {
        int b1[] = { 2,1,4,6,3,4 };
        int b2[] = { 6,5,9,6,1,36,1 };
        int b3[] = { 8,3,7 };
        int a[] = { 2,1,4,6,3,4,  6,5,9,6,1,36,1,   8,3,7 };
        test::random_access_swappable(b1|jointed(b2)|jointed(b3), a);
    }
    {
        // jointed two proxies: swappable
        int b1[] = { 2,1,4,6,3,4 };
        int b2[] = { 6,5,9,6,1,36,1 };
        int a[] = { 2,1,4,6,3,4,  6,5,9,6,1,36,1 };
        test::random_access_swappable(b1|test::proxies|jointed(b2|test::proxies), a);
    }
    {
        // const int& <- int&
        int b1[] = { 2,1,4,6,3,4 };
        int b2[] = { 6,5,9,6,1,36,1 };
        int a[] = { 2,1,4,6,3,4,  6,5,9,6,1,36,1 };
        test::random_access_constant(b1|const_refs|jointed(b2), a);
    }
    {
        // joint nc type
        int b1[] = { 2,1,4,6,3,4 };
        int b2[] = { 6,5,9,6,1,36,1 };
        int a[] = { 2,1,4,6,3,4,  6,5,9,6,1,36,1 };

        test::equality(
            make_jointed(*test::new_vector<test::ncint>(b1), *test::new_vector<test::ncint>(b2)),
            *test::new_vector<test::ncint>(a)
        );
    }
    {
        // test traversal
        int b1[] = { 2,1,4,6,3,4 };
        int b2[] = { 6,5,9,6,1,36,1 };
        int a[] = { 2,1,4,6,3,4,  6,5,9,6,1,36,1 };
        test::bidirectional_swappable(
            make_jointed(b1|identities(in_bidirectional), b2),
            a
        );
    }
    {
        int b1[] = { 2 };
        int b2[] = { 6 };
        int b3[] = { 639 };
        int b4[] = { 1 };
        int b5[] = { 1 };
        int b6[] = { 9,1 };
        int b7[] = { 3 };
        int b8[] = { 6,1,3,4,3,1,2,3,4,6 };
        int b9[] = { 0 };
        int a[] = { 2,6,639,1,1,9,1,3,  6,1,3,4,3,1,2,3,4,6,  0 };
        test::random_access_swappable(
            em|jointed(b1)|jointed(b2)|jointed(b3)|
            jointed(b4)|jointed(b5)|jointed(b6)|jointed(em)|
            jointed(  b7|jointed(em)|jointed(em)|jointed(b8)  )|
            jointed(b9),
            a
        );
    }
#if 1
    {
        bool src0_[] = { true,false,false };
        std::vector<bool> src0 = src0_|copied;
        bool src1_[] = { false,true,false };
        std::vector<bool> src1 = src1_|copied;
        bool src2_[] = { true,false,true };
        std::vector<bool> src2 = src2_|copied;
        bool const ans[] = { true,false,false,false,true,false,true,false,true };
        std::deque<bool> expected = ans|copied;
        test::random_access_swappable(src0|jointed(src1)|jointed(src2), expected);
    }
#endif
    {
        std::string src0;
        std::string src1;
        std::string src2;
        test::emptiness(src0|jointed(src1)|jointed(src2));
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
            single('x')|jointed(std::string("yz")), std::string("xyz")
        ) ));
    }

    {
        BOOST_CHECK(( oven::equals(
            std::string("xy")|jointed(single('z')), std::string("xyz")
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

