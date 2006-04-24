BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg,
    WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0)
{
    return pstade::ketchup::process_window_message(*this, hWnd, uMsg,
        wParam, lParam, lResult, dwMsgMapID);
}