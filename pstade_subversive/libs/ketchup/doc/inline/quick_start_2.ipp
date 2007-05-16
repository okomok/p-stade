public:
    begin_msg_map
    <
        message_handler<WM_CREATE, &_::OnCreate>,
        command_id_handler<ID_APP_EXIT, &_::OnFileExit>,
        command_id_handler<ID_FILE_NEW, &_::OnFileNew>,
        command_id_handler<ID_VIEW_TOOLBAR, &_::OnViewToolBar>,
        command_id_handler<ID_VIEW_STATUS_BAR, &_::OnViewStatusBar>,
        command_id_handler<ID_APP_ABOUT, &_::OnAppAbout>,
        chain_msg_map< WTL::CUpdateUI<CMainFrame> >,
        chain_msg_map< WTL::CFrameWindowImpl<CMainFrame> >
    >
    end_msg_map;
};