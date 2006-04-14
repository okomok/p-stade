#ifndef PSTADE_PIZZA_INI_SECTION_HPP
#define PSTADE_PIZZA_INI_SECTION_HPP


// PStade.Pizza
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// MFC7::CWinApp::WriteProfileXXX


#if !defined(_WIN32_WCE)


#include <cstddef> // size_t
#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/size.hpp>
#include <pstade/instance.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/filesystem/module_file_name.hpp>
#include <pstade/tomato/garlic/back_inserter.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/diet/buffer.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/tstring.hpp>


namespace pstade { namespace pizza {


namespace ini_section_detail {


	PSTADE_INSTANCE_ARGS(const tomato::tstring,
		magicStr, (_T("pstade_tomato_ini_section_detail_magic_string"))
	)


	inline
	bool query_string(const TCHAR* pszFileName, const TCHAR* pszSectionName,
		const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
	{
		{
			// empty-string also is valid value, so we must go...

			oven::array_range<TCHAR> buf(1 + boost::size(magicStr));

			::GetPrivateProfileString(
				pszSectionName, pszValueName,
				tomato::c_str(magicStr), // default
				boost::begin(buf), pstade::integral(boost::size(buf)),
				pszFileName);

			if (oven::equals(buf|oven::null_terminated, magicStr))
				return false;
		}

		::GetPrivateProfileString( // bufsz contains NULL (== buffer size) >= 1
			pszSectionName, pszValueName,
			_T(""), pFirst, pstade::integral(pLast - pFirst), pszFileName);

		return true;
	}


} // namespace ini_section_detail


struct ini_section
{
	ini_section()
	{ }

	template< class CStringizeable0, class CStringizeable1 >
	ini_section(const CStringizeable0& fileName, const CStringizeable1& sectionName)
	{
		open(fileName, sectionName);
	}

	template< class CStringizeable0, class CStringizeable1 >
	void open(const CStringizeable0& fileName, const CStringizeable1& sectionName)
	{
		m_fileName = tomato::c_str(fileName);
		m_sectionName = tomato::c_str(sectionName);

		BOOST_ASSERT(boost::size(m_fileName) < 4095); // can't read in bigger
	}

	void close()
	{
		m_fileName.clear();
		m_sectionName.clear();
	}


	tomato::tstring get_file_name() const
	{ return m_fileName; }

	tomato::tstring get_section_name() const
	{ return m_sectionName; }

	bool is_open() const
	{ return !boost::empty(m_fileName) && !boost::empty(m_sectionName); }


typedef ini_section pstade_pizza_profile;

	void pstade_pizza_initialize(const TCHAR *pszName)
	{
		tomato::tstring ini;
		oven::copy(tomato::module_file_name().identifier(), garlic::back_inserter(ini));
		ini += _T(".ini");
		open(ini, pszName);
	}

	void pstade_pizza_set_string(const TCHAR *pszValueName, const TCHAR *pszValue)
	{
		BOOST_ASSERT(is_open());
		BOOST_ASSERT(diet::valid(pszValueName)); // Note: if pszValue is NULL, section is deleted.
		BOOST_ASSERT(diet::valid(pszValue));
		BOOST_ASSERT(!oven::equals(pszValue|oven::null_terminated, ini_section_detail::magicStr));

		PSTADE_REQUIRE(
			::WritePrivateProfileString(
				tomato::c_str(m_sectionName), pszValueName,
				pszValue, tomato::c_str(m_fileName))
		);
	}

	bool pstade_pizza_query_string(const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast)
	{
		BOOST_ASSERT(is_open());
		BOOST_ASSERT(diet::valid(pszValueName));
		BOOST_ASSERT(diet::valid(tomato::buffer(boost::make_iterator_range(pFirst, pLast))));

		return ini_section_detail::query_string(
			tomato::c_str(m_fileName), tomato::c_str(m_sectionName),
			pszValueName, pFirst, pLast);
	}

	bool pstade_pizza_delete(const TCHAR *pszValueName)
	{
		BOOST_ASSERT(is_open());
		BOOST_ASSERT(diet::valid(pszValueName));

		PSTADE_REQUIRE(
			::WritePrivateProfileString(
				tomato::c_str(m_sectionName), pszValueName, NULL, tomato::c_str(m_fileName))
		);
	}

private:
	tomato::tstring m_fileName, m_sectionName;
};


template< class CStringizeable0, class CStringizeable1 > inline
void delete_ini_section(const CStringizeable0& fileName, const CStringizeable1& sectionName)
{
	PSTADE_REQUIRE(
		::WritePrivateProfileString(tomato::c_str(sectionName), NULL, NULL, tomato::c_str(fileName))
	);
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
