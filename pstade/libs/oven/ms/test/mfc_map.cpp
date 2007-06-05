#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#define _WIN32_WINNT 0x0400 // for <boost/test/minimal.hpp>
#define _AFXDLL

#include <afx.h>


#include <algorithm>
#include <map>
#include <string>
#include <boost/range.hpp>

#include <afxcoll.h>
#include <afxtempl.h>


#include <boost/test/minimal.hpp>


#include "../../test/detail/v1_tests.hpp"
#include <pstade/oven/mfc.hpp>


#include "../../test/detail/v1_core.hpp"
#include <pstade/oven/outdirected.hpp>
#include <pstade/oven/const_refs.hpp>


#include <pstade/deduced_const.hpp>


namespace oven = pstade::oven;
using namespace oven;


template< class MfcMap, class AssocContainer >
void init_map(MfcMap& map, AssocContainer const& sample)
{
    typedef typename range_iterator<PSTADE_DEDUCED_CONST(AssocContainer)>::type iter_t;

    for (iter_t it = boost::const_begin(sample), last = boost::const_end(sample); it != last; ++it) {
        map.SetAt(it->first, it->second);
    }

    BOOST_ASSERT(oven::distance(map) == oven::distance(sample));
}


template< class AssocContainer, class StdPair >
bool has_pair(AssocContainer const& ac, StdPair const& p)
{
    typedef typename range_iterator<PSTADE_DEDUCED_CONST(AssocContainer)>::type iter_t;

    for (iter_t it = boost::const_begin(ac), last = boost::const_end(ac); it != last; ++it) {
        if (it->first == p.first && it->second == p.second)
            return true;
    }

    return false;
}


template< class MfcMap, class AssocContainer >
bool test_mfc_map(MfcMap& map, AssocContainer const& sample)
{
    PSTADE_CONCEPT_ASSERT((Forward<MfcMap>));

    typedef typename range_iterator<MfcMap>::type iter_t;
    typedef typename range_iterator<PSTADE_DEDUCED_CONST(AssocContainer)>::type siter_t;

    bool result = true;

    result = result && (oven::distance(map) == oven::distance(sample));
    if (!result)
        return false;

    {
        for (iter_t it = boost::begin(map), last = boost::end(map); it != last; ++it) {
            result = result && ::has_pair(sample, *it);
        }
    }

    {
        for (siter_t it = boost::begin(sample), last = boost::end(sample); it != last; ++it) {
            result = result && (map[it->first] == it->second);
        }
    }

    return result;
}


template< class MfcMap, class AssocContainer >
bool test_mfc_CPair_map(MfcMap& map, const AssocContainer& sample)
{
    PSTADE_CONCEPT_ASSERT((Forward<MfcMap>));

    typedef typename range_iterator<MfcMap>::type iter_t;
    typedef typename range_iterator<PSTADE_DEDUCED_CONST(AssocContainer)>::type siter_t;

    bool result = true;

    result = result && (oven::distance(map) == oven::distance(sample));
    if (!result)
        return false;

    {
        for (iter_t it = boost::begin(map), last = boost::end(map); it != last; ++it) {
            result = result && ::has_pair(sample, std::make_pair(it->key, it->value));
        }
    }

    {
        for (siter_t it = boost::begin(sample), last = boost::end(sample); it != last; ++it) {
            result = result && (map[it->first] == it->second);
        }
    }

    return result;
}


void test()
{
    { // CMapPtrToWord
		std::map<void *, WORD> sample;
        int o0, o1, o2, o3, o4;
        sample[&o0] = 15, sample[&o1] = 14, sample[&o2] = 3, sample[&o3] = 6, sample[&o4] = 1;

        typedef CMapPtrToWord rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
    { // CMapPtrToPtr
        std::map<void *, void*> sample;
        int o0, o1, o2, o3, o4;
        sample[&o0] = &o3, sample[&o1] = &o2, sample[&o2] = &o1, sample[&o3] = &o0, sample[&o4] = &o4;

        typedef CMapPtrToPtr rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
    { // CMapStringToOb
        std::map< ::CString, CObject * > sample;
        CObArray o0, o1, o2, o3, o4;
        sample[ ::CString('0') ] = &o0, sample[ ::CString('1') ] = &o1, sample[ ::CString('2') ] = &o2,
        sample[ ::CString('3') ] = &o3, sample[ ::CString('4') ] = &o4;

        typedef CMapStringToOb rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
    { // CMapStringToString
        std::map< ::CString, ::CString > sample;
        CString o0('a'), o1('b'), o2('c'), o3('d'), o4('e');
        sample[ ::CString('0') ] = o0, sample[ ::CString('1') ] = o1, sample[ ::CString('2') ] = o2,
        sample[ ::CString('3') ] = o3, sample[ ::CString('4') ] = o4;

        typedef CMapStringToString rng_t;
        rng_t rng;
		::init_map(rng, sample);
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
        BOOST_CHECK( ::test_mfc_CPair_map(rng, sample) );
    #else
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    #endif
    }
    { // CMapWordToOb
        std::map< WORD, CObject * > sample;
        ::CDWordArray o0, o1, o2, o3, o4;
        sample[21] = &o3, sample[52] = &o2, sample[12] = &o1, sample[76] = &o0, sample[54] = &o4;

        typedef CMapWordToOb rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
    { // CMapWordToPtr
        std::map< WORD, void * > sample;
        ::CDWordArray o0, o1, o2, o3, o4;
        sample[21] = &o3, sample[52] = &o2, sample[12] = &o1, sample[76] = &o0, sample[54] = &o4;

        typedef CMapWordToPtr rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
    { // CMap
        std::map< int, std::string > sample;
        sample[0] = "abcde", sample[1] = "ajfie", sample[2] = "lij", sample[3] = "abc", sample[4] = "ioiu";

        typedef CMap<int, int const&, std::string, std::string const&> rng_t;
        rng_t rng;
		::init_map(rng, sample);
    #if !defined(PSTADE_APPLE_MFC_NO_CPAIR)
        BOOST_CHECK( ::test_mfc_CPair_map(rng, sample) );
    #else
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    #endif
    }
    { // CTypedPtrMap
        CString o0(_T('a')), o1(_T('c')), o2(_T('f')), o3(_T('q')), o4(_T('g'));
        int d0, d1, d2, d3, d4;
        std::map< ::CString, int * > sample;
        sample[o0] = &d0, sample[o1] = &d1, sample[o2] = &d2, sample[o3] = &d3, sample[o4] = &d4;

        typedef CTypedPtrMap< CMapStringToPtr, CString, int *> rng_t;
        rng_t rng;
		::init_map(rng, sample);
        BOOST_CHECK( ::test_mfc_map(rng, sample) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
