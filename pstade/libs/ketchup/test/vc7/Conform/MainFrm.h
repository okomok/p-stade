// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <pstade/downcast.hpp>
#include <pstade/ketchup.hpp>

template< class D >
struct CMainFrameCommand1 :
	pstade::ketchup::message_processor< CMainFrameCommand1<D> >
{
private:
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		D& d = *this|pstade::to_derived;

		d.PostMessage(WM_CLOSE);
		return 0;
	}

	void OnFileNew()
	{
		// TODO: add code to initialize document

	}

public:
	typedef CMainFrameCommand1 _;				/*must add*/typename _::template
	begin_msg_map
	<														typename _::template
		command_id_handler<ID_APP_EXIT, &_::OnFileExit>,	typename _::template
		command_id_handler_simple<ID_FILE_NEW, &_::OnFileNew>
	>
	end_msg_map;
};


template< class D >
struct CMainFrameCommand2 :
	pstade::ketchup::message_processor< CMainFrameCommand2<D> >
{
private:
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		D& d = *this|pstade::to_derived;

		static BOOL bVisible = TRUE;	// initially visible
		bVisible = !bVisible;
		CReBarCtrl rebar = d.m_hWndToolBar;
		int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
		rebar.ShowBand(nBandIndex, bVisible);
		d.UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		d.UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		D& d = *this|pstade::to_derived;

		BOOL bVisible = !::IsWindowVisible(d.m_hWndStatusBar);
		::ShowWindow(d.m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		d.UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		d.UpdateLayout();
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	friend class pstade::ketchup::access;

	typedef CMainFrameCommand2 _;										typename _::template
	begin_msg_map
	<																	typename _::template
		command_id_handler<ID_VIEW_TOOLBAR, &_::OnViewToolBar>,			typename _::template
		command_id_handler<ID_VIEW_STATUS_BAR, &_::OnViewStatusBar>,	typename _::template
		command_id_handler<ID_APP_ABOUT, &_::OnAppAbout>
	>
	end_msg_map;
};


class CMainFrame :
	public pstade::ketchup::message_processor<CMainFrame,
		CFrameWindowImpl<CMainFrame>,
		CUpdateUI<CMainFrame>,
		CMainFrameCommand1<CMainFrame>,
		CMainFrameCommand2<CMainFrame>
	>,
	public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CConformView m_view;

	CCommandBarCtrl m_CmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if (CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_view.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		// attach menu
		m_CmdBar.AttachMenu(GetMenu());
		// load command bar images
		m_CmdBar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		SetMenu(NULL);

		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		CreateSimpleStatusBar();

		m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

		UIAddToolBar(hWndToolBar);
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

private:
	friend class pstade::ketchup::access;

	begin_msg_map
	<
		message_handler<WM_CREATE, &_::OnCreate>,
		chain_msg_map< CMainFrameCommand1<CMainFrame> >,
		chain_msg_map< CMainFrameCommand2<CMainFrame> >,
		chain_msg_map< WTL::CUpdateUI<CMainFrame> >,
		chain_msg_map< WTL::CFrameWindowImpl<CMainFrame> >
	>
	end_msg_map;
};
