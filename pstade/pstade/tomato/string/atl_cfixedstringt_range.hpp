#pragma once

// See: boost/range/detail/mfc/cstring.hpp or boost/regex/mfc.hpp

#if (_ATL_VER >= 0x0700) // has ADL.

#include <atlstr.h>
#include <boost/range/metafunctions.hpp>
#include "./atl_csimplestringt_range.hpp"
#include "./atl_cstringt_range.hpp"

namespace boost { // metafunctions


///////////////////////////////////////////////////////////////////////////////
// range_iterator
//
template< class StringT, int chars >
struct range_iterator< ATL::CFixedStringT<StringT, chars> > :
	range_iterator<StringT>
{ };


///////////////////////////////////////////////////////////////////////////////
// range_const_iterator
//
template< class StringT, int chars >
struct range_const_iterator< ATL::CFixedStringT<StringT, chars> > :
	range_const_iterator<StringT>
{ };


///////////////////////////////////////////////////////////////////////////////
// range_difference
//
template< class StringT, int chars >
struct range_difference< ATL::CFixedStringT<StringT, chars> > :
	range_difference<StringT>
{ };


///////////////////////////////////////////////////////////////////////////////
// range_size
//
template< class StringT, int chars >
struct range_size< ATL::CFixedStringT<StringT, chars> > :
	range_size<StringT>
{ };


///////////////////////////////////////////////////////////////////////////////
// range_value
//
template< class StringT, int chars >
struct range_value< ATL::CFixedStringT<StringT, chars> > :
	range_value<StringT>
{ };


} // namespace boost


namespace ATL { // functions


///////////////////////////////////////////////////////////////////////////////
// begin
//
template< class StringT, int chars > inline
typename boost::range_iterator< CFixedStringT<StringT, chars> >::type
boost_range_begin(CFixedStringT<StringT, chars>& str)
{
	return str.GetBuffer(0);
}

template< class StringT, int chars > inline
typename boost::range_const_iterator< CFixedStringT<StringT, chars> >::type
boost_range_begin(const CFixedStringT<StringT, chars>& str)
{
	return str.GetString();
}


///////////////////////////////////////////////////////////////////////////////
// size
//
template< class StringT, int chars > inline
typename boost::range_size< CFixedStringT<StringT, chars> >::type
boost_range_size(const CFixedStringT<StringT, chars>& str)
{
	return str.GetLength();
}


///////////////////////////////////////////////////////////////////////////////
// end
//
template< class StringT, int chars > inline
typename boost::range_iterator< CFixedStringT<StringT, chars> >::type
boost_range_end(CFixedStringT<StringT, chars>& str)
{
	return str.GetBuffer(0) + str.GetLength();
}

template< class StringT, int chars > inline
typename boost::range_const_iterator< CFixedStringT<StringT, chars> >::type
boost_range_end(const CFixedStringT<StringT, chars>& str)
{
	return str.GetString() + str.GetLength();
}


} // namespace ATL

#endif // (_ATL_VER >= 0x0700)
