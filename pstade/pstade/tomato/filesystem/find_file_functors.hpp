#pragma once

#include <functional> // for std::unary_function
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "../diagnostic/is_valid.hpp"

namespace pstade { namespace tomato {


template< class Sequence >
struct find_file_construct :
	std::unary_function<WIN32_FIND_DATA, Sequence>
{
	Sequence operator()(const WIN32_FIND_DATA& data) const
	{
		return Sequence(boost::begin(data.cFileName), boost::end(data.cFileName));
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
