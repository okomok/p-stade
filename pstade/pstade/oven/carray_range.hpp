#pragma once

// is workaround for:
//   1. I guess VC6 has no way of deduction of 'sz' and
//      Boost.Array doesn't support built-in array of non-char anyway.
//   2. Under below Boost 1.34, char array is regarded as null-terminated.

#include <cstddef> // for size_t
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/config.hpp> // for BOOST_RANGE_ARRAY_REF
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/extent.hpp>
#include <pstade/unused.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "./sub_range_base_type.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION
//
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) || defined(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS)
	#define PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION \
	/**/
#endif


namespace carray_range_detail {


	template< class T > inline
	boost::iterator_range< T * >
	aux(T *arr, std::size_t sz)
	{
		return boost::make_iterator_range(arr, arr + sz);
	}


} // namespace carray_range_detail


///////////////////////////////////////////////////////////////////////////////
// carray_range
//
template< class ArrayT >
struct carray_range :
	sub_range_base<ArrayT>::type
{
	typedef typename sub_range_base<ArrayT>::type super_t;

	carray_range(ArrayT& arr, std::size_t sz) :
		super_t(carray_range_detail::aux(arr, sz))
	{ }

#if !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)
	carray_range(ArrayT& arr) :
		super_t(carray_range_detail::aux(arr, boost::extent<ArrayT>::value))
	{ }
#endif
};


///////////////////////////////////////////////////////////////////////////////
// make_carray_range
//
template< class ArrayT > inline
carray_range<ArrayT>
make_carray_range(ArrayT& arr, std::size_t sz)
{
	return carray_range<ArrayT>(arr, sz);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class ArrayT > inline
	carray_range<const ArrayT>
	make_carray_range(const ArrayT& arr, std::size_t sz)
	{
		return carray_range<const ArrayT>(arr, sz);
	}
#endif


#if !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


template< class ArrayT > inline
carray_range<ArrayT>
make_carray_range(ArrayT& arr)
{
	return carray_range<ArrayT>(arr);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class ArrayT > inline
	carray_range<const ArrayT>
	make_carray_range(const ArrayT& arr)
	{
		return carray_range<const ArrayT>(arr);
	}
#endif


#endif // !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


namespace carray_range_detail {


	struct adaptor_sized
	{
		adaptor_sized(std::size_t sz) : m_sz(sz) { }
		std::size_t m_sz;
	};


	template< class ArrayT > inline
	carray_range<ArrayT>
	operator|(ArrayT& arr, adaptor_sized ad)
	{
		return oven::make_carray_range(arr, ad.m_sz);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class ArrayT > inline
		carray_range<const ArrayT>
		operator|(const ArrayT& arr, adaptor_sized ad)
		{
			return oven::make_carray_range(arr, ad.m_sz);
		}
	#endif


#if !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


	struct adaptor
	{ };


	template< class ArrayT > inline
	carray_range<ArrayT>
	operator|(ArrayT& arr, adaptor ad)
	{
		pstade::unused(ad);
		return oven::make_carray_range(arr);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class ArrayT > inline
		carray_range<const ArrayT>
		operator|(const ArrayT& arr, adaptor ad)
		{
			pstade::unused(ad);
			return oven::make_carray_range(arr);
		}
	#endif


#endif // !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


} // namespace carray_range_detail


///////////////////////////////////////////////////////////////////////////////
// carrayed_
//
inline carray_range_detail::adaptor_sized carrayed_(std::size_t sz)
{
	return carray_range_detail::adaptor_sized(sz);
}


#if !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


///////////////////////////////////////////////////////////////////////////////
// carrayed
//
namespace {

static const carray_range_detail::adaptor
carrayed = carray_range_detail::adaptor();

}


#endif // !defined(PSTADE_OVEN_CARRAY_RANGE_NO_SIZE_DEDUCTION)


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class ArrayT > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::carray_range<ArrayT> *&, boost::foreach::tag)
{ return 0; }
