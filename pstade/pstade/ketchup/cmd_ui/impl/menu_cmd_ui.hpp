#pragma once

#include <memory>
#include <atluser.h>
#include <pstade/candy/set.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/candy/reset.hpp>
#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/diagnostic/verify.hpp>
#include <pstade/tomato/menu/get_menu_state.hpp>
#include <pstade/tomato/menu/modify_menu.hpp>
#include <pstade/tomato/menu/set_menu_default_item.hpp>
#include <pstade/tomato/menu/mf_disabled.hpp>
#include <pstade/tomato/menu/mf_bitmap.hpp>
#include <pstade/tomato/structure/version_initialize.hpp>
#include <pstade/tomato/structure/zero_initialize.hpp>
#include "../cmd_ui.hpp"

namespace pstade { namespace ketchup {


struct menu_cmd_ui : cmd_ui
{
	HMENU get_menu() const { return m_hMenu; }
	UINT get_index() const { return m_uIndex; }

	menu_cmd_ui(UINT uID, HMENU hMenu, UINT uIndex, bool dependent) :
		cmd_ui(uID), m_hMenu(hMenu), m_uIndex(uIndex), m_dependent(dependent)
	{
		ATLASSERT(tomato::is_valid(m_hMenu));
	}

protected:
	virtual void enable_impl(bool on)
	{
		::EnableMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
			(on ? MF_ENABLED : (tomato::mf_disabled::value | MF_GRAYED)));
	}

	virtual void set_check_impl(int state)
	{
#if !defined(_WIN32_WCE)
		set_radio_check_type(false);
#endif

		::CheckMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
			(state ? MF_CHECKED : MF_UNCHECKED));
	}

#if !defined(_WIN32_WCE)
	virtual void set_radio_impl(bool on)
	{
		set_radio_check_type(true);

		::CheckMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
			(on ? MF_CHECKED : MF_UNCHECKED));
	}
#endif // !defined(_WIN32_WCE)

	virtual void set_text_impl(LPCTSTR pszText)
	{
		ATLASSERT(tomato::is_valid(pszText));

		// get current menu state so it doesn't change
		UINT uState = tomato::get_menu_state(m_hMenu, m_uIndex, MF_BYPOSITION);
		candy::remove(uState, tomato::mf_bitmap::value | MF_OWNERDRAW | MF_SEPARATOR);

		// set menu text
		MENUITEMINFO mii;
		{
			tomato::version_initialize(tomato::zero_initialize(mii));
			mii.fMask = MIIM_ID;
			tomato::api_verify(::GetMenuItemInfo(m_hMenu, m_uIndex, TRUE, &mii));
		}

		tomato::api_verify(tomato::modify_menu(m_hMenu, m_uIndex, MF_BYPOSITION |
			MF_STRING | uState, mii.wID, pszText));
	}

	virtual void set_default_impl(bool on)
	{
		// place checkmark next to menu item
		if (on)
			tomato::api_verify(tomato::set_menu_default_item(m_hMenu, m_uIndex, TRUE));
	}

	virtual bool is_dependent_impl()
	{
		return m_dependent;
	}

#if !defined(_WIN32_WCE)
private:
	void set_radio_check_type(bool on)
	{
		// Win32 stinks.

		MENUITEMINFO mii; {
			tomato::version_initialize(tomato::zero_initialize(mii));
			mii.fMask = MIIM_TYPE;
			tomato::api_verify(::GetMenuItemInfo(m_hMenu, m_uIndex, TRUE, &mii));
		}

		if (on == candy::test(mii.fType, MFT_RADIOCHECK))
			return;

		// The case of MFT_STRING; MFT_STRING == 0, so...
		std::auto_ptr<TCHAR> szString;
		if (
			!candy::test(mii.fType, MFT_BITMAP) &&
			!candy::test(mii.fType, MFT_SEPARATOR) &&
			!candy::test(mii.fType, MFT_OWNERDRAW) // Win32 documentation is broken.
		)
		{
			// get the menu string
			szString.reset(new TCHAR[mii.cch + 1]);
			mii.dwTypeData = szString.get();
			++mii.cch; 
			tomato::api_verify(::GetMenuItemInfo(m_hMenu, m_uIndex, TRUE, &mii));
		}

		if (on)
			candy::set(mii.fType, MFT_RADIOCHECK);
		else
			candy::reset(mii.fType, MFT_RADIOCHECK);

		tomato::api_verify(::SetMenuItemInfo(m_hMenu, m_uIndex, TRUE, &mii));
	}
#endif // !defined(_WIN32_WCE)

private:
	HMENU m_hMenu;
	UINT m_uIndex;
	bool m_dependent;
};


} } // namespace pstade::ketchup
