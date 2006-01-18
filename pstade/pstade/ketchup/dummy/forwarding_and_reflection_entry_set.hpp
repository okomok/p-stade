#pragma once

#include <boost/mpl/void.hpp>
#include <pstade/unused.hpp>
#include <pstade/tomato/cast/boolean_cast.hpp>

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

			return tomato::auto_bool(Derived::DefaultReflectionHandler(hWnd, uMsg, wParam, lParam, lResult));
		}
	};

}; // forwarding_and_reflection_entry_set


} } // namespace pstade::ketchup
