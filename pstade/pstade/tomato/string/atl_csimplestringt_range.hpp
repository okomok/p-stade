#pragma once

// See: boost/range/detail/mfc/cstring.hpp or boost/regex/mfc.hpp

#if (_ATL_VER >= 0x0700) // has ADL.

#include <atlstr.h>
#include <boost/range/metafunctions.hpp>
#include "../workaround/atl_template.hpp"

namespace boost { // metafunctions


///////////////////////////////////////////////////////////////////////////////
// range_iterator
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
struct range_iterator< ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >
{
	typedef typename ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >::PXSTR type;
};


///////////////////////////////////////////////////////////////////////////////
// range_const_iterator
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
struct range_const_iterator< ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >
{
	typedef typename ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >::PCXSTR type;
};


///////////////////////////////////////////////////////////////////////////////
// range_difference
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
struct range_difference< ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >
{
	typedef std::ptrdiff_t type;
};


///////////////////////////////////////////////////////////////////////////////
// range_size
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
struct range_size< ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >
{
	typedef int type;
};


///////////////////////////////////////////////////////////////////////////////
// range_value
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS >
struct range_value< ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >
{
	typedef typename ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >::XCHAR type;
};


} // namespace boost


namespace ATL { // metafunctions


///////////////////////////////////////////////////////////////////////////////
// begin
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
typename boost::range_iterator< CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >::type
boost_range_begin(CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str)
{
	return str.GetBuffer(0);
}

template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
typename boost::range_const_iterator< CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >::type
boost_range_begin(const ATL::CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str)
{
	return str.GetString();
}


///////////////////////////////////////////////////////////////////////////////
// size
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
typename boost::range_size< CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >::type
boost_range_size(const CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str)
{
	return str.GetLength();
}


///////////////////////////////////////////////////////////////////////////////
// end
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
typename boost::range_iterator< CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >::type
boost_range_end(CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str)
{
	return str.GetBuffer(0) + str.GetLength();
}

template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
typename boost::range_const_iterator< CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > >::type
boost_range_end(const CSimpleStringT< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str)
{
	return str.GetString() + str.GetLength();
}


} // namespace boost

#endif // (_ATL_VER >= 0x0700)
