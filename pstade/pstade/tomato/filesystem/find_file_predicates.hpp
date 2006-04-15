#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/candy/test_any.hpp>


namespace pstade { namespace tomato {


template< DWORD attr >
struct find_file_matches_mask :
	std::unary_function<WIN32_FIND_DATA, bool>
{
	bool operator()(const WIN32_FIND_DATA& data) const
	{
		return candy::test_any(data.dwFileAttributes, attr);
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


#endif
