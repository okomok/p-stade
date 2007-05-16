#include <pstade/ketchup.hpp>

class CMainFrame :
    public pstade::ketchup::message_processor<CMainFrame,
        WTL::CFrameWindowImpl<CMainFrame>,
        WTL::CUpdateUI<CMainFrame>
    >,
    public WTL::CMessageFilter, public WTL::CIdleHandler
{