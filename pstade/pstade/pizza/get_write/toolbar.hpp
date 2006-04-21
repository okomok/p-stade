#ifndef PSTADE_PIZZA_GET_WRITE_TOOLBAR_HPP
#define PSTADE_PIZZA_GET_WRITE_TOOLBAR_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Design:
//
// button-count or something must be saved, because "0 button toolbar" is valid.
// And you need not remove redundant values thanks to button-count.


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CToolBarCtrl
#include <boost/mpl/int.hpp>
#include <boost/scoped_array.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../integer.hpp"
#include "../set_integer.hpp"


namespace pstade { namespace pizza {


struct separator_iBitmap :
    boost::mpl::int_<25964951>
{ };


namespace toolbar_detail {


    inline
    void tbBtn_separator_initialize(TBBUTTON& tbBtn)
    {
        tbBtn.iBitmap = 8;
        tbBtn.idCommand = 0;
        tbBtn.fsState = 0;
        tbBtn.fsStyle = TBSTYLE_SEP;
        tbBtn.dwData = 0;
        tbBtn.iString = 0;
    }


    inline
    tomato::tstring format_button_value_name(int i)
    {
        tomato::tstringstream os;
        os << _T("toolbar.button[") << i << _T("].iBitmap");
        return os.str();
    }


    inline
    void clean_up_buttons(HWND hWndToolBar)
    {
        BOOST_ASSERT(diet::valid(hWndToolBar));
        
        WTL::CToolBarCtrl toolbar(hWndToolBar);
        while (toolbar.DeleteButton(0))
            ;
    }


} // namespace toolbar_detail


template< class Profile >
void write_toolbar(Profile& pr, HWND hWndToolBar)
{
    BOOST_ASSERT(diet::valid(hWndToolBar));
    
    WTL::CToolBarCtrl toolbar(hWndToolBar);

    int count = toolbar.GetButtonCount();
    set_integer(pr, _T("toolbar.buttonCount"), count);

    for (int i = 0; i < count; ++i) {
        TBBUTTON tbBtn;
        PSTADE_REQUIRE(toolbar.GetButton(i, &tbBtn));

        tomato::tstring valName = toolbar_detail::format_button_value_name(i);
        int index = candy::test(tbBtn.fsStyle, TBSTYLE_SEP) ? separator_iBitmap::value : tbBtn.iBitmap;
        pizza::set_integer(pr, valName, index);
    }
}


// hWndToolbar must have all the buttons before calling.
//
template< class Profile >
bool get_toolbar(Profile& pr, HWND hWndToolBar)
{
    BOOST_ASSERT(diet::valid(hWndToolBar));

    WTL::CToolBarCtrl toolbar(hWndToolBar);

    int prCount;
    try {
        prCount = pizza::integer(pr, _T("toolbar.buttonCount"));
    }
    catch (error&) {
        return false;
    }

    int originalCount = toolbar.GetButtonCount();
    boost::scoped_array<TBBUTTON> pTBBtn(new TBBUTTON[originalCount]);

    // save original tbbuttons
    for (int i = 0; i < originalCount; ++i) {
        TBBUTTON tbBtn;
        PSTADE_REQUIRE(toolbar.GetButton(i, &tbBtn));
        pTBBtn[i] = tbBtn;
    }

    toolbar_detail::clean_up_buttons(hWndToolBar);

    // insert buttons
    for (int index = 0; index < prCount; ++index) {

        tomato::tstring valName =
            toolbar_detail::format_button_value_name(index);

        int iBitmap;
        try {
            iBitmap = pizza::integer(pr, valName); // never trust prCount
        }
        catch (error&) {
            break;
        }

        if (iBitmap == separator_iBitmap::value) {
            TBBUTTON tbBtn;
            toolbar_detail::tbBtn_separator_initialize(tbBtn);
            PSTADE_REQUIRE(toolbar.InsertButton(toolbar.GetButtonCount(), &tbBtn));
        }
        else {
            int j = 0;
            for ( ; j < originalCount; ++j) { // look up corresponding iBitmap
                if (!candy::test(pTBBtn[j].fsStyle, TBSTYLE_SEP) &&
                    pTBBtn[j].iBitmap == iBitmap)
                {
                    PSTADE_REQUIRE(toolbar.InsertButton(toolbar.GetButtonCount(), &pTBBtn[j]));
                    break;
                }
            }

            if (j == originalCount) { // not found
                BOOST_ASSERT(false && "pstade::pizza::get_toolbar - an iBidmap not found");
            }
        }

    } // for

    return true;
}


// TODO: maybe should be the range.
// (cannot be the same name because of CToolBarCtrl)
//
template< class Profile, class OutputIter >
bool copy_toolbar(Profile& pr, OutputIter out)
{
    int count;
    try {
        count = pizza::integer(pr, _T("toolbar.buttonCount"));
    }
    catch (error&) {
        return false;
    }

    // copy button index
    for (int index = 0; index < count; ++index) {
        tomato::tstring valName = toolbar_detail::format_button_value_name(index);

        try {
            int iBitmap = pizza::integer(pr, valName);
            *out = iBitmap;
            ++out;
        }
        catch (error&) {
            break;
        }
    }

    return true;
}


} } // namespace pstade::pizza


#endif
