#pragma once

// See: boost/range/detail/mfc/carray.hpp

#include <boost/config.hpp>
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)


#include <cstddef> // for ptrdiff_t
#include <boost/range/metafunctions.hpp>
#include "../workaround/atl_template.hpp"

namespace boost { // metafunctions


///////////////////////////////////////////////////////////////////////////////
// range_iterator
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_iterator< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{
	typedef KeyT *type;
};

	template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
	struct range_iterator< const ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
		range_iterator< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
	{ };


///////////////////////////////////////////////////////////////////////////////
// range_const_iterator
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_const_iterator< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{
	typedef const KeyT *type;
};

	template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
	struct range_const_iterator< const ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
		range_const_iterator< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
	{ };


///////////////////////////////////////////////////////////////////////////////
// range_difference
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_difference< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{
	typedef std::ptrdiff_t type;
};

	template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
	struct range_difference< const ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
		range_difference< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
	{ };


///////////////////////////////////////////////////////////////////////////////
// range_size
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_size< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{
	typedef int type;
};

	template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
	struct range_size< const ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
		range_size< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
	{ };


///////////////////////////////////////////////////////////////////////////////
// range_value
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_value< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{
	typedef KeyT type;
};

template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS >
struct range_value< const ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > > :
	range_value< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >
{ };


} // namespace boost


namespace ATL { // functions


///////////////////////////////////////////////////////////////////////////////
// begin
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
typename boost::range_iterator< CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >::type
boost_range_begin(CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr)
{
	return arr.GetData();
}

template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
typename boost::range_const_iterator< ATL::CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >::type
boost_range_begin(const CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr)
{
	return arr.GetData();
}


///////////////////////////////////////////////////////////////////////////////
// size
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
typename boost::range_size< CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >::type
boost_range_size(const CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr)
{
	return arr.GetSize();
}


///////////////////////////////////////////////////////////////////////////////
// end
//
template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
typename boost::range_iterator< CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >::type
boost_range_end(CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr)
{
	return arr.GetData() + arr.GetSize();
}

	template< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS > inline
	typename boost::range_const_iterator< CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS > >::type
	boost_range_end(const CSimpleArray< PSTADE_TOMATO_WORKAROUND_ATL_CSIMPLEARRAY_TEMPLATE_ARGS >& arr)
	{
		return arr.GetData() + arr.GetSize();
	}


} // namespace ATL


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
