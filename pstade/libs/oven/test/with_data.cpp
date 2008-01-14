#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/with_data.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <pstade/oven/identities.hpp>
#include <boost/array.hpp>


namespace oven = pstade::oven;
using namespace oven;


template<class Rng, class Data>
void check_data(Rng& rng, Data const& dt)
{
    BOOST_CHECK(oven::data<Data>(rng) == dt);
}

template<class Rng, class Data>
void check_data_ref(Rng& rng, Data& dt)
{
    BOOST_CHECK(oven::data<Data &>(rng) == dt);
    BOOST_CHECK(&oven::data<Data &>(rng) == &dt); // holds by reference
}


void pstade_minimal_test()
{
    {
        std::string a("abcdefghijklmn");
        std::string b("abcdefghijklmn");

        int dt = 12;
        int cdt = 13;
        ::check_data(b|with_data(dt), dt); // value
        ::check_data_ref(b|with_data(boost::ref(dt)), dt); // refeference
        ::check_data_ref(b|with_data(boost::ref(cdt)), cdt); // const reference

        ::check_data(b|with_data(dt)|identities|with_data(boost::ref(dt))|identities, dt);
        ::check_data_ref(b|with_data(dt)|identities|with_data(boost::ref(dt))|identities, dt);
        ::check_data_ref(b|with_data(dt)|identities|with_data(boost::ref(cdt))|identities, cdt);

        test::random_access_swappable(b|with_data(dt), a);
    }
    {
        std::string a("abcdefghijklmn");
        std::string b("abcdefghijklmn");
        boost::array<char, 5000> big_data;

        test::forward_constant(b|with_data(big_data), a);
    }
    {
        test::emptiness(
            std::string()|with_data(0)
        );
    }
}
