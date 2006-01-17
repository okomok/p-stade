
// default MFC-style
template<
	UINT id,
	void (Derived::*func)(ketchup::cmd_ui&)
>
struct cmd_ui_handler
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

		if (uMsg == ketchup::id_update_cmd_ui_message())
		{
			ketchup::cmd_ui& ui = ketchup::wParam_to_cmd_ui(wParam);
			if (ui.get_id() == id)
			{
				ui.set_handled(true);
				(derived.*func)(ui);
				if (ui.is_handled())
				{
					ketchup::set_cmd_ui_handled(lResult, true);
					return true; // make lResult alive!
				}
			}
		}

		return false;
	}
};

// independent
template<
	UINT id,
	void (Derived::*func)(ketchup::cmd_ui&)
>
struct independent_cmd_ui_handler
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

		if (uMsg == ketchup::id_update_cmd_ui_message())
		{
			ketchup::cmd_ui& ui = ketchup::wParam_to_cmd_ui(wParam);
			if (ui.get_id() == id && !ui.is_dependent())
			{
				ui.set_handled(true);
				(derived.*func)(ui);
				if (ui.is_handled())
				{
					ketchup::set_cmd_ui_handled(lResult, true);
					return true; // make lResult alive!
				}
			}
		}

		return false;
	}
};

// dependent
template<
	UINT id,
	void (Derived::*func)(ketchup::cmd_ui&)
>
struct dependent_cmd_ui_handler
{
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

		if (uMsg == ketchup::id_update_cmd_ui_message())
		{
			ketchup::cmd_ui& ui = ketchup::wParam_to_cmd_ui(wParam);
			if (ui.get_id() == id && ui.is_dependent())
			{
				ui.set_handled(true);
				(derived.*func)(ui);
				if (ui.is_handled())
				{
					ketchup::set_cmd_ui_handled(lResult, true);
					return true; // make lResult alive!
				}
			}
		}

		return false;
	}
};
