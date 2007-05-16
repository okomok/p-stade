begin_msg_map
<
    message_handler<WM_CREATE, &_::OnCreate>,
    command_id_handler<ID_APP_EXIT, &_::OnFileExit>,
    command_id_handler<ID_FILE_NEW, &_::OnFileNew>,
    chain_client_commands<>,
    chain_msg_map< WTL::CFrameWindowImpl<CMainFrame> >
>
end_msg_map;
