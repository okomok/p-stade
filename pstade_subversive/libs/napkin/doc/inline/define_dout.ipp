struct dout_type
{
    void operator<<(const TCHAR *psz)
    {
        ::OutputDebugString(psz);
    }
};