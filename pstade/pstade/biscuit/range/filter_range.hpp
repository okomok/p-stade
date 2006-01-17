#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/workaround/warning_no_assignment_operator.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "../state/null_state.hpp"
#include "./filter_iterator.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// filter_range
//
template< class Parser, class ForwardRange, class UserState >
struct filter_range;


template< class Parser, class ForwardRange, class UserState >
struct filter_range_super
{
	typedef boost::iterator_range<
		biscuit::filter_iterator<
			Parser,
			typename boost::range_result_iterator<ForwardRange>::type,
			UserState
		>
	> type;
};


template< class Parser, class ForwardRange, class UserState = null_state_type >
struct filter_range :
	filter_range_super<Parser, ForwardRange, UserState>::type
{
private:
	typedef typename filter_range_super<Parser, ForwardRange, UserState>::type super_t;

public:
	explicit filter_range(ForwardRange& r, UserState& us = null_state) :
		super_t(
			biscuit::make_filter_iterator<Parser>(boost::begin(r), boost::end(r), &us),
			biscuit::make_filter_iterator<Parser>(boost::end(r), boost::end(r), &us)
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_filter_range
//
template< class Parser, class ForwardRange, class UserState > inline
typename pstade::disable_if_const< ForwardRange, filter_range<Parser, ForwardRange, UserState> >::type
make_filter_range(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return filter_range<Parser, ForwardRange, UserState>(r, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState > inline
	filter_range<Parser, ForwardRange const, UserState>
	make_filter_range(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return filter_range<Parser, ForwardRange const, UserState>(r, us);
	}
#endif

// no user-state
template< class Parser, class ForwardRange > inline
typename pstade::disable_if_const< ForwardRange, filter_range<Parser, ForwardRange> >::type
make_filter_range(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return filter_range<Parser, ForwardRange>(r);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange > inline
	filter_range<Parser, ForwardRange const>
	make_filter_range(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return filter_range<Parser, ForwardRange const>(r);
	}
#endif


namespace filter_range_detail {


	template< class Parser, class UserState >
	struct adaptor
	{
		adaptor(UserState& us) : m_us(us) { }
		UserState& m_us;
		PSTADE_WORKAROUND_WARNING_NO_ASSIGNMENT_OPERATOR(adaptor)
	};


	template< class Parser, class ForwardRange, class UserState > inline
	filter_range<Parser, ForwardRange, UserState>
	operator|(ForwardRange& rng, adaptor<Parser, UserState> ad)
	{
		return biscuit::make_filter_range<Parser>(rng, ad.m_us);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class Parser, class ForwardRange, class UserState > inline
		filter_range<Parser, ForwardRange const, UserState>
		operator|(ForwardRange const& rng, adaptor<Parser, UserState> ad)
		{
			return biscuit::make_filter_range<Parser>(rng, ad.m_us);
		}
	#endif


} // namespace filter_range_detail


///////////////////////////////////////////////////////////////////////////////
// filtered
//
template< class Parser, class UserState > inline
filter_range_detail::adaptor<Parser, UserState>
filtered(UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return filter_range_detail::adaptor<Parser, UserState>(us);
}

// no user-state
template< class Parser > inline
filter_range_detail::adaptor<Parser, null_state_type>
filtered(BOOST_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return filter_range_detail::adaptor<Parser, null_state_type>(null_state);
}


} } // namespace pstade::biscuit

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class Parser, class ForwardRange, class UserState > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::biscuit::filter_range<Parser, ForwardRange, UserState> *&, boost::foreach::tag)
{ return 0; }
