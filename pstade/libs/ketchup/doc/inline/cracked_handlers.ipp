LRESULT OnCreate(LPCREATESTRUCT)
{
    m_pView = new CHelloView();
    RECT rect = { 0, 0, 1, 1 };
    m_hWndClient = m_pView->Create(m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE);

    // SetMsgHandled(FALSE); is not supported.
    return 1;
}

begin_msg_map
<
    msg_wm_create<&_::OnCreate, not_handled>, // cracked!
    chain_client_commands<>,
    chain_client_cmd_ui<>,
    chain_msg_map< CMDIChildWindowImpl<CHelloWnd> >
>
end_msg_map;
