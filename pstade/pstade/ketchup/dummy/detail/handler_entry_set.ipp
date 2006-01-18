
#include "./atlwin_h.ipp"

template<
	class F_msg,
	LRESULT (Derived::*func)(UINT,WPARAM,LPARAM,BOOL&)
>
struct registered_message_handler
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		(derived); (hWnd); (uMsg); (wParam); (lParam); (lResult); (dwMsgMapID);

		if(uMsg == F_msg()(derived))
		{
			BOOL bHandled = TRUE;
			lResult = (derived.*func)(uMsg, wParam, lParam, bHandled);
			if(bHandled)
				return true;
		}
	
		return false;
	}
};
