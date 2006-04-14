#ifndef PSTADE_OVEN_FILE_RANGE_HPP
#define PSTADE_OVEN_FILE_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/utility/base_from_member.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template<
	class CharT = char
>
struct file_range :
	private boost::base_from_member< boost::spirit::file_iterator<CharT> >,
	boost::iterator_range< boost::spirit::file_iterator<CharT> >
{
private:
	typedef boost::spirit::file_iterator<CharT> iter_t;
	typedef boost::base_from_member<iter_t> initializer_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit file_range(const std::string& path) :
		initializer_t(path),
		super_t(
			initializer_t::member,
			initializer_t::member ? initializer_t::member.make_end() : initializer_t::member
		)
	{ }

	bool is_open() const
	{ return initializer_t::member; }
};


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::file_range, 1)


#endif
