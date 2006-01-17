#pragma once

#if !defined(PSTADE_CFG_NO_STD_IOSTREAM)


#include <cstddef> // for ptrdiff_t
#include <iosfwd> // for basic_istream
#include <iterator> // for istream_iterator
#include <string> // for char_traits
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/iterator_range.hpp>
#include <boost/type.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// istream_range
//
template<
	class T,
	class CharT = char,
	class TraitsT = std::char_traits<CharT>,
	class DistanceT = std::ptrdiff_t
>
struct istream_range :
	boost::iterator_range< std::istream_iterator<T, CharT, TraitsT, DistanceT> >
{
private:
	typedef std::istream_iterator<T, CharT, TraitsT, DistanceT> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit istream_range(std::basic_istream<CharT, TraitsT>& in) :
		super_t(iter_t(in), iter_t())
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_istream_range
//   This code shows why we cannot use 'explicit template parameters'.
//
template< class T, class CharT, class TraitsT, class DistanceT > inline
istream_range<T, CharT, TraitsT, DistanceT>
make_istream_range(boost::type<T>, std::basic_istream<CharT, TraitsT>& in, boost::type<DistanceT>)
{
	return istream_range<T, CharT, TraitsT, DistanceT>(in);
}

// default DistanceT
template< class T, class CharT, class TraitsT > inline
istream_range<T, CharT, TraitsT>
make_istream_range(boost::type<T>, std::basic_istream<CharT, TraitsT>& in)
{
	return istream_range<T, CharT, TraitsT>(in);
}

// CharT == T
template< class CharT, class TraitsT, class DistanceT > inline
istream_range<CharT, CharT, TraitsT, DistanceT>
make_istream_range(std::basic_istream<CharT, TraitsT>& in, boost::type<DistanceT>)
{
	return istream_range<CharT, CharT, TraitsT, DistanceT>(in);
}

// CharT == T, default DistanceT
template< class CharT, class TraitsT > inline
istream_range<CharT, CharT, TraitsT>
make_istream_range(std::basic_istream<CharT, TraitsT>& in)
{
	return istream_range<CharT, CharT, TraitsT>(in);
}


} } // namespace pstade::oven


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class T, class CharT, class TraitsT, class DistanceT > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::istream_range<T, CharT, TraitsT, DistanceT> *&, boost::foreach::tag)
{ return 0; }


#endif // !defined(PSTADE_CFG_NO_STD_IOSTREAM)
