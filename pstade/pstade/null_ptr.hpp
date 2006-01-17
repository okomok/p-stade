#pragma once

// Thanks to:
//   someone who uploaded to boost sandbox.
// Note:
//   'nullptr' is proposed to Standard C++.
//    http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/


#include <boost/config.hpp> // for BOOST_NO_MEMBER_TEMPLATES

namespace pstade {


#if !defined(BOOST_NO_MEMBER_TEMPLATES)

	namespace null_ptr_detail {

		struct null_ptr_type
		{
			// Workaround: to suppress warnings
			friend class pstade_null_ptr_dummy_class;

			template< class AnyT >
			operator AnyT* () const { return 0; }

			template< class AnyT, class MemT >
			operator MemT AnyT::* () const { return 0; }

		private:
			null_ptr_type();
			null_ptr_type(const null_ptr_type&);
			void operator=(const null_ptr_type&);
			void operator&() const;
		};

	} // namespace null_ptr_detail

	namespace {
		// Workaround: static is still required for broken stdafx.cpp
		static const null_ptr_detail::null_ptr_type& null_ptr = *(null_ptr_detail::null_ptr_type*)0;
	}

#else

	namespace {
		static const int null_ptr = 0;
	}

#endif // !defined(BOOST_NO_MEMBER_TEMPLATES)


} // namespace pstade
