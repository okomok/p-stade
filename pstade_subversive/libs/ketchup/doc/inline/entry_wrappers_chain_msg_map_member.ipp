my_chain_mem m_chain;

struct chain_ftor_t {
    my_chain_mem& operator()(CMainFrame& me) { return me.m_chain; }
};

begin_msg_map
<
    message_handler<WM_CREATE, &_::OnCreate>,
    command_id_handler<ID_VIEW_TOOLBAR, &_::OnViewToolBar>,
    command_id_handler<ID_VIEW_STATUS_BAR, &_::OnViewStatusBar>,
    chain_msg_map_member<chain_ftor_t>,
    // ...
>
end_msg_map;
