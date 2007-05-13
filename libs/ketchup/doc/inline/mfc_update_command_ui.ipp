void OnUpdateViewStatusBar(ketchup::cmd_ui& ui)
{
    ui.set_check(::IsWindowVisible(m_hWndStatusBar));
}

virtual BOOL OnIdle()
{
    ketchup::update_toolbar_cmd_ui(m_hWnd, m_wndToolBar);
    return FALSE;
}

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
    // ...
>
end_msg_map;
