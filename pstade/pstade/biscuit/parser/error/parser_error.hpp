#ifndef PSTADE_BISCUIT_PARSER_ERROR_PARSER_ERROR_HPP
#define PSTADE_BISCUIT_PARSER_ERROR_PARSER_ERROR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <exception> // exception


namespace pstade { namespace biscuit {


struct parser_error_base : std::exception
{
protected:
	parser_error_base() { }
	virtual ~parser_error_base() throw() { }

public:
	parser_error_base(parser_error_base const& other) :
		std::exception(other)
	{ }
};


template< class Range, class InfoT >
struct parser_error : parser_error_base
{
	parser_error(Range const& rng, InfoT const& info) :
		m_rng(rng), m_info(info)
	{ }

	virtual char const *what() const throw()
	{
		return "biscuit::parser_error";
	}

	Range const& get_range() const { return m_rng; }
	InfoT const& get_info() const { return m_info; }

private:
	Range m_rng;
	InfoT m_info;
};


} } // namespace pstade::biscuit


#endif
