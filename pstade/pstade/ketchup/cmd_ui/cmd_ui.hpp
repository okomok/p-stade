#ifndef PSTADE_KETCHUP_CMD_UI_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/apple/sdk/windows.hpp>


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
    { return override_enable(on); }

    void set_check(int state)
    { return override_set_check(state); }

    void set_radio(bool on)
    { return override_set_radio(on); }

    void set_text(TCHAR const *psz)
    { return override_set_text(psz); }

    void set_default(bool on)
    { return override_set_default(on); }

    bool is_dependent() const
    { return override_is_dependent(); }

protected:
    ~cmd_ui()
    { }

private:
    virtual void override_enable(bool)
    { }

    virtual void override_set_check(int)
    { }

    virtual void override_set_radio(bool on)
    { set_check(on); }

    virtual void override_set_text(TCHAR const *)
    { }

    virtual void override_set_default(bool)
    { }

    virtual bool override_is_dependent() const
    { return false; }

private:
    UINT m_uID;
    bool m_handled;
};


} } // namespace pstade::ketchup


#endif
