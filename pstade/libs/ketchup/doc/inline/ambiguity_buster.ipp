class CMainFrame :
    public WTL::CFrameWindowImpl<CMainFrame>,
    public WTL::CUpdateUI<CMainFrame>,
    public WTL::CMessageFilter,
    public WTL::CIdleHandler,
    public ketchup::message_processor<CMainFrame,
        ketchup::vector<
            my_chain_base_simple1<CMainFrame>,
            my_chain_base_simple2<CMainFrame>
        >
    >
{
    // ...
