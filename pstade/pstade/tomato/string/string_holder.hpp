#pragma once

// The type erasure for ATL::CString and WTL::CString
// _CSTRING_NS stinks.

namespace pstade { namespace tomato {


// See: boost::any or boost::spirit::rule_t
struct string_placeholder
{
	virtual ~string_placeholder() { }
	virtual LPCTSTR lpctstr() = 0;
	virtual void copy(LPCTSTR) = 0;
	virtual void empty() = 0;
	virtual BOOL is_empty() = 0;
};

template< class StringT >
struct string_holder : string_placeholder
{
// ctor
	string_holder(StringT const& str) : held(str) { }
// overrides
	virtual LPCTSTR lpctstr() { return held; }
	virtual void copy(LPCTSTR psz) { held = psz; }
	virtual void empty() { held.Empty(); }
	virtual BOOL is_empty() { return held.IsEmpty(); }
private:
	StringT held;
};


} } // namespace pstade::tomato
