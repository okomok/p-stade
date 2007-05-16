template< class DerivedMessageProcessor >
BOOL process_window_message(DerivedMessageProcessor& derived,
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);
