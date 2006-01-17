#pragma once

// Model of:
//   Readable and Single Pass (Input) Range of WIN32_FIND_DATA
// Port of:
//   boost::directory_iterator to non-shared_ptr version

#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "./find_file_iterator.hpp"

namespace pstade { namespace tomato {


namespace find_file_range_detail {

	// See: Boost.BaseFromMember
	struct initializer
	{
	protected:
		HANDLE m_hFind;
		WIN32_FIND_DATA m_data;

		explicit initializer(LPCTSTR pszName)
		{
			ATLASSERT(tomato::is_valid(pszName));

			m_hFind = ::FindFirstFile(pszName, &m_data);
		}

		~initializer()
		{
			if (m_hFind != INVALID_HANDLE_VALUE)
				ATLVERIFY(::FindClose(m_hFind)); // cannot throw
		}
	};

} // namespace find_file_range_detail


struct find_file_range  :
	private boost::noncopyable,
	private find_file_range_detail::initializer,
	boost::iterator_range<find_file_iterator>
{
private:
	typedef boost::iterator_range<find_file_iterator> super_t;

public:
	explicit find_file_range(LPCTSTR pszName) :
		find_file_range_detail::initializer(pszName),
		super_t(
			find_file_iterator(m_hFind, m_data),
			find_file_iterator()
		)
	{ }
};


} } // namespace pstade::tomato
