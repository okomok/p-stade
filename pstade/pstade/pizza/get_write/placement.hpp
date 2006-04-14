#ifndef PSTADE_PIZZA_GET_WRITE_PLACEMENT_HPP
#define PSTADE_PIZZA_GET_WRITE_PLACEMENT_HPP


// PStade.Pizza
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(_WIN32_WCE)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/size_initialize.hpp>
#include "./window_placement.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_placement(Profile& pr, HWND hWnd)
{
	BOOST_ASSERT(diet::valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::size_initialize(wndpl);
	PSTADE_REQUIRE(::GetWindowPlacement(hWnd, &wndpl));

	pizza::write_window_placement(pr, wndpl);
}


template< class Profile >
bool get_placement(Profile& pr, HWND hWnd)
{
	BOOST_ASSERT(diet::valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::size_initialize(wndpl);

	if (!pizza::get_window_placement(pr, wndpl))
		return false; // not found

	PSTADE_REQUIRE(::SetWindowPlacement(hWnd, &wndpl));
	return true;
}


// showCmd service
//
template< class Profile >
void get_placement_show(Profile& pr, HWND hWnd, int showCmd)
{
	BOOST_ASSERT(diet::valid(hWnd));

	if (!pizza::get_placement(pr, hWnd)) // not found
		::ShowWindow(hWnd, showCmd);
}


// give the chance
//
template< class Profile, class Functor >
void get_placement_after(Profile& pr, HWND hWnd, int showCmd, Functor fun)
{
	BOOST_ASSERT(diet::valid(hWnd));

	WINDOWPLACEMENT wndpl;
	tomato::size_initialize(wndpl);

	if (pizza::get_window_placement(pr, wndpl)) {
		showCmd = wndpl.showCmd; // show it later
		wndpl.showCmd = SW_HIDE;
		PSTADE_REQUIRE(::SetWindowPlacement(hWnd, &wndpl));
	}

	fun();
	::ShowWindow(hWnd, showCmd);
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
