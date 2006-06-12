// TomatoStyle.cpp : main source file for TomatoStyle.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>

#include "resource.h"

#include "TomatoStyleView.h"
#include "aboutdlg.h"
#include "MainFrm.h"

#include <pstade/tomato.hpp>
#include <pstade/tomato/alias.hpp>

WTL::CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    tomato::message_loop theLoop;

    CMainFrame wndMain;

    if (wndMain.CreateEx() == NULL)
    {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }

    wndMain.ShowWindow(nCmdShow);

    return theLoop.run();
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);

	using namespace pstade;

	tomato::co_init ci;
	tomato::module_init mi(hInstance);
    WTL::AtlInitCommonControls(ICC_COOL_CLASSES | ICC_BAR_CLASSES); // add flags to support other controls
    return Run(lpstrCmdLine, nCmdShow);
}
