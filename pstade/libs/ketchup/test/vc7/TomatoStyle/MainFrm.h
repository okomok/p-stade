// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/wtl/misc.hpp>
#include <boost/mpl/void.hpp>
#include <pstade/ketchup.hpp>
#include <pstade/ketchup/alias.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/tomato.hpp>
#include <pstade/tomato/alias.hpp>
#include <pstade/pizza.hpp>
#include <pstade/pizza/alias.hpp>


template< class = boost::mpl::void_ >
struct tomato_style_profile
{
	typedef pizza::ini_section type;
	//typedef ATL::CRegKey type;
};


struct CMainFrame :
	ketchup::message_processor<CMainFrame,
		WTL::CFrameWindowImpl<CMainFrame>
	>,
	WTL::CMessageFilter, WTL::CIdleHandler
{
public:
	static WTL::CFrameWndClassInfo& GetWndClassInfo() {
		return tomato::frame_wnd_class<CMainFrame>(NULL, IDR_MAINFRAME);
	}

	CTomatoStyleView m_view;
	WTL::CCommandBarCtrl m_cmdbar;
	WTL::CToolBarCtrl m_toolbar;
	WTL::CReBarCtrl m_rebar;
	tomato::message_filtering m_filtering;
	tomato::idle_handling m_idling;

	tomato_style_profile<>::type m_profile;

#if (PSTADE_APPLE_ATL_VER >= 0x0700)
	ATL::CString m_profile_name;
#else
	WTL::CString m_profile_name;
#endif

	CMainFrame() : m_profile_name(_T("mainFrame"))
	{
		pizza::initialize(m_profile, m_profile_name);
	}

	BOOL PreTranslateMessage(MSG *pMsg)
	{
		if (WTL::CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return true;

		return m_view.PreTranslateMessage(pMsg);
	}

	BOOL OnIdle()
	{
		ketchup::update_toolbar_cmd_ui(m_hWnd, m_toolbar.m_hWnd);
		return FALSE;
	}

public:
// message handlers
	LRESULT OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		// create command bar window
		m_cmdbar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE, 0, ATL_IDW_COMMAND_BAR);
		// attach menu
		m_cmdbar.AttachMenu(GetMenu());
		// load command bar images
		m_cmdbar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		::SetMenu(m_hWnd, NULL);

		m_toolbar = this->CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE, ATL_IDW_TOOLBAR);
		pizza::get_toolbar(m_profile, m_toolbar.m_hWnd);

		pizza::rebar_band_info const bands[] =
		{
			{	m_cmdbar,	RBBS_GRIPPERALWAYS|RBBS_USECHEVRON,				_T("")			},
			{	m_toolbar,	RBBS_GRIPPERALWAYS|RBBS_USECHEVRON|RBBS_BREAK,	_T("Toolbar")	}
		};

		this->CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		m_rebar = m_hWndToolBar;
		pizza::get_rebar(m_profile, m_rebar.m_hWnd, bands);

		this->CreateSimpleStatusBar();
		pizza::get_statusbar(m_profile, m_hWndStatusBar);

		m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

		//WTL::CLogFont lf;
		//pizza::get_logfont(m_profile, lf);
		m_filtering.start(this);
		m_idling.start(this);

		pstade::unused(lpCreateStruct);
		set_msg_handled(false);
		return tomato::create_success;
	}

	void ShowWindow(int nCmdShow)
	{
		// WINBUG? workaround: if called on OnCreate, window placement is broken.
		try {
			pizza::get_placement(m_profile, m_hWnd);
		}
		catch (pizza::error& ) {
			::ShowWindow(m_hWnd, nCmdShow);
		}
	}

	void OnClose()
	{
		write_profile();
		set_msg_handled(false);
	}

	void write_profile()
	{
		pizza::write_placement(m_profile, m_hWnd);
		pizza::write_rebar(m_profile, m_rebar.m_hWnd);
		pizza::write_toolbar(m_profile, m_toolbar.m_hWnd);
		pizza::write_statusbar(m_profile, m_hWndStatusBar);
		pizza::write_font(m_profile, m_cmdbar.m_hWnd);
	}

	void OnFileExit()
	{
		tomato::post_message(m_hWnd, WM_CLOSE);
	}

	void OnFileNew()
	{
		using namespace tomato;
		// TODO: add code to initialize document
	}

	void OnViewToolBar()
	{
        tomato::rebar_band band(m_rebar.m_hWnd, ATL_IDW_TOOLBAR);
        band.show(!band.is_visible());
		this->UpdateLayout();
	}

	void OnViewStatusBar()
	{
		tomato::toggle_window(m_hWndStatusBar);
		this->UpdateLayout();
	}

	void OnAppAbout()
	{
#if 1
        BOOST_FOREACH (tomato::rebar_band band, m_rebar|tomato::rebar_bands) {
            int id = band.id();
            (void)id;
        }
#endif
		CAboutDlg dlg;
		dlg.DoModal();
	}

// cmd_ui handlers
	void OnUpdateViewToolBar(cmd_ui& ui)
	{
		if (!ui.is_dependent())
			ui.set_radio(tomato::rebar_band(m_rebar.m_hWnd, ATL_IDW_TOOLBAR).is_visible());
	}

	void OnUpdateViewStatusBar(cmd_ui& ui)
	{
		ui.set_check(::IsWindowVisible(m_hWndStatusBar));
	}

	void OnUpdateFileNew(cmd_ui& ui)
	{
		ui.set_radio(::IsWindowVisible(m_hWndStatusBar)|tomato::to_boolean);
	}

	begin_msg_map
	<
		msg_wm_create<&_::OnCreate>,
		msg_wm_close<&_::OnClose>,
		command_id_handler_simple<ID_APP_EXIT, &_::OnFileExit>,
		command_id_handler_simple<ID_FILE_NEW, &_::OnFileNew>,
		command_id_handler_simple<ID_VIEW_TOOLBAR, &_::OnViewToolBar>,
		command_id_handler_simple<ID_VIEW_STATUS_BAR, &_::OnViewStatusBar>,
		command_id_handler_simple<ID_APP_ABOUT, &_::OnAppAbout>,
		update_menu_cmd_ui<>,
		cmd_ui_handler<ID_VIEW_TOOLBAR, &_::OnUpdateViewToolBar>,
		cmd_ui_handler<ID_VIEW_STATUS_BAR, &_::OnUpdateViewStatusBar>,
		cmd_ui_handler<ID_FILE_NEW, &_::OnUpdateFileNew>,
		chain_msg_map< WTL::CFrameWindowImpl<CMainFrame> >
	>
	end_msg_map;
};
