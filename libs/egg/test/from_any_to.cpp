#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/from_any_to.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/any.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/is_same.hpp>
#include <pstade/egg/do_swap.hpp>


using pstade::any_ref;
using pstade::any_cref;
using pstade::any_movable;
using pstade::egg::do_swap;
using pstade::egg::is_same;
using pstade::egg::xp_from_any_to;


void test_from_any()
{
    using pstade::egg::from_any;

    {
        int i = 3;
        any_ref a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( is_same(*o, i) );

        // convertible type is no longer allowed.
        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( !co );

        {
            boost::optional<int &> o = xp_from_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( is_same(*o, i) );

            // convertible type is no longer allowed.
            boost::optional<int const &> co = xp_from_any_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( !co );
        }

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int const i = 3;
        any_ref a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( !o );

#if !defined(__GNUC__)
        // for some reason, copy-initialization doesn't work.
        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == 3 );
        BOOST_CHECK( is_same(*co, i) );
#endif 

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int const i = 3;
        any_cref a = i;

#if !defined(__GNUC__)
        // for some reason, copy-initialization doesn't work.
        boost::optional<int const &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( is_same(*o, i) );
#endif

        boost::optional<int &> q = from_any(a);
        BOOST_CHECK( !q );
        
        boost::optional<char &> q_ = from_any(a);
        BOOST_CHECK( !q_ );
    }
    {
        std::auto_ptr<int> i(new int(3));
        any_movable a = i;

        boost::optional<std::auto_ptr<int> &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( **o == 3 );
        BOOST_CHECK( **o = 9 );
        BOOST_CHECK( **o == 9 );

        {
            boost::optional<std::auto_ptr<int> &> o = xp_from_any_to< boost::optional<std::auto_ptr<int> &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( **o == 9 );
            BOOST_CHECK( **o = 3 );
            BOOST_CHECK( **o == 3 );
        }


        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
    }
    {
        int i = 3;
        boost::any a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( o );
        BOOST_CHECK( *o == i );

        boost::optional<int const &> co = from_any(a);
        BOOST_CHECK( co );
        BOOST_CHECK( *co == i );

        {
            boost::optional<int &> o = xp_from_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( o );
            BOOST_CHECK( *o == i );

            boost::optional<int const &> co = xp_from_any_to< boost::optional<int const &> >()(a);
            BOOST_CHECK( co );
            BOOST_CHECK( *co == i );
        }

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
        boost::optional<char const &> cq = from_any(a);
        BOOST_CHECK( !cq );
    }
    {
        int i = 3;
        boost::any const a = i;

        boost::optional<int &> o = from_any(a);
        BOOST_CHECK( !o );
        {
            boost::optional<int &> o = xp_from_any_to< boost::optional<int &> >()(a);
            BOOST_CHECK( !o );
        }

        boost::optional<char &> q = from_any(a);
        BOOST_CHECK( !q );
        boost::optional<char const &> cq = from_any(a);
        BOOST_CHECK( !cq );
    }
}


void test_any_to()
{
    {
        int i = 10;
        boost::any a(i);

        int & i_ = pstade::egg::any_to<int>(a);
        BOOST_CHECK(i_ == 10);
    }
    {
        int i = 10;
        boost::any const a(i);

        int const & i_ = pstade::egg::any_to<int const>(a);
        BOOST_CHECK(i_ == 10);
    }
}


void pstade_unit_test()
{
    test_from_any();
    test_any_to();
}
