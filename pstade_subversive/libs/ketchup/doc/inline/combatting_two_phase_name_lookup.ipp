template< class D >
struct CMainFrameCommand1 :
    pstade::ketchup::message_processor< CMainFrameCommand1<D> >
{
    // ...

public:
    typedef CMainFrameCommand1 _;                           typename _::template // must be added.
    begin_msg_map
    <                                                       typename _::template
        command_id_handler<ID_APP_EXIT, &_::OnFileExit>,    typename _::template
        command_id_handler<ID_FILE_NEW, &_::OnFileNew>
    >
    end_msg_map;
};