#pragma once

#include "../cast/boolean_cast.hpp"

namespace pstade { namespace tomato {


namespace enum_child_windows_detail {

	template< class Functor >
	struct data
	{
		data(Functor f) : fun(f) { }
		Functor fun;
	};

	// Workaround: BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
	//    BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE cannot be used to keep the same signature.
	template< class DataT >
	struct proc_holder
	{
		static BOOL CALLBACK proc(HWND hWnd, LPARAM lParam)
		{
			DataT *p_data = reinterpret_cast<DataT *>(lParam);

			return tomato::boolean_cast<BOOL>(p_data->fun(hWnd));
		}
	};

} // namespace enum_child_windows_detail


template< class Functor > inline
Functor enum_child_windows(HWND hWndParent, Functor fun)
{
	typedef enum_child_windows_detail::data<Functor> data_t;
	data_t data(fun);

	// Note:
	//   if no child, EnumChildWindows "fails"
	//   and the GetLastError value is undocumented.
	//   So there is no way to verify.
	::EnumChildWindows(
		hWndParent,
		&enum_child_windows_detail::proc_holder<data_t>::proc,
		reinterpret_cast<LPARAM>(&data)
	);

	return data.fun;
}


} } // namespace pstade::tomato
