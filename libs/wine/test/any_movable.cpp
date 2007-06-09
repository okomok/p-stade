#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/any_movable.hpp>


using pstade::any_movable;


void test()
{
    {
        any_movable m(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( !m.empty() );
        BOOST_CHECK( *(m.base< std::auto_ptr<int> >()) == 3 );
        BOOST_CHECK( *pstade::any_movable_cast< std::auto_ptr<int> >(m) == 3 );
        m.type();
    }
    {
        any_movable m = std::auto_ptr<int>(new int(3));
        BOOST_CHECK( *(m.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable m;
        BOOST_CHECK( m.empty() );
        m = any_movable(std::auto_ptr<int>(new int(3)));
        BOOST_CHECK( *(m.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable m(std::auto_ptr<int>(new int(3)));
        std::auto_ptr<int> ap(m.base< std::auto_ptr<int> >());
        BOOST_CHECK( *ap == 3 );
    }
    {
        any_movable m(std::auto_ptr<int>(new int(3)));
        any_movable m_(m);
        BOOST_CHECK( *(m_.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable m(std::auto_ptr<int>(new int(3)));
        any_movable m_ = m;
        BOOST_CHECK( *(m_.base< std::auto_ptr<int> >()) == 3 );
    }
    {
        any_movable m(std::auto_ptr<int>(new int(3)));
        any_movable m_; m_ = m;
        BOOST_CHECK( *(m_.base< std::auto_ptr<int> >()) == 3 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
