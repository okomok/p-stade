begin_msg_map
<
    alt_msg_map<0,
        message_handler<WM_CREATE, &_::OnCreate>,
        message_handler<WM_KEYDOWN, &_::OnKey>,
        message_handler<WM_KEYUP, &_::OnKey>,
        message_handler<WM_LBUTTONDOWN, &_::OnKey>
    >,
    alt_msg_map<1,
        command_id_handler<ID_EDIT_UNDO, &_::OnEditUndo>,
        command_id_handler<ID_EDIT_CUT, &_::OnEditCut>,
        command_id_handler<ID_EDIT_COPY, &_::OnEditCopy>,
        command_id_handler<ID_EDIT_PASTE, &_::OnEditPaste>,
        command_id_handler<ID_EDIT_CLEAR, &_::OnEditClear>,
        command_id_handler<ID_EDIT_SELECT_ALL, &_::OnEditSelectAll>
    >,
    assert_valid_msg_map_id< ketchup::idset<0, 1> >
>
end_msg_map;
