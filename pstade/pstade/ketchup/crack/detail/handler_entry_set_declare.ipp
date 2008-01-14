

#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/tomato/wtl/misc.hpp> // WTL::CSize, CPoint


#if !defined(_WTL_NO_WTYPES)
    #define KETCHUP_wtype_ns WTL
#elif (_ATL_VER < 0x0700)
    #error undef _WTL_NO_WTYPES for WTL::CSize and CPoint
#else
    #define KETCHUP_wtype_ns // ATL
    #include <pstade/tomato/atl/types.hpp>
#endif


#if !defined(_WIN32_WCE)
    #include <ras.h> // RASCONNSTATE
#else
    #if !defined(RASCONNSTATE)
        #define RASCONNSTATE enum tagRASCONNSTATE
    #endif
    // :^)
    struct LPMINMAXINFO;
    struct HDROP;
    struct LPHELPINFO;
    struct LPMDINEXTMENU;
    struct PMENUGETOBJECTINFO;
#endif
