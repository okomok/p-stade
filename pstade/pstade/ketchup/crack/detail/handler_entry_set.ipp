
#if !defined(KETCHUP_wtype_ns)
	#error ketchup::handler_entry_set fatal error - no KETCHUP_wtype_ns given.
#endif

#include "atlcrack_h.ipp"
#include "atlcrack_h_not_handled.ipp"

///////////////////////////////////////////////////////////////////////////////
// command_id_handler_simple
//
template<
	UINT id,
	void (Derived::*func)()
>
struct command_id_handler_simple
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		(derived); (hWnd); (uMsg); (wParam); (lParam); (lResult); (dwMsgMapID);

		if (uMsg == WM_COMMAND && id == LOWORD(wParam))
		{
			(derived.*func)();
			lResult = 0;
			return true;
		}
		return false;
	}
};

template<
	UINT id,
	void (Derived::*func)()
>
struct command_id_handler_simple_not_handled
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		(derived); (hWnd); (uMsg); (wParam); (lParam); (lResult); (dwMsgMapID);

		if (uMsg == WM_COMMAND && id == LOWORD(wParam))
		{
			(derived.*func)();
			lResult = 0;
		}
		return false;
	}
};

