#ifndef PSTADE_TOMATO_ATL_BASE_HPP
#define PSTADE_TOMATO_ATL_BASE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <atlbase.h>
#include "./config.hpp" // ATL_VER


#if (PSTADE_TOMATO_ATL_VER < 0x0700)

    #include <pstade/gravy/sdk/windows.hpp>

    namespace ATL {

        inline void * __stdcall __AllocStdCallThunk()
	    {
		    return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
	    }

	    inline void __stdcall __FreeStdCallThunk(void *p)
	    {
		    ::HeapFree(::GetProcessHeap(), 0, p);
	    }

    }

    #pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")

#endif // (PSTADE_TOMATO_ATL_VER < 0x0700)



#endif
