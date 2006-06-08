#ifndef PSTADE_KETCHUP_CORE_ACCESS_HPP
#define PSTADE_KETCHUP_CORE_ACCESS_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#include <boost/type.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/boolean_cast.hpp>
#include <pstade/unused.hpp>
#include "./process_window_message_fwd.hpp"


namespace pstade { namespace ketchup {


struct chain_msg_map_entry_set;


class access
{

#if 1 // defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

public:

#else

    template< class MessageProcessor, class Derived >
    friend BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID);

    // I don't know how to friendify an inner class
    template< class ChainClass, DWORD msgMapID >
    friend struct chain_msg_map_entry_set::chain_msg_map_alt;
    
#endif // defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)

    template< class MessageProcessor, class Derived >
    static BOOL process_window_message(const MessageProcessor& processor, Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        pstade::unused(processor);

        return tomato::boolean(processor.end_msg_map.process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID));
    }

    // Note:
    //   As this code seems to be difficult for broken compilers,
    //   BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE cannot work around BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS.
    template< class ChainClass, class msgMapID_t, class Derived >
    static bool chain_msg_map_alt(
        Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID,
        boost::type<ChainClass>, msgMapID_t
    )
    {
        pstade::unused(dwMsgMapID);

        return tomato::boolean(derived.ChainClass::ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult, msgMapID_t::value));
    }

    // Note:
    //   CDynamicChain must be derived as public, but what if CallChain were private? So I define...
    template< class dynaChainID_t, class Derived >
    static bool chain_msg_map_dynamic(
        Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID,
        dynaChainID_t
    )
    {
        pstade::unused(dwMsgMapID);

        return tomato::boolean(derived.ATL::CDynamicChain::CallChain(dynaChainID_t::value, hWnd, uMsg, wParam, lParam, lResult));
    }

}; // class access


} } // namespace pstade::ketchup


#endif
