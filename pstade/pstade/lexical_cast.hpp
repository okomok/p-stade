#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>


namespace pstade {


template< class TargetT, class SourceT > inline const
TargetT lexical_cast(const SourceT& src)
{
	return boost::lexical_cast<TargetT>(src);
}


namespace lexical_detail {


	template< class SourceT >
	struct temp
	{
		explicit temp(const SourceT& src) :
			m_psrc(&src)
		{ }

		template< class TargetT >
		operator TargetT() const
		{
			return pstade::lexical_cast<TargetT>(*m_psrc);
		}

	private:
		const SourceT *m_psrc;
	};


} // namespace lexical_detail


template< class SourceT > inline const
lexical_detail::temp<SourceT> lexical(const SourceT& src)
{
	return lexical_detail::temp<SourceT>(src);
}


#if 0

// yet another interface
//


// boost::optional<int> x = string_to<int>(str);

// throw ver.
// pstade::require(x);
// std::cout << x;

// condition ver.
// if (!x)
//     std::cout << x;


template< class TargetT, class SourceT > inline const
boost::optional<TargetT> string_to(const SourceT& src)
{
	try {
		return boost::optional<TargetT>(
			boost::lexical_cast<TargetT>(src)
		);
	}
	catch (...) {
		return boost::optional<TargetT>();
	}
}


template< class TargetT, class SourceT > inline const
boost::optional<TargetT> to_string(const SourceT& src)
{
	try {
		return boost::optional<TargetT>(
			boost::lexical_cast<TargetT>(src)
		);
	}
	catch (...) {
		return boost::optional<TargetT>();
	}
}


#endif // 0


} // namespace pstade


#endif
