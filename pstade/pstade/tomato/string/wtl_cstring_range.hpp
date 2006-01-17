#pragma once

// See:
//   boost/range/detail/mfc/cstring.hpp
//   http://aspn.activestate.com/ASPN/Mail/Message/boost/2804138

#include <cstddef> // for ptrdiff_t
#include <atlmisc.h> // for WTL::CString
#include <boost/range/metafunctions.hpp>
#include <pstade/oven/workaround/range_metafunction_class.hpp>

namespace boost { // metafunctions


///////////////////////////////////////////////////////////////////////////////
// range_iterator
//
template< >
PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS range_iterator< WTL::CString >
{
public:
	typedef TCHAR *type;
};


///////////////////////////////////////////////////////////////////////////////
// range_const_iterator
//
template< >
PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS range_const_iterator< WTL::CString >
{
public:
	typedef const TCHAR *type;
};


///////////////////////////////////////////////////////////////////////////////
// range_difference
//
template< >
struct range_difference< WTL::CString >
{
public:
	typedef std::ptrdiff_t type;
};


///////////////////////////////////////////////////////////////////////////////
// range_size
//
template< >
PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS range_size< WTL::CString >
{
public:
	typedef int type;
};


///////////////////////////////////////////////////////////////////////////////
// range_value
//
template< >
PSTADE_OVEN_WORKAROUND_RANGE_METAFUNCTION_CLASS range_value< WTL::CString >
{
public:
	typedef TCHAR type;
};


} // namespace boost


#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300) // has ADL.


	namespace WTL { // functions


	///////////////////////////////////////////////////////////////////////////////
	// begin
	//
	inline boost::range_iterator< CString >::type boost_range_begin(CString& str)
	{
		return str.GetBuffer(0);
	}

	inline boost::range_const_iterator< CString >::type boost_range_begin(const CString& str)
	{
		return static_cast<LPCTSTR>(str);
	}


	///////////////////////////////////////////////////////////////////////////////
	// size
	//
	inline boost::range_size< CString >::type boost_range_size(const CString& str)
	{
		return str.GetLength();
	}


	///////////////////////////////////////////////////////////////////////////////
	// end
	//
	inline boost::range_iterator< CString >::type boost_range_end(CString& str)
	{
		return boost_range_begin(str) + boost_range_size(str);
	}

	inline boost::range_const_iterator< CString >::type boost_range_end(const CString& str)
	{
		return boost_range_begin(str) + boost_range_size(str);
	}


	} // namespace WTL


#else


	// Note:
	//   This customization is undocumented.
	//   Even if you overload boost::begin directly, internal compiler errors come.


	namespace boost { namespace range_detail { // functions


	template< >
	class range< WTL::CString >
	{
		typedef WTL::CString type;
	};


	///////////////////////////////////////////////////////////////////////////////
	// begin
	//
	template< >
	struct range_begin< WTL::CString >
	{
		static range_iterator< WTL::CString >::type fun(WTL::CString& str)
		{
			return str.GetBuffer(0);
		}
	};

	template< >
	struct range_begin< const WTL::CString >
	{
		static range_const_iterator< WTL::CString >::type fun(const WTL::CString& str)
		{
			return static_cast<LPCTSTR>(str);
		}
	};


	///////////////////////////////////////////////////////////////////////////////
	// size
	//
	template< >
	struct range_size_< WTL::CString >
	{
		template< class T >
		struct inner
		{
			static range_size< WTL::CString >::type fun(const WTL::CString& str)
			{
				return str.GetLength();
			}
		};
	};

	template< >
	struct range_size_< const WTL::CString > :
		range_size_< WTL::CString >
	{ };


	///////////////////////////////////////////////////////////////////////////////
	// end
	//
	template< >
	struct range_end< WTL::CString >
	{
		template< class T >
		struct inner
		{
			static range_iterator< WTL::CString >::type fun(WTL::CString& str)
			{
				return str.GetBuffer(0) + str.GetLength();
			}
		};
	};

	template< >
	struct range_end< const WTL::CString >
	{
		template< class T >
		struct inner
		{
			static range_const_iterator< WTL::CString >::type fun(const WTL::CString& str)
			{
				return static_cast<LPCTSTR>(str) + str.GetLength();
			}
		};
	};


	} } // namespace boost::range_detail


#endif // !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
