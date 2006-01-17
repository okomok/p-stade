#pragma once

#include <boost/noncopyable.hpp>

namespace pstade { namespace ketchup {


// The reason why is_dependent is public:
//   1. So MFC does.
//   2. enable_cmd_ui_if_handled works easily, for
//      a view can insist "the cmd id is mine!" by one handler.

struct cmd_ui :
	private boost::noncopyable
{
	explicit cmd_ui(UINT uID) :
		m_uID(uID), m_handled(false)
	{ }

	UINT get_id() const { return m_uID; }
	void set_handled(bool handled) { m_handled = handled; }
	bool is_handled() const { return m_handled; }

	void enable(bool on) { enable_impl(on); }
	void set_check(int state) { set_check_impl(state); }
	void set_radio(bool on) { set_radio_impl(on); }
	void set_text(LPCTSTR psz) { set_text_impl(psz); }
	void set_default(bool on) { set_default(on); }
	bool is_dependent() { return is_dependent_impl(); }

protected:
	~cmd_ui() { }

	virtual void enable_impl(bool) { }
	virtual void set_check_impl(int) { }
	virtual void set_radio_impl(bool on) { set_check(on); }
	virtual void set_text_impl(LPCTSTR) { }
	virtual void set_default_impl(bool) { }
	virtual bool is_dependent_impl() { return false; }

private:
	UINT m_uID;
	bool m_handled;
};


} } // namespace pstade::ketchup
