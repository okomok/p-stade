
#ifndef _WTL_NO_WTYPES
	#define KETCHUP_wtype_ns WTL
	namespace WTL {
		class CSize;
		class CPoint;
	}
#else
	#define KETCHUP_wtype_ns // ATL
	class CSize;
	class CPoint;
#endif

#ifndef RASCONNSTATE
	#define RASCONNSTATE enum tagRASCONNSTATE
#endif

#ifdef _WIN32_WCE
	// :^)
	struct LPMINMAXINFO;
	struct HDROP;
	struct LPHELPINFO;
	struct LPMDINEXTMENU;
	struct PMENUGETOBJECTINFO;
#endif
