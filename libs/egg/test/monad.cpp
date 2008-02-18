#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: http://haskell.g.hatena.ne.jp/muscovyduck/20060812


#include <boost/egg/monad/optional.hpp>
#include <boost/egg/monad/core.hpp>
#include <boost/egg/infix.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <map>
#include <string>
#include <boost/optional/optional.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct little_lookup
{
    template<class Myself, class Key, class Map>
    struct apply
    {
        typedef boost::optional<typename Map::mapped_type> type;
    };

    template<class Result, class Key, class Map>
    Result call(Key key, Map map) const
    {
        typename Map::iterator it = map.find(key);
        if (it != map.end())
            return it->second;
        else
            return Result();
    }
};

result_of_curry2< function<little_lookup, by_value> >::type
const lookup = BOOST_EGG_CURRY2_L {{}} BOOST_EGG_CURRY2_R;


void pstade_minimal_test()
{
    typedef std::map<std::string, std::string> imap_t;
    typedef std::map<std::string, imap_t> map_t;
        
    map_t config;
    {
        imap_t im;
        im["path"] = "/var/app/db";
        im["encoding"] = "euc-jp";
        config["database"] = im;
    }
    {
        imap_t im;
        im["cgiurl"] = "/app";
        im["rewrite"] = "True";
        config["urlmapper"] = im;
    }
    {
        imap_t im;
        im["path"] = "/var/app/template";
        config["template"] = im;
    }

    using namespace infix;

    BOOST_CHECK( !(
        X_monad_return< boost::optional<map_t> >()(config)
            ^monad_bind^ lookup("foo")
            ^monad_bind^ lookup("encoding")
    ) );

    boost::optional<map_t> r = monad_return(config); // automatic deduction.

    BOOST_CHECK( *(
        monad_return(config)
            ^monad_bind^ lookup("database")
            ^monad_bind^ lookup("encoding")
    ) == "euc-jp");
}
