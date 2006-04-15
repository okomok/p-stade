#ifndef PSTADE_KETCHUP_WIN_FORWARDING_AND_REFLECTION_ENTRY_SET_HPP
#define PSTADE_KETCHUP_WIN_FORWARDING_AND_REFLECTION_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/void.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace ketchup {


struct forwarding_and_reflection_entry_set
{

	struct forward_notifications
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			BOOL bHandled = TRUE;
			lResult = derived.ForwardNotifications(uMsg, wParam, lParam, bHandled);
			if(bHandled)
				return true;
		}
	};

	template< class Dummy = boost::mpl::void_ >
	struct reflect_notifications
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			BOOL bHandled = TRUE;
			lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
			if(bHandled)
				return true;
		}
	};

	template< class Dummy = boost::mpl::void_ >
	struct default_reflection_handler
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			return tomato::boolean(Derived::DefaultReflectionHandler(hWnd, uMsg, wParam, lParam, lResult));
		}
	};

}; // forwarding_and_reflection_entry_set


} } // namespace pstade::ketchup


#endif
