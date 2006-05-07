#ifndef PSTADE_KETCHUP_CMD_UI_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/noncopyable.hpp>


namespace pstade { namespace ketchup {


// The reason why is_dependent is public:
//   1. So MFC does.
//   2. enable_cmd_ui_if_handled works easily, for
//      a view can insist "the cmd id is mine!" by one handler.
//
struct cmd_ui :
    private boost::noncopyable
{
    explicit cmd_ui(UINT uID) :
        m_uID(uID), m_handled(false)
    { }

    UINT get_id() const
    { return m_uID; }

    void set_handled(bool handled)
    { m_handled = handled; }

    bool is_handled() const
    { return m_handled; }

    void enable(bool on)
    { impl_enable(on); }

    void set_check(int state)
    { impl_set_check(state); }

    void set_radio(bool on)
    { impl_set_radio(on); }

    void set_text(const TCHAR *psz)
    { impl_set_text(psz); }

    void set_default(bool on)
    { impl_set_default(on); }

    bool is_dependent()
    { return impl_is_dependent(); }

protected:
    ~cmd_ui() { }

    virtual void impl_enable(bool) { }
    virtual void impl_set_check(int) { }
    virtual void impl_set_radio(bool on) { set_check(on); }
    virtual void impl_set_text(const TCHAR *) { }
    virtual void impl_set_default(bool) { }
    virtual bool impl_is_dependent() { return false; }

private:
    UINT m_uID;
    bool m_handled;
};


} } // namespace pstade::ketchup


#endif
