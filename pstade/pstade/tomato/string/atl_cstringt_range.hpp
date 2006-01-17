#pragma once

// See: boost/range/detail/mfc/cstring.hpp

#if (_ATL_VER >= 0x0700)

#include <cstddef>
#include <atlstr.h>
#include <boost/range/metafunctions.hpp>

namespace boost { // matafunctions


///////////////////////////////////////////////////////////////////////////////
// range_iterator
//
template< class BaseT, class TraitsT >
struct range_iterator< ATL::CStringT<BaseT, TraitsT> >
{
	typedef typename ATL::CStringT<BaseT, TraitsT>::PXSTR type;
};


///////////////////////////////////////////////////////////////////////////////
// range_const_iterator
//
template< class BaseT, class TraitsT >
struct range_const_iterator< ATL::CStringT<BaseT, TraitsT> >
{
	typedef typename ATL::CStringT<BaseT, TraitsT>::PCXSTR type;
};


///////////////////////////////////////////////////////////////////////////////
// range_difference
//
template< class BaseT, class TraitsT >
struct range_difference< ATL::CStringT<BaseT, TraitsT> >
{
	typedef std::ptrdiff_t type;
};


///////////////////////////////////////////////////////////////////////////////
// range_size
//
template< class BaseT, class TraitsT >
struct range_size< ATL::CStringT<BaseT, TraitsT> >
{
	typedef int type;
};


///////////////////////////////////////////////////////////////////////////////
// range_value
//
template< class BaseT, class TraitsT >
struct range_value< ATL::CStringT<BaseT, TraitsT> >
{
	typedef typename ATL::CStringT<BaseT, TraitsT>::XCHAR type;
};


} // namespace boost


namespace ATL { // functions

// Note: The followings are required because primary templates eat CSimpleStringT's.


///////////////////////////////////////////////////////////////////////////////
// begin
//
template< class BaseT, class TraitsT > inline
typename boost::range_iterator< ATL::CStringT<BaseT, TraitsT> >::type
boost_range_begin(CStringT<BaseT, TraitsT>& str)
{
	return str.GetBuffer(0);
}

template< class BaseT, class TraitsT > inline
typename boost::range_const_iterator< CStringT<BaseT, TraitsT> >::type
boost_range_begin(const CStringT<BaseT, TraitsT>& str)
{
	return str.GetString();
}


///////////////////////////////////////////////////////////////////////////////
// size
//
template< class BaseT, class TraitsT > inline
typename boost::range_size< CStringT<BaseT, TraitsT> >::type
boost_range_size(const CStringT<BaseT, TraitsT>& str)
{
	return str.GetLength();
}


///////////////////////////////////////////////////////////////////////////////
// end
//
template< class BaseT, class TraitsT > inline
typename boost::range_iterator< CStringT<BaseT, TraitsT> >::type
boost_range_end(CStringT<BaseT, TraitsT>& str)
{
	return str.GetBuffer(0) + str.GetLength();
}

template< class BaseT, class TraitsT > inline
typename boost::range_const_iterator< CStringT<BaseT, TraitsT> >::type
boost_range_end(const CStringT<BaseT, TraitsT>& str)
{
	return str.GetString() + str.GetLength();
}


} // namespace ATL

#endif // (_ATL_VER >= 0x0700)
