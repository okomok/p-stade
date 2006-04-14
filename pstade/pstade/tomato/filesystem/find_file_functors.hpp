#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_FUNCTORS_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_FUNCTORS_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <functional> // unary_function
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>


namespace pstade { namespace tomato {


template< class Sequence >
struct find_file_construct :
	std::unary_function<WIN32_FIND_DATA, Sequence>
{
	Sequence operator()(const WIN32_FIND_DATA& data) const
	{
		return oven::sequence(data.cFileName|oven::null_terminated);
	}
};


template< class StringT >
struct find_file_stringize :
	std::unary_function<WIN32_FIND_DATA, StringT>
{
	StringT operator()(const WIN32_FIND_DATA& data) const
	{
		return StringT(data.cFileName);
	}
};


} } // namespace pstade::tomato


#endif
