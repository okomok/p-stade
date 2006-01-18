#pragma once

#include <exception>

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// parser_error_base
//
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

///////////////////////////////////////////////////////////////////////////////
// parser_error
//
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
