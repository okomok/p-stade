#include <atlctrls.h>
#include <atlctrlw.h>

// <mdf>
#include <pstade/ketchup.hpp>
#include <pstade/ketchup/alias.hpp>
#include <pstade/tomato.hpp>
#include <pstade/tomato/alias.hpp>
#include <boost/mpl/bool.hpp>
// </mdf>

class CHelloView : public ketchup::message_processor< CHelloView, CWindowImpl<CHelloView> >
{
public:
	COLORREF m_clrText;

	//state of color buttons
	BOOL m_bBlack;
	BOOL m_bRed;
	BOOL m_bBlue;
	BOOL m_bGreen;
	BOOL m_bWhite;
	BOOL m_bCustom;
	/* <mdf>
	CUpdateUIBase* m_pUpdateUI;

	CHelloView(CUpdateUIBase* pUpdateUI) : m_clrText(RGB(0, 0, 0)),
	</mdf> */
	CHelloView() : m_clrText(RGB(0, 0, 0)),
		m_bBlack(TRUE),
		m_bRed(FALSE),
		m_bBlue(FALSE),
		m_bGreen(FALSE),
		m_bWhite(FALSE),
		m_bCustom(FALSE) /* , <mdf>
		m_pUpdateUI(pUpdateUI) </mdf> */
	{ }

	DECLARE_WND_CLASS(NULL)

	void ClearAllColors()
	{
		m_bBlack = m_bBlue = m_bRed = FALSE;
		m_bWhite = m_bGreen = FALSE;
	}

	void MixColors() 
	{
		COLORREF tmpClr;
		int r, g, b;
		BOOL bSetColor;
		
		// Determine which colors are currently chosen.
		bSetColor = m_bRed || m_bGreen || m_bBlue || m_bWhite || m_bBlack;

   		// If the current color is custom, ignore mix request.
		if(!bSetColor && m_bCustom)
			return;

   		// Set color value to black and then add the necessary colors.
		r = g = b = 0;

		if(m_bRed)
			r = 255;
		if(m_bGreen)
			g = 255;
		if(m_bBlue)
			b = 255;

		tmpClr = RGB(r, g, b);

	// NOTE: Because a simple algorithm is used to mix colors
	// if the current selection contains black or white, the 
	// result will be black or white; respectively. This is due
	// to the additive method for mixing the colors.

		if(m_bBlack)
			tmpClr = RGB(0, 0, 0);

		if(m_bWhite)
			tmpClr = RGB(255, 255, 255);

   		// Once the color has been determined, update document 
		// data, and force repaint of all views.

		if(!bSetColor)
			m_bBlack = TRUE;
		m_clrText = tmpClr;
		m_bCustom = FALSE;

		// <mdf> UpdateButtons(); </mdf>
		Invalidate();
	}

	// <mdf>
	void OnUpdateBlack(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bBlack);
	}

	void OnUpdateRed(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bRed);
	}

	void OnUpdateGreen(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bGreen);
	}

	void OnUpdateBlue(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bBlue);
	}

	void OnUpdateWhite(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bWhite);
	}
	void OnUpdateCustom(ketchup::cmd_ui& ui)
	{
		if (!ui.is_dependent())
			ui.set_check(m_bCustom);
	}
	// </mdf>

	/* <mdf>
	void UpdateButtons()
	{
		m_pUpdateUI->UISetCheck(ID_BLACK, m_bBlack);
		m_pUpdateUI->UISetCheck(ID_RED, m_bRed);
		m_pUpdateUI->UISetCheck(ID_GREEN, m_bGreen);
		m_pUpdateUI->UISetCheck(ID_BLUE, m_bBlue);
		m_pUpdateUI->UISetCheck(ID_WHITE, m_bWhite);
		m_pUpdateUI->UISetCheck(ID_CUSTOM, m_bCustom);
	}
	</mdf> */

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	/* <mdf>
	BEGIN_MSG_MAP(CHelloView)
		KETCHUP_CHAIN_CMD_UI_MAP_CMD_UI(cmd_ui_map)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		// <mdf> MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus) </mdf>
		COMMAND_RANGE_HANDLER(ID_BLACK, ID_WHITE, OnColor)
		COMMAND_ID_HANDLER(ID_CUSTOM, OnCustomColor)
	END_MSG_MAP()
	</mdf> */

	// <mdf> LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL&) </mdf>
	void OnPaint(HDC)
	{
		CPaintDC dc(m_hWnd);

		RECT rect;
		GetClientRect(&rect);
		dc.SetTextColor(m_clrText);
		dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
		dc.DrawText(_T("Good bye, BEGIN_MSG_MAP!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		// <mdf> return 0; </mdf>
	}

	/* <mdf>
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pUpdateUI->UIEnable(ID_BLACK, TRUE);
		m_pUpdateUI->UIEnable(ID_RED, TRUE);
		m_pUpdateUI->UIEnable(ID_GREEN, TRUE);
		m_pUpdateUI->UIEnable(ID_BLUE, TRUE);
		m_pUpdateUI->UIEnable(ID_WHITE, TRUE);
		m_pUpdateUI->UIEnable(ID_CUSTOM, TRUE);

		m_pUpdateUI->UISetCheck(ID_SPEED_SLOW, 0);
		m_pUpdateUI->UISetCheck(ID_SPEED_FAST, 0);
		m_pUpdateUI->UIEnable(ID_SPEED_SLOW, FALSE);
		m_pUpdateUI->UIEnable(ID_SPEED_FAST, FALSE);

		UpdateButtons();

		bHandled = FALSE;
		return 1;
	}
	</mdf> */

	// <mdf> LRESULT OnColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnColor(WORD, WORD wID, HWND, BOOL&)
	// </mdf>
	{
		switch(wID)
		{
		 case ID_BLACK:
			ClearAllColors();
			m_bBlack = !(m_bBlack);
			break;
		 case ID_WHITE:
			ClearAllColors();
			m_bWhite = !(m_bWhite);
			break;
		 case ID_RED:
			m_bRed = !(m_bRed);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 case ID_GREEN:
			m_bGreen = !(m_bGreen);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 case ID_BLUE:
			m_bBlue = !(m_bBlue);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 default:
			TCHAR buff[256];
			::LoadString(_Module.GetResourceInstance(), IDS_UNKCOLOR, buff, 255);
			MessageBox(buff);
			return 1;
		}
		MixColors();
		return 0;
	}

	// <mdf> LRESULT OnCustomColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnCustomColor(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		CColorDialog dlgColor(m_clrText);
		if(dlgColor.DoModal() == IDOK)
		{
			m_clrText = dlgColor.GetColor();
			ClearAllColors();
			m_bCustom = TRUE;
			// <mdf> UpdateButtons(); </mdf>
			Invalidate();
		}
		return 0;
	}

	// <mdf>

	struct cmd_ui_map_sub;	// forward declaration also works fine.
		
	// which do you like typedef...
	typedef begin_msg_map<	
		cmd_ui_handler<ID_BLACK, &_::OnUpdateBlack>,
		cmd_ui_handler<ID_RED, &_::OnUpdateRed>,
		cmd_ui_handler<ID_GREEN, &_::OnUpdateGreen>,
		cmd_ui_map_sub				// chain
	> cmd_ui_map;

	// or struct?
	struct cmd_ui_map_sub : begin_msg_map<
		cmd_ui_handler<ID_BLUE, &_::OnUpdateBlue>,
		begin_msg_map<				// chain
			cmd_ui_handler<ID_WHITE, &_::OnUpdateWhite>,
			cmd_ui_handler<ID_CUSTOM, &_::OnUpdateCustom>
		>
	> { };

	begin_msg_map4
	<
		cmd_ui_map,						// chain
		msg_wm_paint<&_::OnPaint>,
		command_range_handler<ID_BLACK, ID_WHITE, &_::OnColor>,
		command_id_handler<ID_CUSTOM, &_::OnCustomColor>
	>
	end_msg_map;

	// </mdf>
};

class CHelloWnd : public ketchup::message_processor< CHelloWnd, CMDIChildWindowImpl<CHelloWnd> >
{
public:
	CHelloView* m_pView;
/* <mdf>
	CUpdateUIBase* m_pUpdateUI;

	CHelloWnd(CUpdateUIBase* pUpdateUI) : m_pView(NULL), m_pUpdateUI(pUpdateUI) </mdf> */
	CHelloWnd() : m_pView(NULL)
	{ }

	DECLARE_FRAME_WND_CLASS(NULL, IDR_HELLOTYPE)

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	/* <mdf>
	BEGIN_MSG_MAP(CHelloWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_CLIENT_COMMANDS()
		KETCHUP_CHAIN_CLIENT_CMD_UI()
		CHAIN_MSG_MAP(CMDIChildWindowImpl<CHelloWnd>)
	END_MSG_MAP()
	</mdf> */

	// <mdf> LRESULT OnCreate(UINT, WPARAM, LPARAM lParam, BOOL& bHandled)
	// LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
	LRESULT OnCreate(LPCREATESTRUCT)
	// </mdf>
	{
		m_pView = new CHelloView(); // <mdf> m_pUpdateUI); </mdf>
		RECT rect = { 0, 0, 1, 1 };
		m_hWndClient = m_pView->Create(m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE);

		// <mdf> bHandled = FALSE; </mdf>
		// ketchup::set_msg_handled(*this, false);
		return 1;
	}

	begin_msg_map
	<
		// <mdf> message_handler<WM_CREATE, &_::OnCreate>, </mdf>
		msg_wm_create<&_::OnCreate, not_handled>, // cracked!
		chain_client_commands<>,
		chain_client_cmd_ui<>,
		chain_msg_map< CMDIChildWindowImpl<CHelloWnd> >
	>
	end_msg_map;
};

#define ABS(x) ((x) < 0? -(x) : (x) > 0? (x) : 0)

class CBounceView : public ketchup::message_processor< CBounceView, CWindowImpl<CBounceView> >
{
public:
	COLORREF m_clrBall;

	//state of color buttons
	BOOL m_bBlack;
	BOOL m_bRed;
	BOOL m_bBlue;
	BOOL m_bGreen;
	BOOL m_bWhite;
	BOOL m_bCustom;

	BOOL m_bFastSpeed;         // current speed

	POINT m_ptPixel;           // pixel size
	SIZE m_sizeRadius;         // radius of ball
	SIZE m_sizeMove;           // move speed
	SIZE m_sizeTotal;          // total size for ball bitmap
	POINT m_ptCenter;          // current center for the ball

	CBitmap m_bmBall;          // for replicating bouncing ball

	/* <mdf> CUpdateUIBase* m_pUpdateUI;

	CBounceView(CUpdateUIBase* pUpdateUI) : m_clrBall(RGB(0, 0, 0)),
	</mdf> */
	CBounceView() : m_clrBall(RGB(0, 0, 0)),
		m_bBlack(TRUE),
		m_bRed(FALSE),
		m_bBlue(FALSE),
		m_bGreen(FALSE),
		m_bWhite(FALSE),
		m_bCustom(FALSE),
		m_bFastSpeed(FALSE)// <mdf> , m_pUpdateUI(pUpdateUI) </mdf>
	{ }

	DECLARE_WND_CLASS(NULL)

	HWND Create(HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			UINT nID = 0, LPVOID = NULL) // <mdf> lpCreateParam) = NULL) </mdf>
	{
		CWndClassInfo& wci = GetWndClassInfo();
		wci.m_lpszCursorID = IDC_SIZENS;
		ATOM atom = wci.Register(&m_pfnSuperWindowProc);
		return CWindowImplBase::Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle,
			nID, atom);
	}

	void ClearAllColors()
	{
		m_bBlack = m_bBlue = m_bRed = FALSE;
		m_bWhite = m_bGreen = FALSE;
	}

	void MixColors() 
	{
		COLORREF tmpClr;
		int r, g, b;
		BOOL bSetColor;
		
		// Determine which colors are currently chosen.
		bSetColor = m_bRed || m_bGreen || m_bBlue || m_bWhite || m_bBlack;

   		// If the current color is custom, ignore mix request.
		if(!bSetColor && m_bCustom)
			return;

   		// Set color value to black and then add the necessary colors.
		r = g = b = 0;

		if(m_bRed)
			r = 255;
		if(m_bGreen)
			g = 255;
		if(m_bBlue)
			b = 255;

		tmpClr = RGB(r, g, b);

	// NOTE: Because a simple algorithm is used to mix colors
	// if the current selection contains black or white, the 
	// result will be black or white; respectively. This is due
	// to the additive method for mixing the colors.

		if(m_bBlack)
			tmpClr = RGB(0, 0, 0);

		if(m_bWhite)
			tmpClr = RGB(255, 255, 255);

   		// Once the color has been determined, update document 
		// data, and force repaint of all views.

		if(!bSetColor)
			m_bBlack = TRUE;
		m_clrBall = tmpClr;
		m_bCustom = FALSE;

		// <mdf> UpdateColorButtons(); </mdf>
		MakeNewBall();
		Invalidate();
	}
	// <mdf>
	void OnUpdateBlack(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bBlack);
	}
	void OnUpdateRed(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bRed);
	}
	void OnUpdateGreen(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bGreen);
	}
	void OnUpdateBlue(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bBlue);
	}
	void OnUpdateWhite(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bWhite);
	}
	void OnUpdateCustom(ketchup::cmd_ui& ui)
	{
		if (!ui.is_dependent())
			ui.set_check(m_bCustom);
	}
	void OnUpdateSlow(ketchup::cmd_ui& ui)
	{
		if (!ui.is_dependent())
			ui.set_check(!m_bFastSpeed);
	}
	void OnUpdateFast(ketchup::cmd_ui& ui)
	{
		ui.set_check(m_bFastSpeed);
	}
	// </mdf>
	/* <mdf>
	void UpdateColorButtons()
	{
		m_pUpdateUI->UISetCheck(ID_BLACK, m_bBlack);
		m_pUpdateUI->UISetCheck(ID_RED, m_bRed);
		m_pUpdateUI->UISetCheck(ID_GREEN, m_bGreen);
		m_pUpdateUI->UISetCheck(ID_BLUE, m_bBlue);
		m_pUpdateUI->UISetCheck(ID_WHITE, m_bWhite);
		m_pUpdateUI->UISetCheck(ID_CUSTOM, m_bCustom);
	}

	void UpdateSpeedButtons()
	{
		m_pUpdateUI->UISetCheck(ID_SPEED_SLOW, !m_bFastSpeed);
		m_pUpdateUI->UISetCheck(ID_SPEED_FAST, m_bFastSpeed);
	}
	</mdf> */
	void MakeNewBall()
	{
		m_sizeTotal.cx = (m_sizeRadius.cx + ABS(m_sizeMove.cx)) << 1;
		m_sizeTotal.cy = (m_sizeRadius.cy + ABS(m_sizeMove.cy)) << 1;

		if(m_bmBall.m_hBitmap != NULL)
			m_bmBall.DeleteObject();        // get rid of old bitmap

		CClientDC dc(m_hWnd);
		CDC dcMem;
		dcMem.CreateCompatibleDC(dc);

		m_bmBall.CreateCompatibleBitmap(dc, m_sizeTotal.cx, m_sizeTotal.cy);
		_ASSERTE(m_bmBall.m_hBitmap != NULL);

		dcMem.SelectBitmap(m_bmBall);

		// draw a rectangle in the background (window) color
		RECT rect = { 0, 0, m_sizeTotal.cx, m_sizeTotal.cy };
		CBrush brBackground;
		brBackground.CreateSolidBrush(::GetSysColor(COLOR_WINDOW));
		dcMem.FillRect(&rect, brBackground);

		CBrush brCross;
		brCross.CreateHatchBrush(HS_DIAGCROSS, 0L);
		dcMem.SelectBrush(brCross);

		dcMem.SetBkColor(m_clrBall);
		dcMem.Ellipse(ABS(m_sizeMove.cx), ABS(m_sizeMove.cy),
			m_sizeTotal.cx - ABS(m_sizeMove.cx),
			m_sizeTotal.cy - ABS(m_sizeMove.cy));
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}
	
	/* <mdf>
	BEGIN_MSG_MAP(CBounceView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		// <mdf> MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus) </mdf>
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		COMMAND_RANGE_HANDLER(ID_BLACK, ID_WHITE, OnColor)
		COMMAND_ID_HANDLER(ID_CUSTOM, OnCustomColor)
		COMMAND_ID_HANDLER(ID_SPEED_SLOW, OnChangeSpeed)
		COMMAND_ID_HANDLER(ID_SPEED_FAST, OnChangeSpeed)
	END_MSG_MAP()
	</mdf> */

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
	{
#if (_ATL_VER >= 0x0300)
		if(!SetTimer(1, 100))	// start slow
#else
		if(!SetTimer(1, 100, NULL))	// start slow
#endif //(_ATL_VER == 0x0300)
		{
			MessageBox(_T("Not enough timers available for this window."),
					_T("MDI:Bounce"), MB_ICONEXCLAMATION | MB_OK);

			// signal creation failure...
			return -1;
		}

		CClientDC dc(m_hWnd);
		m_ptPixel.x = dc.GetDeviceCaps(ASPECTX);
		m_ptPixel.y = dc.GetDeviceCaps(ASPECTY);

		bHandled = FALSE;
		return 1;
	}

	/* <mdf>
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pUpdateUI->UIEnable(ID_BLACK, TRUE);
		m_pUpdateUI->UIEnable(ID_RED, TRUE);
		m_pUpdateUI->UIEnable(ID_GREEN, TRUE);
		m_pUpdateUI->UIEnable(ID_BLUE, TRUE);
		m_pUpdateUI->UIEnable(ID_WHITE, TRUE);
		m_pUpdateUI->UIEnable(ID_CUSTOM, TRUE);
		m_pUpdateUI->UIEnable(ID_SPEED_SLOW, TRUE);
		m_pUpdateUI->UIEnable(ID_SPEED_FAST, TRUE);

		UpdateColorButtons();
		UpdateSpeedButtons();

		bHandled = FALSE;
		return 1;
	}
	</mdf> */

	// <mdf> LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	LRESULT OnSize(UINT, WPARAM, LPARAM lParam, BOOL& bHandled)
	// </mdf>
	{
		int cx = LOWORD(lParam);
		int cy = HIWORD(lParam);
		LONG lScale;

		m_ptCenter.x = cx >> 1;
		m_ptCenter.y = cy >> 1;
		m_ptCenter.x += cx >> 3; // make the ball a little off-center

		lScale = min((LONG)cx * m_ptPixel.x,
			(LONG)cy * m_ptPixel.y) >> 4;
		m_sizeRadius.cx = (int)(lScale / m_ptPixel.x);
		m_sizeRadius.cy = (int)(lScale / m_ptPixel.y);
		m_sizeMove.cx = max(1, m_sizeRadius.cy >> 2);
		m_sizeMove.cy = max(1, m_sizeRadius.cy >> 2);

		MakeNewBall();

		bHandled = FALSE;
		return 1;
	}

	LRESULT OnTimer(UINT, WPARAM, LPARAM, BOOL&)// <mdf> bHandled) </mdf>
	{
		if (m_bmBall.m_hBitmap == NULL)
			return 1;     // no bitmap for the ball

		RECT rcClient;
		GetClientRect(&rcClient);

		CClientDC dc(m_hWnd);

		CDC dcMem;
		dcMem.CreateCompatibleDC(dc);
		dcMem.SelectBitmap(m_bmBall);

		dc.BitBlt(m_ptCenter.x - m_sizeTotal.cx / 2,
				m_ptCenter.y - m_sizeTotal.cy / 2,
				m_sizeTotal.cx, m_sizeTotal.cy,
				dcMem, 0, 0, SRCCOPY);

		m_ptCenter.x += m_sizeMove.cx;
		m_ptCenter.y += m_sizeMove.cy;

		if((m_ptCenter.x + m_sizeRadius.cx >= rcClient.right) ||
			(m_ptCenter.x - m_sizeRadius.cx <= 0))
		{
			m_sizeMove.cx = -m_sizeMove.cx;
		}

		if((m_ptCenter.y + m_sizeRadius.cy >= rcClient.bottom) ||
			(m_ptCenter.y - m_sizeRadius.cy <= 0))
		{
			m_sizeMove.cy = -m_sizeMove.cy;
		}

		return 0;
	}

	// <mdf> LRESULT OnColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	 LRESULT OnColor(WORD, WORD wID, HWND, BOOL&)
	 // </mdf>
	{
		switch(wID)
		{
		 case ID_BLACK:
			ClearAllColors();
			m_bBlack = !(m_bBlack);
			break;
		 case ID_WHITE:
			ClearAllColors();
			m_bWhite = !(m_bWhite);
			break;
		 case ID_RED:
			m_bRed = !(m_bRed);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 case ID_GREEN:
			m_bGreen = !(m_bGreen);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 case ID_BLUE:
			m_bBlue = !(m_bBlue);
			m_bBlack = FALSE;
			m_bWhite = FALSE;
			break;
		 default:
			TCHAR buff[256];
			::LoadString(_Module.GetResourceInstance(), IDS_UNKCOLOR, buff, 255);
			MessageBox(buff);
			return 1;
		}
		MixColors();
		return 0;
	}


	// <mdf> LRESULT OnCustomColor(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnCustomColor(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		CColorDialog dlgColor(m_clrBall);
		if(dlgColor.DoModal() == IDOK)
		{
			m_clrBall = dlgColor.GetColor();
			ClearAllColors();
			m_bCustom = TRUE;
			// <mdf> UpdateColorButtons(); </mdf>
			MakeNewBall();
			Invalidate();
		}
		return 0;
	}

	// <mdf> LRESULT OnChangeSpeed(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnChangeSpeed(WORD, WORD wID, HWND, BOOL&)
	// </mdf>
	{
		m_bFastSpeed = (wID == ID_SPEED_FAST) ? TRUE : FALSE;
		// <mdf> UpdateSpeedButtons(); </mdf>
		KillTimer(1);
#if (_ATL_VER >= 0x0300)
		if(!SetTimer(1, m_bFastSpeed ? 0 : 100))
#else
		if(!SetTimer(1, m_bFastSpeed ? 0 : 100, NULL))
#endif //(_ATL_VER == 0x0300)
		{
			MessageBox(_T("Not enough timers available for this window."),
					_T("MDI:Bounce"), MB_ICONEXCLAMATION | MB_OK);
			DestroyWindow();
		}
		return 0;
	}

	begin_msg_map2
	<
		alt_msg_map<0,
			message_handler<WM_CREATE, &_::OnCreate>,
			message_handler<WM_SIZE, &_::OnSize>,
			message_handler<WM_TIMER, &_::OnTimer>,

			command_range_handler<ID_BLACK, ID_WHITE, &_::OnColor>,
			command_id_handler<ID_CUSTOM, &_::OnCustomColor>,
			command_id_handler<ID_SPEED_SLOW, &_::OnChangeSpeed>,
			command_id_handler<ID_SPEED_FAST, &_::OnChangeSpeed>,

			cmd_ui_handler<ID_BLACK, &_::OnUpdateBlack>,
			cmd_ui_handler<ID_RED, &_::OnUpdateRed>,
			cmd_ui_handler<ID_GREEN, &_::OnUpdateGreen>,
			cmd_ui_handler<ID_BLUE, &_::OnUpdateBlue>,
			cmd_ui_handler<ID_WHITE, &_::OnUpdateWhite>,
			cmd_ui_handler<ID_CUSTOM, &_::OnUpdateCustom>,
			cmd_ui_handler<ID_SPEED_SLOW, &_::OnUpdateSlow>,
			cmd_ui_handler<ID_SPEED_FAST, &_::OnUpdateFast>
		>,
		alt_msg_map<1,
			empty_entry<>,
			empty_entry<>,
			empty_entry<>,
			assert_entry<boost::mpl::false_>
		>
	>
	end_msg_map;

	// </mdf>
};

class CBounceWnd : public ketchup::message_processor< CBounceWnd, CMDIChildWindowImpl<CBounceWnd> >
{
public:
	CBounceView* m_pView;
	/* <mdf>
	CUpdateUIBase* m_pUpdateUI;

	CBounceWnd(CUpdateUIBase* pUpdateUI) : m_pView(NULL), m_pUpdateUI(pUpdateUI)
	</mdf> */
	CBounceWnd() : m_pView(NULL)
	{ }

	DECLARE_FRAME_WND_CLASS(NULL, IDR_BOUNCETYPE)

	HWND Create(HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			UINT nMenuID = 0, LPVOID lpCreateParam = NULL)
	{
		CFrameWndClassInfo& wci = GetWndClassInfo();
		wci.m_lpszCursorID = IDC_UPARROW;
		return CMDIChildWindowImpl<CBounceWnd>::Create(hWndParent, rect, szWindowName, dwStyle, dwExStyle, nMenuID, lpCreateParam);
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL& bHandled)
	{
		m_pView = new CBounceView(); // <mdf> m_pUpdateUI); </mdf>
		RECT rect = { 0, 0, 1, 1 };
		m_hWndClient = m_pView->Create(m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE);

		bHandled = FALSE;
		return 1;
	}

	begin_msg_map
	<
		message_handler<WM_CREATE, &_::OnCreate>,
		chain_client_cmd_ui<>
	>
	end_msg_map;

	BEGIN_MSG_MAP(CBounceWnd)
		// <mdf> MESSAGE_HANDLER(WM_CREATE, OnCreate) </mdf>
		PSTADE_KETCHUP_CHAIN_MSG(*this)
		CHAIN_CLIENT_COMMANDS()
		CHAIN_MSG_MAP(CMDIChildWindowImpl<CBounceWnd>)
	END_MSG_MAP()

};


class CAboutDlg : public ketchup::message_processor< CAboutDlg, CDialogImpl<CAboutDlg> >
{
public:
	enum { IDD = IDD_ABOUTDLG };

	/* <mdf>
	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()
	</mdf> */

	// <mdf> LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
	// </mdf>
	{
		CenterWindow(GetParent());
		return (LRESULT)TRUE;
	}

	// <mdf> LRESULT OnCloseCmd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnCloseCmd(WORD, WORD wID, HWND, BOOL&)
	// </mdf>
	{
		EndDialog(wID);
		return 0;
	}

	begin_msg_map
	<
		message_handler<WM_INITDIALOG, &_::OnInitDialog>,
		debug_entry< command_id_handler<IDOK, &_::OnCloseCmd> >,
		command_id_handler<IDCANCEL, &_::OnCloseCmd>
	>
	end_msg_map;
};


class CMDIFrame : // <mdf> CUpdateUI<CMDIFrame>, </mdf>
	public CMessageFilter, public CUpdateUIObject,
	public ketchup::message_processor< CMDIFrame, CMDIFrameWindowImpl<CMDIFrame> >
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CMDICommandBarCtrl m_CmdBar;
	// <mdf>
	CToolBarCtrl m_wndToolBar;
	// </mdf>

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CMDIFrameWindowImpl<CMDIFrame>::PreTranslateMessage(pMsg);
	}
	/* <mdf>
	virtual BOOL DoUpdate()
	{
		UIUpdateToolBar();
		return FALSE;
	}
	</mdf> */
	
	// <mdf>
	void OnUpdateViewToolBar(ketchup::cmd_ui& ui)
	{
		if (!ui.is_dependent())
			ui.set_check(::IsWindowVisible(m_hWndToolBar));
	}

	void OnUpdateViewStatusBar(ketchup::cmd_ui& ui)
	{
		ui.set_check(::IsWindowVisible(m_hWndStatusBar));
	}

	virtual BOOL OnIdle()
	{
		ketchup::update_toolbar_cmd_ui(m_hWnd, m_wndToolBar);
		return FALSE;
	}
	// </mdf>

	/* <mdf>
	BEGIN_MSG_MAP(CMDIFrame)
		KETCHUP_UPDATE_MENU_CMD_UI(cmd_ui_map)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEWBOUNCE, OnBounce)
		COMMAND_ID_HANDLER(ID_FILE_NEWHELLO, OnHello)
		COMMAND_ID_HANDLER(ID_WINDOW_CASCADE, OnWindowCascade)
		COMMAND_ID_HANDLER(ID_WINDOW_TILE_HORZ, OnWindowTile)
		COMMAND_ID_HANDLER(ID_WINDOW_ARRANGE, OnWindowArrangeIcons)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		// <mdf> MESSAGE_HANDLER(WM_MDISETMENU, OnMDISetMenu) </mdf>
		CHAIN_MDI_CHILD_COMMANDS()
		// <mdf> CHAIN_MSG_MAP(CUpdateUI<CMDIFrame>) </mdf>
		CHAIN_MSG_MAP(CMDIFrameWindowImpl<CMDIFrame>)
	END_MSG_MAP()
	</mdf> */ 

	/* <mdf>
	BEGIN_UPDATE_UI_MAP(CMDIFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_BLACK,  UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_RED,    UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_GREEN,  UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_BLUE,   UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_WHITE,  UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_CUSTOM, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_SPEED_SLOW, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_SPEED_FAST, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
	END_UPDATE_UI_MAP()
	<mdf> */
	// <mdf> LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&)
	// </mdf>
	{
		// Create MDIClient
		CreateMDIClient();

		// Create MDI CommandBar
		m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		m_CmdBar.SetMDIClient(m_hWndClient);
		m_CmdBar.AttachMenu(GetMenu());
		SetMenu(NULL);

		// Create Toolbar
		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);
		// <mdf>UIAddToolBar(hWndToolBar); </mdf>

		// Create Rebar
		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(m_CmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);
		// <mdf>
		m_wndToolBar = hWndToolBar;
		// </mdf>

		CreateSimpleStatusBar(_T("Ready"));

		/* <mdf>
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		UIEnable(ID_BLACK, FALSE);
		UIEnable(ID_RED, FALSE);
		UIEnable(ID_GREEN, FALSE);
		UIEnable(ID_BLUE, FALSE);
		UIEnable(ID_WHITE, FALSE);
		UIEnable(ID_CUSTOM, FALSE);
		UIEnable(ID_SPEED_SLOW, FALSE);
		UIEnable(ID_SPEED_FAST, FALSE);
		</mdf> */
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		pLoop->AddMessageFilter(this);
    // <mdf> pLoop->AddUpdateUI(this);
		pLoop->AddIdleHandler(this);
		// </mad>

		return 0;
	}

		/* <mdf>
	LRESULT OnMDISetMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		UISetCheck(ID_BLACK, 0);
		UISetCheck(ID_RED, 0);
		UISetCheck(ID_GREEN, 0);
		UISetCheck(ID_BLUE, 0);
		UISetCheck(ID_WHITE, 0);
		UISetCheck(ID_CUSTOM, 0);
		UISetCheck(ID_SPEED_SLOW, 0);
		UISetCheck(ID_SPEED_FAST, 0);

		UIEnable(ID_BLACK, FALSE);
		UIEnable(ID_RED, FALSE);
		UIEnable(ID_GREEN, FALSE);
		UIEnable(ID_BLUE, FALSE);
		UIEnable(ID_WHITE, FALSE);
		UIEnable(ID_CUSTOM, FALSE);
		UIEnable(ID_SPEED_SLOW, FALSE);
		UIEnable(ID_SPEED_FAST, FALSE);
		bHandled = FALSE;
		return 1;
	}
	</mdf> */

	// <mdf> LRESULT OnFileExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnFileExit(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	// <mdf> LRESULT OnBounce(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnBounce(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		CBounceWnd* pChild = new CBounceWnd(); /* (CUpdateUIBase*)this); */
		pChild->CreateEx(m_hWndClient, NULL, _T("Bounce"));

		return 0;
	}

	// <mdf> LRESULT OnHello(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnHello(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		CHelloWnd* pChild = new CHelloWnd(); /* (CUpdateUIBase*)this); */
		pChild->CreateEx(m_hWndClient, NULL, _T("Hello"));

		return 0;
	}

	// <mdf> LRESULT OnWindowCascade(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnWindowCascade(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		MDICascade(0);
		return 0;
	}

	// <mdf> LRESULT OnWindowTile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnWindowTile(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		MDITile(MDITILE_HORIZONTAL);
		return 0;
	}

	// <mdf> LRESULT OnWindowArrangeIcons(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnWindowArrangeIcons(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		MDIIconArrange();
		return 0;
	}

	// <mdf> LRESULT OnViewToolBar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnViewToolBar(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		BOOL bNew = !::IsWindowVisible(m_hWndToolBar);
		/* <mdf>
		::ShowWindow(m_hWndToolBar, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_TOOLBAR, bNew);
		*/
		::ShowWindow(m_hWndToolBar, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
		// </mdf>
		UpdateLayout();
		return 0;
	}

	// <mdf> LRESULT OnViewStatusBar(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnViewStatusBar(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		BOOL bNew = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
		// <mdf> UISetCheck(ID_VIEW_STATUS_BAR, bNew); </mdf>
		UpdateLayout();
		return 0;
	}

	// <mdf> LRESULT OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	LRESULT OnAppAbout(WORD, WORD, HWND, BOOL&)
	// </mdf>
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

	// <mdf>
	typedef ketchup::idset<
		ID_BLACK, ID_RED, ID_GREEN, ID_BLUE, ID_WHITE,
		ID_CUSTOM, ID_SPEED_SLOW, ID_SPEED_FAST
	> child_cmd_ids;

	begin_msg_map
	<
		update_menu_cmd_ui<>,
		cmd_ui_handler<ID_VIEW_TOOLBAR, &_::OnUpdateViewToolBar>,
		cmd_ui_handler<ID_VIEW_STATUS_BAR, &_::OnUpdateViewStatusBar>,
		enable_cmd_ui_if_handled<chain_mdi_child_cmd_ui<>, child_cmd_ids>,

		message_handler<WM_CREATE, &_::OnCreate>,
		command_id_handler<ID_APP_EXIT, &_::OnFileExit>,
		command_id_handler<ID_FILE_NEWBOUNCE, &_::OnBounce>,
		command_id_handler<ID_FILE_NEWHELLO, &_::OnHello>,
		command_id_handler<ID_WINDOW_CASCADE, &_::OnWindowCascade>,
		command_id_handler<ID_WINDOW_TILE_HORZ, &_::OnWindowTile>,
		command_id_handler<ID_WINDOW_ARRANGE, &_::OnWindowArrangeIcons>,
		command_id_handler<ID_VIEW_TOOLBAR, &_::OnViewToolBar>,
		command_id_handler<ID_VIEW_STATUS_BAR, &_::OnViewStatusBar>,
		command_id_handler<ID_APP_ABOUT, &_::OnAppAbout>,
		chain_mdi_child_commands<>,
		chain_msg_map< CMDIFrameWindowImpl<CMDIFrame> >
	>
	end_msg_map;

	// </mdf>
};
