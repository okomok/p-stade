#pragma once

#include <boost/config.hpp> // for BOOST_NO_MEMBER_TEMPLATES, BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/detail/workaround.hpp>
#include <pstade/workaround/warning_no_copy_constructor.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_TOMATO_NO_AUTO_BOOL
//
#if defined(BOOST_NO_MEMBER_TEMPLATES)
	#define PSTADE_TOMATO_NO_AUTO_BOOL
#endif


///////////////////////////////////////////////////////////////////////////////
// boolean_cast_converter
//
template< class TargetT, class SourceT >
struct boolean_cast_converter;


#define PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargetT, SourceT, Expr) \
	template< > \
	struct boolean_cast_converter<TargetT, SourceT> \
	{ \
		static TargetT convert(SourceT b) \
		{ \
			return Expr; \
		} \
	}; \
/**/

#define PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(TargeT, t, f) \
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargeT, bool, b ? t : f) \
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargeT, BOOL, b ? t : f) \
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargeT, VARIANT_BOOL, b ? t : f) \
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargeT, BOOLEAN, b ? t : f) \
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER(TargeT, LRESULT, b ? t : f) \
/**/


	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(bool, true, false)
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(BOOL, TRUE, FALSE)

	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(BOOLEAN, (BOOLEAN)TRUE, (BOOLEAN)FALSE)
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(LRESULT, 1, 0)

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)   
	#pragma warning(push)
	#pragma warning(disable: 4310)
#endif

	// VARIANT_BOOL b = VARIANT_TRUE; warns...
	PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET(VARIANT_BOOL, VARIANT_TRUE, VARIANT_FALSE)

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)   
	#pragma warning(pop)
#endif


#undef PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER
#undef PSTADE_TOMATO_BOOLEAN_CAST_DETAIL_CONVERTER_SET


///////////////////////////////////////////////////////////////////////////////
// boolean_cast
//
template< class TargetT, class SourceT > inline
TargetT boolean_cast(SourceT arg BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(TargetT))
{
	// See: boost::numeric_cast

	typedef boolean_cast_converter<TargetT, SourceT> converter_t;
	return converter_t::convert(arg);
}


#if !defined(PSTADE_TOMATO_NO_AUTO_BOOL)


namespace boolean_cast_detail {

	template< class SourceT >
	struct auto_bool_type
	{
		explicit auto_bool_type(SourceT b) : m_b(b)
		{ }

		template< class TargetT >
		operator TargetT() const
		{ return tomato::boolean_cast<TargetT>(m_b); }

		PSTADE_WORKAROUND_WARNING_NO_COPY_CONSTRUCTOR(auto_bool_type)

	private:
		SourceT m_b;
	};

} // namespace boolean_cast_detail


///////////////////////////////////////////////////////////////////////////////
// auto_bool
//
template< class SourceT > inline
boolean_cast_detail::auto_bool_type<SourceT> auto_bool(SourceT b)
{
	return boolean_cast_detail::auto_bool_type<SourceT>(b);
}


#endif // !defined(BOOST_NO_MEMBER_TEMPLATES)


} } // namespace pstade::tomato
