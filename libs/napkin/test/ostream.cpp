#include <pstade/vodka/drink.hpp>


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/napkin/ostream.hpp>
#include <sstream>
#include <pstade/minimal_test.hpp>


void pstade_minimal_test()
{
    using namespace pstade::napkin;

    {
        std::stringstream sout;

        ostream os1(sout);
        BOOST_CHECK( !os1.empty() );
        BOOST_CHECK( os1.contains<std::stringstream>() );
        std::stringstream& sout_ = os1.content<std::stringstream>();
        sout_ << "xxx";
        BOOST_CHECK( sout.str() == "xxx" );

        os1 = boost::none;
        os1 << "xxx"; // no effect
        BOOST_CHECK( sout.str() == "xxx" );

        os1 = sout;
        os1 << "xxx";
        BOOST_CHECK( sout.str() == "xxxxxx" );

        {
            ostream os2 = os1; // just a copy-initialization
            BOOST_CHECK( !os2.empty() );
            BOOST_CHECK( os2.contains<std::stringstream>() );
            std::stringstream& sout_ = os2.content<std::stringstream>();
            sout_ << "xxx";
            BOOST_CHECK( sout.str() == "xxxxxxxxx" );
        }
        {
            ostream os2;
            os2.reset(os1); // type erasure!
            BOOST_CHECK( !os2.empty() );
            BOOST_CHECK( os2.contains<ostream>() );
            ostream& os1_ = os2.content<ostream>();
            os1_ << "xxx";
            BOOST_CHECK( sout.str() == "xxxxxxxxxxxx" );
        }
    }
}
