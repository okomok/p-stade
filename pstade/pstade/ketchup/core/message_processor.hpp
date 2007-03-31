#ifndef PSTADE_KETCHUP_CORE_MESSAGE_PROCESSOR_HPP
#define PSTADE_KETCHUP_CORE_MESSAGE_PROCESSOR_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_params_with_defaults.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/downcast.hpp>
#include "../cmd_ui/cmd_ui.hpp"
#include "../cmd_ui/dependent_value.hpp"
#include "../config/limit_message_processor_base_size.hpp"
#include "./entry_subset.hpp"
#include "./process_window_message.hpp"

#include "../cmd_ui/detail/handler_entry_set_include.ipp"
#include "../crack/detail/handler_entry_set_declare.ipp"


// Note:
//   message_processor is the ambiguity buster.
//
//   As entry_subset has only classes,
//   multiple inheritance makes no ambiguity:
//
//     struct A { struct X { }; };
//
//   A is just a namespace.
//
#pragma warning(push)
#pragma warning(disable: 4584) // base-class 'meta_unique_base<Base>' is already a base-class
//
//   But handler-entries are class templates,
//   so they makes ambiguity:
//
//     template< class T >
//     struct B { struct X { T x; }; };
//
//   B<int> and B<char> are different namespaces.
//
//   By the way, you need not care about access control
//   of entry_subset thanks to C++ Standard 11.7.


namespace pstade { namespace ketchup {


namespace message_processor_detail {


    // prepare for (Sequence == entry_subset)
    template< class Base >
    struct meta_unique_base : Base
    {
        typedef meta_unique_base type;
    };


    #define PSTADE_KETCHUP_DETAIL_MAKE_UNIQUE_BASE(z, n, unused) \
        struct BOOST_PP_CAT(unique_base, n) { }; \
    /**/

    BOOST_PP_REPEAT(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, PSTADE_KETCHUP_DETAIL_MAKE_UNIQUE_BASE, ~)


} // namespace message_processor_detail


PSTADE_ADL_BARRIER(message_processor) {

template<
    class Derived,
    BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, class BaseT, message_processor_detail::unique_base)
>
struct message_processor :
    message_processor_detail::meta_unique_base<entry_subset>::type,
    BOOST_PP_ENUM_PARAMS(PSTADE_KETCHUP_LIMIT_MESSAGE_PROCESSOR_BASE_SIZE, BaseT)
{
#if !defined(BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS)
    #include "../win/detail/handler_entry_set.ipp"
    #include "../crack/detail/handler_entry_set.ipp"
    #include "../cmd_ui/detail/handler_entry_set.ipp"
#endif

    typedef Derived _;
    typedef ketchup::cmd_ui cmd_ui;
    typedef ketchup::dependent dependent;
    typedef ketchup::independent independent;

    BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg,
        WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
    {
        Derived& d = *this|static_downcasted;

        return ketchup::process_window_message(d, hWnd, uMsg,
            wParam, lParam, lResult, dwMsgMapID);
    }

    void set_msg_handled(bool handled)
    {
        m_pstade_ketchup_handled = handled;
    }

    bool is_msg_handled() const
    {
        return m_pstade_ketchup_handled;
    }

private:
    bool m_pstade_ketchup_handled;
};

} // ADL barrier


} } // namespace pstade::ketchup


#pragma warning(pop)


#include "../crack/detail/handler_entry_set_undef.ipp"


#endif
