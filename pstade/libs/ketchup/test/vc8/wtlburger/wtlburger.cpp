// wtlburger.cpp : main source file for wtlburger.exe
//

#include "stdafx.h"
#include "./resource.h"
#include <boost/microsoft/wtl/app.hpp>


#include <boost/assert.hpp>
#include <pstade/hamburger.hpp>
#include <pstade/lime/load_file.hpp>
#include <pstade/tomato/co_initializer.hpp>
#include <pstade/tomato/message_loop.hpp>
#include <pstade/tomato/module_initializer.hpp>
#include <pstade/unused.hpp>


WTL::CAppModule _Module;


namespace wtlburger_detail {


    int run(LPTSTR lpstrCmdLine, int nCmdShow)
    {
        using namespace pstade;

        tomato::message_loop theLoop;
        std::string iname("sample_view.xml");
        hamburger::unknown root;
        // root.att("path") = ...;
        lime::load_file(root, iname);

        pstade::unused(lpstrCmdLine, nCmdShow);
        return theLoop.run();
    }


} // namespace wtlburger_detail


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, int nCmdShow)
{
    using namespace pstade;

    try {
        tomato::co_initializer co;
        tomato::module_initializer module(hInstance);
        WTL::AtlInitCommonControls(ICC_BAR_CLASSES); // add flags to support other controls
        return wtlburger_detail::run(lpstrCmdLine, nCmdShow);
    }
    catch (std::exception& err) {
        err.what();
    }

    pstade::unused(hPrevInstance);
    return 0;
}
