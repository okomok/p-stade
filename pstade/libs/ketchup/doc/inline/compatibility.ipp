begin_msg_map
<
    message_handler<WM_CREATE, &_::OnCreate>,
    chain_client_cmd_ui<>
>
end_msg_map;

BEGIN_MSG_MAP(CBounceWnd)
    // MESSAGE_HANDLER(WM_CREATE, OnCreate)
    PSTADE_KETCHUP_CHAIN_MSG(*this)
    CHAIN_CLIENT_COMMANDS()
    CHAIN_MSG_MAP(CMDIChildWindowImpl<CBounceWnd>)
END_MSG_MAP()
