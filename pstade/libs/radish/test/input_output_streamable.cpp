#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Radish
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/radish/input_streamable.hpp>
#include <pstade/radish/output_streamable.hpp>


#include <string>
#include <sstream>


using namespace pstade;


struct xxx :
    private radish::output_streamable<xxx>
{
    xxx() :
        m_str("xxx")
    { }

private:
    std::string m_str;

    template< class OStream > friend
    void pstade_radish_output(xxx const& self, OStream& os)
    {
        os << self.m_str;
    }
};


struct yyy :
    private radish::output_streamable<yyy>,
    xxx
{
private:
    template< class OStream > friend
    void pstade_radish_output(yyy const&, OStream& os)
    {
        os << "yyy";
    }
};


struct aaa :
    private radish::input_streamable<aaa>
{
    char m_value;
private:
    template< class IStream > friend
    void pstade_radish_input(aaa& self, IStream& is)
    {
        is >> self.m_value;
    }
};


struct bbb :
    private radish::input_streamable<bbb>,
    aaa
{
    int m_value;
private:
    template< class IStream > friend
    void pstade_radish_input(bbb& self, IStream& is)
    {
        is >> self.m_value;
    }
};


void test()
{
    {
        std::stringstream ss;
        ss << xxx() << yyy();
        BOOST_CHECK( ss.str() == "xxxyyy" );
    }

    {
        std::stringstream ss;
        ss << "a 1";
        aaa a; bbb b;
        ss >> a >> b;
        BOOST_CHECK( a.m_value == 'a' );
        BOOST_CHECK( b.m_value == 1   );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
