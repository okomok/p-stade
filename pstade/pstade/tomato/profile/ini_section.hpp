#pragma once

// See: MFC7::CWinApp::WriteProfileXXX

#if !defined(_WIN32_WCE)


#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <pstade/overload.hpp>
#include "../cast/boolean_cast.hpp"
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/is_valid_address.hpp"
#include "../diagnostic/verify.hpp"
#include "../filesystem/build_module_file_name_extension.hpp"

namespace pstade { namespace tomato {


template< class StringT >
struct ini_section
{
	// structors
	ini_section()
	{ }

	ini_section(LPCTSTR pszFileName, LPCTSTR pszSectionName)
	{
		open(pszFileName, pszSectionName);
	}

	void open(LPCTSTR pszFileName, LPCTSTR pszSectionName)
	{
		m_file_name = pszFileName;
		m_section_name = pszSectionName;

		tomato::verify(m_file_name.GetLength() < 4095); // can't read in bigger
	}

	void close()
	{
		m_file_name.Empty();
		m_section_name.Empty();
	}

	// accessors
	StringT get_file_name() const
	{
		return m_file_name;
	}

	StringT get_section_name() const
	{
		return m_section_name;
	}

	bool is_open() const
	{
		return !m_file_name.IsEmpty() && !m_section_name.IsEmpty();
	}

	// profile functions
	void pstade_tomato_profile_initialize(LPCTSTR pszName)
	{
		StringT ini;
		tomato::build_module_file_name_extension(ini, _T(".ini"));
		open(ini, pszName);
	}

	void pstade_tomato_profile_set_string(LPCTSTR pszValueName, LPCTSTR pszValue)
	{
		ATLASSERT(is_open());
		ATLASSERT(tomato::is_valid(pszValueName)); // Note: if pszValue is NULL, section is deleted.
		ATLASSERT(tomato::is_valid(pszValue));

		tomato::api_verify(::WritePrivateProfileString(m_section_name, pszValueName, pszValue, m_file_name));
	}

	bool pstade_tomato_profile_query_string(LPCTSTR pszValueName, TCHAR *pValueBuf, ULONG& ulBufs)
	{
		ATLASSERT(is_open());
		ATLASSERT(tomato::is_valid(pszValueName));
		ATLASSERT(tomato::is_valid_address(pValueBuf, ulBufs)); // ini-section can't determine ulBufs

		{
			// empty-string is also valid value, so we must do...
			typedef boost::mpl::int_<9> magic_sz_bufs;
			TCHAR const magic_sz[magic_sz_bufs::value] = _T("ABCD0123");
			TCHAR sz[magic_sz_bufs::value];
			::GetPrivateProfileString(m_section_name, pszValueName, magic_sz, sz, magic_sz_bufs::value, m_file_name);

			if (lstrcmp(sz, magic_sz) == 0)
				return false;
		}

		// ulBufs contains NULL ( == buffer size) >= 1
		::GetPrivateProfileString(m_section_name, pszValueName, _T(""), pValueBuf, ulBufs, m_file_name);
		return true;
	}

	bool pstade_tomato_profile_delete(LPCTSTR pszValueName)
	{
		ATLASSERT(is_open());
		ATLASSERT(tomato::is_valid(pszValueName));

		tomato::api_verify(::WritePrivateProfileString(m_section_name, pszValueName, NULL, m_file_name));
	}

private:
	StringT m_file_name, m_section_name;
};


// special function
inline void delete_ini_section(LPCTSTR pszFileName, LPCTSTR pszSectionName)
{
	tomato::api_verify(::WritePrivateProfileString(pszSectionName, NULL, NULL, pszFileName));
}


} } // namespace pstade::tomato


// somewhat optimization
template< class StringT >
bool pstade_tomato_profile_query_dword(
	pstade::tomato::ini_section<StringT>& sect,
	LPCTSTR pszValueName, DWORD& dwValue,
	pstade::overload
)
{
	ATLASSERT(sect.is_open());
	ATLASSERT(pstade::tomato::is_valid(pszValueName));

	typedef boost::mpl::integral_c<INT, 0xABCD0123> magic_number;

	UINT uValue = ::GetPrivateProfileInt(sect.get_section_name(), pszValueName, magic_number::value, sect.get_file_name());
	if (uValue == magic_number::value)
		return false;

	dwValue = uValue;
	return true;
}


#endif // !defined(_WIN32_WCE)
