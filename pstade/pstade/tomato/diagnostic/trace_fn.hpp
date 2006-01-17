#pragma once

// Note:
//   The original version CTraceFn was written by Paul DiLascia.
//   CTraceFn represented "trace a function name".
//   On the other hand, trace_fn represents "fancy trace".
//   trace_fn depends on optimizer..., but that is the modern programming.
//
// See:
//   http://www.dilascia.com/index.htm
//   http://www.microsoft.com/msj/0197/mfcp1/mfcp1.aspx

#include <cstdarg>
#include <typeinfo>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <pstade/is_debug.hpp>

namespace pstade { namespace tomato {


// local macro
#define PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(dwCategory, nLevel) \
	output_header<HeaderT, SpaceCountT>(); \
	va_list ptr; \
	va_start(ptr, pszFormat); \
	ATL::CTrace::s_trace.TraceV(NULL, -1, dwCategory, nLevel, pszFormat, ptr); \
	va_end(ptr); \
	ATL::AtlTrace(_T("\n")); \
/**/


namespace trace_fn_detail {

	// Workaround: if inline missing, the compiler doesn't remove s_count.
	inline LONG& indent_count()
	{
		static LONG s_count = -1;
		return s_count;
	}

	struct output_header_
	{
		template< class HeaderT >
		static void execute()
		{
			// Workaround: For the compiler, it seems better to define a named object.
			const std::type_info& tid = typeid(HeaderT);
			ATLTRACE(tid.name());
			ATLTRACE(_T("::"));
		}

		typedef output_header_ type;
	};

	struct output_no_header_
	{
		template< class HeaderT >
		static void execute() { }
		
		typedef output_no_header_ type;
	};

	template< class HeaderT, class SpaceCountT >
	void output_header()
	{
		for (int i = 0, count = SpaceCountT::value * indent_count(); i < count; ++i) {
			ATL::AtlTrace(_T(" "));
		}

		typedef typename
		boost::mpl::eval_if< boost::is_same<HeaderT, boost::mpl::void_>,
			output_no_header_,
			output_header_
		>::type output_t;

		output_t::execute<HeaderT>();
	}

	struct trace_impl_on_base
	{
		trace_impl_on_base() { ::InterlockedIncrement(&indent_count()); }
		~trace_impl_on_base() { ::InterlockedDecrement(&indent_count()); }
	};

	template< class HeaderT, class SpaceCountT >
	struct on : trace_impl_on_base
	{
		on() { }

		// ctor style
		on(LPCSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(ATL::atlTraceGeneral, 0);
		}

		on(LPCWSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(ATL::atlTraceGeneral, 0);
		}

		on(DWORD_PTR dwCategory, UINT nLevel, LPCSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(dwCategory, nLevel);
		}

		on(DWORD_PTR dwCategory, UINT nLevel, LPCWSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(dwCategory, nLevel);
		}

		// operator() style
		void operator()(LPCSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(ATL::atlTraceGeneral, 0);
		}

		void operator()(LPCWSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(ATL::atlTraceGeneral, 0);
		}

		void operator()(DWORD_PTR dwCategory, UINT nLevel, LPCSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(dwCategory, nLevel);
		}

		void operator()(DWORD_PTR dwCategory, UINT nLevel, LPCWSTR pszFormat, ...)
		{
			PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL(dwCategory, nLevel);
		}

		typedef on type;
	};

	struct off
	{
		off() { }
		// ctor style
		off(LPCSTR, ...) { }
		off(LPCWSTR, ...) { }
		off(DWORD_PTR, UINT, LPCSTR, ...) { }
		off(DWORD_PTR, UINT, LPCWSTR, ...) { }
		// operator() style
		void operator()(LPCSTR, ...) { }
		void operator()(LPCWSTR, ...) { }
		void operator()(DWORD_PTR, UINT, LPCSTR, ...) { }
		void operator()(DWORD_PTR, UINT, LPCWSTR, ...) { }

		typedef off type;
	};

} // namespace trace_fn_detail


// must be metafunction, because constructor is not inherited.
template<
	class HeaderT = boost::mpl::void_,
	class OnT = boost::mpl::true_,
	class SpaceCountT = boost::mpl::int_<2>
>
struct trace_fn
{
	typedef typename
	boost::mpl::eval_if< boost::mpl::and_<pstade::is_debug<>, OnT>,
		trace_fn_detail::on<HeaderT, SpaceCountT>,
		trace_fn_detail::off
	>::type type;
};


#undef PSTADE_TOMATO_TRACE_FN_DETAIL_ATL_TRACE_IMPL


} } // namespace pstade::tomato
