#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_NO_MEMBER_TEMPLATES
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/workaround/warning_no_assignment_operator.hpp>

namespace pstade { namespace stove {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_STOVE_CONSTRUCT_NO_AUTO_SEQUENCE
//
#if defined(BOOST_NO_MEMBER_TEMPLATES)
	#define PSTADE_STOVE_CONSTRUCT_NO_AUTO_SEQUENCE
#endif


///////////////////////////////////////////////////////////////////////////////
// construct
//
template< class StlSequence, class Range > inline
StlSequence construct(const Range& rng BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(StlSequence))
{
	return StlSequence(boost::const_begin(rng), boost::const_end(rng));
}


#if !defined(PSTADE_STOVE_CONSTRUCT_NO_AUTO_SEQUENCE)


namespace construct_detail {

	template< class Range >
	struct auto_sequence_type
	{
		explicit auto_sequence_type(const Range& rng) :
			m_rng(rng)
		{ }

		template< class StlSequence >
		operator StlSequence ()
		{
			return stove::construct<StlSequence>(m_rng);
		}

	private:
		const Range& m_rng;

		PSTADE_WORKAROUND_WARNING_NO_ASSIGNMENT_OPERATOR(auto_sequence_type)
	};

} // construct_detail


///////////////////////////////////////////////////////////////////////////////
// auto_sequence
//
template< class Range > inline
construct_detail::auto_sequence_type<Range> auto_sequence(const Range& rng)
{
	// Topic:
	//   When tmp is missing under GCC3.4.4, I ran a foul of strange behaviors
	//   if conversion template target is reference type.
 
	construct_detail::auto_sequence_type<Range> tmp(rng);
	return tmp;
}


#endif // !defined(PSTADE_STOVE_CONSTRUCT_NO_AUTO_SEQUENCE)


} } // namespace pstade::stove
