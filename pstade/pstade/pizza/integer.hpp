#ifndef PSTADE_PIZZA_INTEGER_HPP
#define PSTADE_PIZZA_INTEGER_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/empty.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/tomato/c_str.hpp>
#include "./error.hpp"
#include "./string.hpp"


namespace pstade { namespace pizza {


struct invalid_integer :
	error
{
	invalid_integer(const std::string& msg) :
		error(msg)
	{ }
};


namespace integer_detail {


	template< class CStringizable >
	std::string error_msg(const CStringizable& valueName)
	{
		std::stringstream msg;
		msg <<
			"<value-name>" <<
				tomato::c_str(valueName) <<
			"</value-name>";

		return msg.str();
	};


} // namespace integer_detail


template< class IntegerT, class Profile, class CStringizable > const
IntegerT get_integer(Profile& pr, const CStringizable& valueName)
{
	try {
		pizza::string str(pr, valueName);
		return pstade::lexical(str.c_str());
	}
	catch (boost::bad_lexical_cast&) {
		invalid_integer err(integer_detail::error_msg(valueName));
		boost::throw_exception(err);
	}

	return 0;
}


namespace integer_detail {


	template< class Profile, class CStringizable >
	struct temp
	{
		explicit temp(Profile& pr, const CStringizable& valueName) :
			m_ppr(&pr), m_pvalueName(&valueName)
		{ }

		template< class IntegerT >
		operator IntegerT() const
		{
			return pizza::get_integer<IntegerT>(*m_ppr, *m_pvalueName);
		}

	private:
		Profile *m_ppr;
		const CStringizable *m_pvalueName;
	};


} // namespace integer_detail


template< class Profile, class CStringizable > inline const
integer_detail::temp<Profile, CStringizable>
integer(Profile& pr, const CStringizable& valueName)
{
	return integer_detail::temp<Profile, CStringizable>(pr, valueName);
}


} } // namespace pstade::pizza


#endif
