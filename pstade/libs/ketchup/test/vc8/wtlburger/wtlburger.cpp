// wtlburger.cpp : main source file for wtlburger.exe
//

#include "stdafx.h"
#include "./resource.h"
#include <pstade/tomato/wtl/app.hpp>

#include <pstade/hamburger.hpp>

#include <pstade/oven/copied.hpp>
#include <pstade/gravy/co_init.hpp>
#include <pstade/gravy/module_file_name.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/tomato/message_loop.hpp>
#include <pstade/tomato/module_init.hpp>
#include <pstade/tomato/to_tstring_to.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>


WTL::CAppModule _Module;


namespace wtlburger_detail {


    int run(LPTSTR lpstrCmdLine, int nCmdShow)
    {
        using namespace pstade;
        using namespace hamburger;

        gravy::module_file_name mf;
        gravy::tstring path = mf.folder()|oven::copied;
        path += _T("sample.xml");

        hamburger::element root;
        root%Name_includedHref = tomato::tstring_to<ustring>(path);
        hamburger::load(root, path|oven::copied);

        (root/"desktop").create();

        hamburger::view_join_all(); // goodbye threads

        (root/"desktop").destroy();

        hamburger::save(root/"desktop");

        pstade::unused(lpstrCmdLine, nCmdShow);
        return 1;
    }


} // namespace wtlburger_detail


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

    using namespace pstade;

    try {
        gravy::co_init ci;
        tomato::module_init mi(hInstance);
        WTL::AtlInitCommonControls(ICC_BAR_CLASSES); // add flags to support other controls
        return wtlburger_detail::run(lpstrCmdLine, nCmdShow);
    }
    catch (std::exception& err) {
        err.what();
    }

    pstade::unused(hPrevInstance);
    return 0;
}
