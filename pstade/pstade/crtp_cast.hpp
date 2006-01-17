#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_NO_MEMBER_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace pstade {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_CRTP_CAST_NO_AUTO_DERIVED
//
#if defined(BOOST_NO_MEMBER_TEMPLATES)
	#define PSTADE_CRTP_CAST_NO_AUTO_DERIVED
#endif


///////////////////////////////////////////////////////////////////////////////
// crtp_cast
//
template< class DerivedT, class BaseT > inline
DerivedT& crtp_cast(BaseT *pbase BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(DerivedT))
{	
	BOOST_STATIC_ASSERT((boost::is_base_of<BaseT, DerivedT>::value));

	return static_cast<DerivedT&>(*pbase);
}


#if !defined(PSTADE_CRTP_CAST_NO_AUTO_DERIVED)


namespace crtp_cast_detail {

	template< class BaseT >
	struct auto_derived_type
	{
		explicit auto_derived_type(BaseT *pbase) :
			m_pbase(pbase)
		{ };

		template< class DerivedT >
		operator DerivedT& ()
		{
			return pstade::crtp_cast<DerivedT>(m_pbase);
		}

		template< class DerivedT >
		operator DerivedT *()
		{
			return &pstade::crtp_cast<DerivedT>(m_pbase);
		}

	private:
		BaseT *m_pbase;
	};

} // namespace crtp_cast_detail


///////////////////////////////////////////////////////////////////////////////
// auto_derived
//
template< class BaseT > inline
crtp_cast_detail::auto_derived_type<BaseT> auto_derived(BaseT *pbase)
{
	// return crtp_cast_detail::auto_derived_type<BaseT>(pbase);

	// Workaround:
	//   If tmp is missing like above, GCC3.4.4 tries to convert 'auto_derived_type' to
	//   itself using the first conversion operator template.
	//   For its constructor? I don't know why.

	crtp_cast_detail::auto_derived_type<BaseT> tmp(pbase);
	return tmp;
}


#endif // !defined(PSTADE_CRTP_CAST_NO_AUTO_DERIVED)


} // namespace pstade
