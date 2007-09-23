#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/any_output_iterator.hpp>
#include <pstade/minimal_test.hpp>


#include <vector>
#include <list>
#include <algorithm> // copy
#include <pstade/oven/equals.hpp>
#include <string>
#include <iterator>
#include <sstream>
#include <pstade/egg/do_swap.hpp>


namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        typedef std::back_insert_iterator< std::vector<char> > back_insert_iter_t;
        std::vector<char> v;
        any_output_iterator<char &> oi(std::back_inserter(v));
        BOOST_CHECK(oi.has_base< back_insert_iter_t >());
        BOOST_CHECK(!oi.has_base< int * >());
        BOOST_CHECK(oi.type() == typeid(back_insert_iter_t));

        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), oi);

        BOOST_CHECK( equals(v, src) );
    }
    {
        typedef std::back_insert_iterator< std::vector<char> > back_insert_iter_t;
        std::vector<char> v;
        any_output_iterator<char &> oi(std::back_inserter(v));
        BOOST_CHECK(oi.has_base< back_insert_iter_t >());
        BOOST_CHECK(!oi.has_base< int * >());

        back_insert_iter_t b = oi.base< std::back_insert_iterator< std::vector<char> > >();
        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), b);
        BOOST_CHECK( equals(v, src) );
    }
    {
        std::vector<char> v;
        any_output_iterator<char &> oi;
        oi = std::back_inserter(v);

        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), oi);

        BOOST_CHECK( equals(v, src) );
    }
    {
        std::stringstream sout;
        any_output_iterator<char> oi;
        oi = std::ostream_iterator<char>(sout); // assignment can avoid vexing parse.
        BOOST_CHECK(oi.has_base< std::ostream_iterator<char> >());
        BOOST_CHECK(!oi.has_base< int * >());

        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), oi);

        BOOST_CHECK( equals(sout.str(), src) );
    }
    {
        any_output_iterator<char const&> oi;
        BOOST_CHECK( oi.empty() );
        oi = boost::none;
        BOOST_CHECK( oi.empty() );
        BOOST_CHECK(oi.type() != typeid(int *));
        BOOST_CHECK(!oi.has_base<int *>());
        int arr[7];
        oi = &arr[0];
        BOOST_CHECK(oi.type() == typeid(int *));
        BOOST_CHECK(oi.has_base<int *>());

        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), oi);

        BOOST_CHECK( equals(arr, src) );
    }
    {
        any_output_iterator<char const&> oi;
        any_output_iterator<char const&> oj;
        oj = oi; // just copy-assignment
        BOOST_CHECK(oj.empty());

        oj.reset(oi); // not copy-assignment! - (1)
        BOOST_CHECK( !oj.empty() );
        BOOST_CHECK(oj.type() == typeid(any_output_iterator<char const&>));
        BOOST_CHECK(!oi.has_base<int *>());

        BOOST_CHECK( oi.empty() );
        int arr[7];
        oi = &arr[0];
        BOOST_CHECK(oi.type() == typeid(int *));
        BOOST_CHECK(oi.has_base<int *>());

        // notice the base of oj in (1) is a copy, hence you need to reset it here.
        oj.reset(oi);

        std::string src("abcdefg");
        std::copy(src.begin(), src.end(), oj); // through oj.

        BOOST_CHECK( equals(arr, src) );
    }
    {
        std::vector<char> vj;
        std::list<char> vi;
        any_output_iterator<char> oi;
        any_output_iterator<char> oj;
        pstade::egg::do_swap(oi, oj); // no effect
        oi = std::back_inserter(vj);
        oj = std::back_inserter(vi);
        pstade::egg::do_swap(oi, oj);

        std::string srci("abcdefg");
        std::string srcj("hijklmn");
        std::copy(srci.begin(), srci.end(), oi);
        std::copy(srcj.begin(), srcj.end(), oj);

        BOOST_CHECK(equals(vi, srci));
        BOOST_CHECK(equals(vj, srcj));
    }
    {
        std::string src("abcdefg");
        any_output_iterator<char const&> oi(src.begin());
        *oi++ = 'x';
        BOOST_CHECK( src == "xbcdefg" );
        *oi++ = 'y';
        BOOST_CHECK( src == "xycdefg" );

        *oi = 'z';
        BOOST_CHECK( src == "xyzdefg" );

        any_output_iterator<char const &> oj(oi++);
        BOOST_CHECK( *oi.base<std::string::iterator>() == 'd' );

        *oj = '0';
        BOOST_CHECK( src == "xyz0efg" );
    }
}
