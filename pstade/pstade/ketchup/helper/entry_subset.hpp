#ifndef PSTADE_KETCHUP_HELPER_ENTRY_SUBSET_HPP
#define PSTADE_KETCHUP_HELPER_ENTRY_SUBSET_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <pstade/is_debug.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace ketchup {


struct helper_entry_subset
{

	template< class T >
	struct assert_entry
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			BOOST_ASSERT(T::value);
			return false;
		}
	};

	template< class Dummy = boost::mpl::void_ >
	struct empty_entry : assert_entry<boost::mpl::true_>
	{
	};

	template< class Entry, class On = boost::mpl::true_ >
	struct debug_entry
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			typedef typename
			boost::mpl::eval_if< boost::mpl::and_< pstade::is_debug<>, On >,
				boost::mpl::identity< Entry >,
				boost::mpl::identity< empty_entry<> >
			>::type entry_t;

			return entry_t::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
		}
	};

	template< class Entry >
	struct identity_entry
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			return Entry::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);
		}
	};

	template< class IDs >
	struct assert_valid_msg_map_id
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (!IDs::contains(dwMsgMapID))
			{
				BOOST_ASSERT(false && "invalid message map ID");
			}

			return false;
		}
	};

	template< UINT msg >
	struct handle_message
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (msg == uMsg)
			{
				return true;
			}

			return false;
		}
	};
	
	template< UINT msg >
	struct defwindowproc_message
	{
		template< class Derived >
		static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
		{
			pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

			if (msg == uMsg)
			{
				return derived.DefWindowProc(uMsg, wParam, lParam);
			}

			return false;
		}
	};

}; // struct helper_entry_subset


} } // namespace pstade::ketchup


#endif
