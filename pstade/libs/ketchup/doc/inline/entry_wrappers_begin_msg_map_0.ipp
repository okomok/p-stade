struct cmd_ui_map_sub;  // forward declaration also works fine.
    
// which do you like typedef...
typedef begin_msg_map<
    cmd_ui_handler<ID_BLACK, &_::OnUpdateBlack>,
    cmd_ui_handler<ID_RED, &_::OnUpdateRed>,
    cmd_ui_handler<ID_GREEN, &_::OnUpdateGreen>,
    cmd_ui_map_sub              // chain
> cmd_ui_map;

// or struct?
struct cmd_ui_map_sub : begin_msg_map<
    cmd_ui_handler<ID_BLUE, &_::OnUpdateBlue>,
    begin_msg_map<              // chain
        cmd_ui_handler<ID_WHITE, &_::OnUpdateWhite>,
        cmd_ui_handler<ID_CUSTOM, &_::OnUpdateCustom>
    >
> { };

begin_msg_map
<
    cmd_ui_map,                     // chain
    msg_wm_paint<&_::OnPaint>,
    command_range_handler<ID_BLACK, ID_WHITE, &_::OnColor>,
    command_id_handler<ID_CUSTOM, &_::OnCustomColor>
>
end_msg_map;
