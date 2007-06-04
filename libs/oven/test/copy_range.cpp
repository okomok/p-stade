#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copy_range.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <pstade/oven/copied_to.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/copy_assign.hpp>
#include <pstade/oven/equals.hpp>


struct convertible_to_any
{
    template< class To_ >
    operator To_() const
    {
        return To_();
    }
};


void test_()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<int> vec = oven::counting(3, 9)|copied;
        vec.push_back(9);
        BOOST_CHECK( oven::equals(vec, oven::counting(3, 10)) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec = oven::copy_range< std::vector<char> >(rng);
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec = rng|copied;
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec;
        pstade::copy_assign(vec, rng|copied);
        BOOST_CHECK( oven::equals(vec, rng) );
    }

#if 0 // rejected
    {
        std::string   in("hello, copied!");
        std::string out1("hello, ranges!");
        std::string out2("hello, ranges!");
        std::string out3("hello, ranges!");
        in|copied_to(out1);
        in|copied_to(out2)|copied_to(out3);
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }
#endif

    {
        std::string   in("hello, copied!");
        std::string out1;
        std::string out2;
        std::string out3;
        in|copied_to(std::back_inserter(out1));
        in|copied_to(std::back_inserter(out2))|copied_to(std::back_inserter(out3));
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }

    {
        std::string in("hello, copied_to!");
        std::string out = in|copied;
        BOOST_CHECK( oven::equals(in, out) );
    }

#if 0 // rejected
    {
        std::stringstream ss;
        std::string ans("abcdefg");
        ss << ans;

        std::vector<char> out = ans|copied;
        oven::make_istream_range<char>(ss)|copied_to(out);
        BOOST_CHECK( oven::equals(out, ans) );
    }
#endif

#if 0 // illegal
    {
        std::string rng("abcdefg");
        std::vector<char> vec(rng|copied);
        BOOST_CHECK( oven::equals(vec, rng) );
    }
#endif
    { // 'boost::array'
        int const src[3] = { 1,2,3 };
        int const ans[5] = { 1,2,3,0,0 };
        boost::array<int, 5> arr = src|copied;
        BOOST_CHECK( oven::equals(arr, ans) );
    }

    {
        typedef std::vector<int>  row;
        typedef std::vector<row>  matrix;

        ::convertible_to_any x;
#if 0 // not guaranteed to compile. GCC actually fails.
        matrix m(&x, &x+1);
#endif
        matrix m = make_iter_range(&x, &x+1)|copied;
    }
}


inline
std::vector<int> fun()
{
    namespace oven = pstade::oven;
    using namespace oven;
    return oven::counting(3, 10)|copied;
}


// extension test
//

#include <pstade/oven/extension.hpp>


namespace xxx {

    struct X{ };

}

namespace pstade_oven_extension {

    template< >
    struct Range< xxx::X >
    {
        template< class X, class From >
        X copy(From& rng)
        {
            (void)rng;
            return xxx::X();
        }

        template< class X >
        struct associate
        {
            typedef int *mutable_iterator;
            typedef int *constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X&)
        {
            return 0;
        }

        template< class Iterator, class X >
        Iterator end(X&)
        {
            return 0;
        }
    };

}

PSTADE_OVEN_EXTENSION_OF_TYPE((xxx)(X))


void test_extension()
{
    using namespace pstade;
    using namespace oven;

    xxx::X x = std::string()|copied;
    (void)x;
}


void pstade_minimal_test()
{
    ::test_();
    ::test_extension();
}
