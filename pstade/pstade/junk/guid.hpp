#ifndef PSTADE_TOMATO_GUID_HPP
#define PSTADE_TOMATO_GUID_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// But template arguments needs non-reference.


#include <boost/microsoft/sdk/basetyps.hpp> // IID
#include <boost/preprocessor/cat.hpp>


#define PSTADE_TOMATO_GUID(Name, L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8) \
    typedef pstade::tomato::guid<L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8> Name; \
/**/


namespace pstade { namespace tomato {


template<
	unsigned long L, unsigned short W1, unsigned short W2,
	unsigned char B1, unsigned char B2, unsigned char B3, unsigned char B4,
	unsigned char B5, unsigned char B6, unsigned char B7, unsigned char B8
>
struct guid
{
	static const GUID value;
};


template<
	unsigned long L, unsigned short W1, unsigned short W2,
	unsigned char B1, unsigned char B2, unsigned char B3, unsigned char B4,
	unsigned char B5, unsigned char B6, unsigned char B7, unsigned char B8
>
const GUID
guid<L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8>::value =
{
	L, W1, W2, { B1, B2, B3, B4, B5, B6, B7, B8 }
};


} } // namespace pstade::tomato


// Oops, ATL::CComQIPtr etc needs constant as template arguments...
// VC accepts, but it's illegal.
//
#define PSTADE_TOMATO_USELESS_GUID(Name, L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8) \
    inline \
    const IID& BOOST_PP_CAT(pstade_tomato_guid_of_, Name)() \
    { \
        static const IID iid = { \
            L, W1, W2, { B1, B2, B3, B4, B5, B6, B7, B8 } \
        }; \
        return iid; \
    } \
    namespace { \
        extern const IID& Name = BOOST_PP_CAT(pstade_tomato_guid_of_, Name)(); \
    } \
/**/


#endif
