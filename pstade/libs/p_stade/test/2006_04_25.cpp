#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


typedef struct _MYGUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} MYGUID,*MYREFGUID,*MYLPGUID;


#define PSTADE_GUID(Name, L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8) \
    inline \
    const MYGUID& pstade_tomato_guid_of_ ## Name () \
    { \
        static const MYGUID iid = { \
            L, W1, W2, { B1, B2, B3, B4, B5, B6, B7, B8 } \
        }; \
        return iid; \
    } \
    namespace { \
        extern const MYGUID& Name = pstade_tomato_guid_of_ ## Name (); \
    } \
/**/


#define PSTADE_GUID_VALUE(Name, L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8) \
    typedef ::myguid_c<L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8> Name; \
/**/

	template<
		unsigned long L, unsigned short W1, unsigned short W2,
		unsigned char B1, unsigned char B2, unsigned char B3, unsigned char B4,
		unsigned char B5, unsigned char B6, unsigned char B7, unsigned char B8
	>
	struct myguid_c
	{
		static const MYGUID value;
	};

	template<
		unsigned long L, unsigned short W1, unsigned short W2,
		unsigned char B1, unsigned char B2, unsigned char B3, unsigned char B4,
		unsigned char B5, unsigned char B6, unsigned char B7, unsigned char B8
	>
	const MYGUID
	myguid_c<L, W1, W2, B1, B2, B3, B4, B5, B6, B7, B8>::value =
	{
		L, W1, W2, { B1, B2, B3, B4, B5, B6, B7, B8 }
	};


PSTADE_GUID(MYIID_IPStade,
	0xda73ce21, 0x82f3, 0x4b8a, 0x83, 0xde, 0x87, 0x3d, 0x9c, 0x80, 0x9e, 0x90)

PSTADE_GUID_VALUE(MYIID_IPStade_c,
	0xda73ce21, 0x82f3, 0x4b8a, 0x83, 0xde, 0x87, 0x3d, 0x9c, 0x80, 0x9e, 0x90)


template< class T, const MYGUID *piid >
class CComQIPtr;

struct IPStade
{
    virtual void FuncA() = 0;
};


void test()
{
	typedef ::CComQIPtr<IPStade, &MYIID_IPStade> ptr_t_illegal; // VC++Ç≈ÇÕí ÇÈÇ™ïsê≥
	typedef ::CComQIPtr<IPStade, &MYIID_IPStade_c::value> ptr_t; // OK
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
