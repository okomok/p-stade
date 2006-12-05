#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define _ATL_NO_AUTOMATIC_NAMESPACE


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/atl.hpp> // can be placed first. VC++ ignores, though.


#include <map>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/metafunctions.hpp>
#include <pstade/oven/reverse_range.hpp>


#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/coll.hpp>


#include <pstade/const.hpp>


namespace oven = pstade::oven;
using namespace oven;


// Hmm, CPair is neither accessible nor CopyConstructible.
// How can I test!?


template< class MfcMap, class AssocContainer >
void init_map(MfcMap& map, AssocContainer const& sample)
{
    typedef typename range_iterator<PSTADE_CONST(AssocContainer)>::type iter_t;

    for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
        map.SetAt(it->first, it->second);
    }

    BOOST_ASSERT(oven::distance(map) == oven::distance(sample));
}


template< class MfcMap, class AssocContainer >
void init_multimap(MfcMap& map, AssocContainer const& sample)
{
    typedef typename range_iterator<PSTADE_CONST(AssocContainer)>::type iter_t;

    for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
        map.Insert(it->first, it->second);
    }

    BOOST_ASSERT(oven::distance(map) == oven::distance(sample));
}


template< class AssocContainer, class StdPair >
bool has_pair(AssocContainer const& ac, StdPair const& p)
{
    typedef typename range_iterator<PSTADE_CONST(AssocContainer)>::type iter_t;

    for (iter_t it = boost::const_begin(ac), last = boost::const_end(ac); it != last; ++it) {
        if (it->first == p.first && it->second == p.second)
            return true;
    }

    return false;
}


// CRBTree provides no easy access function, but yes, it is the range!
template< class AtlMap, class KeyT, class MappedT >
bool has_key_and_mapped(AtlMap& map, const KeyT& k, const MappedT m)
{
    typedef typename range_iterator<AtlMap>::type iter_t;

    for (iter_t it = boost::begin(map), last = boost::end(map); it != last; ++it) {
        if (it->m_key == k && it->m_value == m)
            return true;
    }

    return false;
}


template< class AtlMap, class AssocContainer >
bool test_atl_map(AtlMap& map, const AssocContainer& sample)
{
    PSTADE_CONCEPT_ASSERT((Forward<AtlMap>));

    typedef typename range_iterator<AtlMap>::type iter_t;
    typedef typename range_iterator<PSTADE_CONST(AssocContainer)>::type siter_t;

    bool result = true;

    result = result && (oven::distance(map) == oven::distance(sample));
    if (!result)
        return false;

    {
        for (iter_t it = boost::begin(map), last = boost::end(map); it != last; ++it) {
            result = result && ::has_pair(sample, std::make_pair(it->m_key, it->m_value));
        }
    }

    {
        for (siter_t it = boost::begin(sample), last = boost::end(sample); it != last; ++it) {
            result = result && ::has_key_and_mapped(map, it->first, it->second);
        }
    }

    return result;
}


template< class Map >
void bidirectional_assertion()
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Map>));
    // PSTADE_CONCEPT_ASSERT((Readable<Map>)); CPair is not CopyConstructible.
}


void test()
{
#if (_ATL_VER >= 0x0700)

    std::map<int, std::string> sample; {
        sample[0] = "hello";
        sample[1] = "range";
        sample[2] = "atl";
        sample[3] = "mfc";
        sample[4] = "collections";
    }

    {
        typedef ATL::CRBMap<int, std::string> rng_t;
        ::bidirectional_assertion<rng_t>();

        rng_t rng;
        ::init_map(rng, sample);
        BOOST_CHECK( ::test_atl_map(rng, sample) );

        {
            ATL::CRBTree<int, std::string>& rng_(rng);
            BOOST_CHECK( ::test_atl_map(rng_, sample) );
        }
    }
    {
        typedef ATL::CRBMultiMap<int, std::string> rng_t;
        ::bidirectional_assertion<rng_t>();

        rng_t rng;
        ::init_multimap(rng, sample);
        BOOST_CHECK( ::test_atl_map(rng, sample) );
    }
    {
        typedef ATL::CAtlMap<int, std::string> rng_t;

        rng_t rng;
        ::init_map(rng, sample);
        BOOST_CHECK( ::test_atl_map(rng, sample) );
    }

#endif // (_ATL_VER >= 0x0700)
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
