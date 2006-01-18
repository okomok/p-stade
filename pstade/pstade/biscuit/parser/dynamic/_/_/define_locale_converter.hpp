#pragma once


#if !defined(PSTADE_CFG_NO_STD_LOCALE)

	#include <locale>
	#include <functional> // for std::unary_function

	#define PSTADE_BISCUIT_DEFINE_LOCALE_CONVERTER(name, fun) \
		namespace pstade { namespace biscuit { \
			\
			template< class CharT > \
			struct name : \
				std::unary_function<CharT, CharT> \
			{ \
				CharT operator()(CharT ch) const \
				{ \
					return fun(ch, std::locale()); \
				} \
			}; \
			\
		} } \
	/**/

#else

	#define PSTADE_BISCUIT_DEFINE_LOCALE_CONVERTER(name, fun) \
	/**/

#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)
