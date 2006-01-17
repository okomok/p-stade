#pragma once

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "./tab_unexpand_iterator.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// tab_unexpand_range
//
template< class ForwardRange >
struct tab_unexpand_range :
	boost::iterator_range<
		tab_unexpand_iterator<
			typename boost::range_result_iterator<ForwardRange>::type
		>
	>
{
	typedef typename boost::range_result_iterator<ForwardRange>::type base_iterator;

private:
	typedef tab_unexpand_iterator<base_iterator> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	tab_unexpand_range(ForwardRange& rng, int tabsize) :
		super_t(
			iter_t(boost::begin(rng), boost::end(rng), tabsize),
			iter_t(boost::end(rng), boost::end(rng), tabsize)
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_tab_unexpand_range
//
template< class ForwardRange > inline
tab_unexpand_range<ForwardRange>
make_tab_unexpand_range(ForwardRange& rng, int tabsize)
{
	return tab_unexpand_range<ForwardRange>(rng, tabsize);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template<class ForwardRange > inline
	tab_unexpand_range<const ForwardRange>
	make_tab_unexpand_range(const ForwardRange& rng, int tabsize)
	{
		return tab_unexpand_range<const ForwardRange>(rng, tabsize);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// tab_unexpand_range_adaptor
//
struct tab_unexpanded
{
	tab_unexpanded(int tabsize) : m_tabsize(tabsize) { }
	int m_tabsize;
};


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class ForwardRange > inline
tab_unexpand_range<ForwardRange>
operator|(ForwardRange& rng, tab_unexpanded ad)
{
	return oven::make_tab_unexpand_range(rng, ad.m_tabsize);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class ForwardRange > inline
	tab_unexpand_range<const ForwardRange>
	operator|(const ForwardRange& rng, tab_unexpanded ad)
	{
		return oven::make_tab_unexpand_range(rng, ad.m_tabsize);
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class ForwardRange > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::tab_unexpand_range<ForwardRange> *&, boost::foreach::tag)
{ return 0; }
