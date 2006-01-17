#pragma once

#include <functional>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/candy/test_any.hpp>

namespace pstade { namespace tomato {


template< DWORD attr >
struct find_file_matches_mask :
	std::unary_function<WIN32_FIND_DATA, bool>
{
	bool operator()(const WIN32_FIND_DATA& data) const
	{
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
		return candy::test_any(data.dwFileAttributes, attr);
#else
		// Workaround: C2891
		DWORD attr_ = attr;
		return candy::test_any(data.dwFileAttributes, attr_);
#endif
	}
};

struct find_file_is_read_only :
	find_file_matches_mask<FILE_ATTRIBUTE_READONLY>
{ };

struct find_file_is_directory :
	find_file_matches_mask<FILE_ATTRIBUTE_DIRECTORY>
{ };

struct find_file_is_compressed :
	find_file_matches_mask<FILE_ATTRIBUTE_COMPRESSED>
{ };

struct find_file_is_system :
	find_file_matches_mask<FILE_ATTRIBUTE_SYSTEM>
{ };

struct find_file_is_hidden :
	find_file_matches_mask<FILE_ATTRIBUTE_HIDDEN>
{ };

struct find_file_is_temporary :
	find_file_matches_mask<FILE_ATTRIBUTE_TEMPORARY>
{ };

struct find_file_is_normal :
	find_file_matches_mask<FILE_ATTRIBUTE_NORMAL>
{ };

struct find_file_is_archived :
	find_file_matches_mask<FILE_ATTRIBUTE_ARCHIVE>
{ };

struct find_file_is_dots :
	std::unary_function<WIN32_FIND_DATA, bool>
{
	bool operator()(const WIN32_FIND_DATA& data) const
	{
		return
			find_file_is_directory()(data) &&
			data.cFileName[0] == _T('.') &&
			(
				data.cFileName[1] == _T('\0') ||
				(
					data.cFileName[1] == _T('.') && 
					data.cFileName[2] == _T('\0')
				)
			)
		;
	}
};


} } // namespace pstade::tomato
