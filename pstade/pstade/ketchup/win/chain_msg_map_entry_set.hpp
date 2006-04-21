#ifndef PSTADE_KETCHUP_WIN_CHAIN_MSG_MAP_ENTRY_SET_HPP
#define PSTADE_KETCHUP_WIN_CHAIN_MSG_MAP_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/type.hpp>
#include <pstade/unused.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include "../core/access.hpp"


namespace pstade { namespace ketchup {


struct chain_msg_map_entry_set
{

    template< class ChainClass, DWORD msgMapID >
    struct chain_msg_map_alt
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            return access::chain_msg_map_alt(
                derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID,
                boost::type<ChainClass>(), boost::mpl::integral_c<DWORD, msgMapID>()
            );
        }
    };

    template< class ChainClass >
    struct chain_msg_map : chain_msg_map_alt<ChainClass, 0>
    {
    };

    template< DWORD dynaChainID >
    struct chain_msg_map_dynamic
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            return access::chain_msg_map_dynamic(
                derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID,
                boost::mpl::intergral_c<DWORD, dynaChainID>()
            );
        }
    };

    template< class F_ChainClass, DWORD msgMapID >
    struct chain_msg_map_alt_member
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            return tomato::boolean(F_ChainClass()(derived).ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID));
        }
    };

    template< class ChainFtorClass >
    struct chain_msg_map_member : chain_msg_map_alt_member<ChainFtorClass, 0>
    {
    };

}; // struct chain_msg_map_entry_set


} } // namespace pstade::ketchup


#endif
