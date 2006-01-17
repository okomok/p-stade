#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>
#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size.hpp>
#include <boost/range/size_type.hpp>
#include <pstade/null_ptr.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


// primary template
template< class StringT >
struct scoped_c_str_buffer
{
	typedef TCHAR *iterator;
	typedef TCHAR const *const_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef int size_type;
	typedef TCHAR value_type;

	iterator begin() { return m_first; }
	iterator end() { return m_first + m_size; }
	const_iterator begin() const { return m_first; }
	const_iterator end() const { return m_first + m_size; }
	int size() const { return m_size; }
	bool empty() const { return false; }

	scoped_c_str_buffer(StringT& str) : m_string(str)
	{
		construct_aux(boost::size(m_string));
	}

	// len doesn't contain trailling '\0'
	scoped_c_str_buffer(StringT& str, int len) : m_string(str)
	{
		ATLASSERT(len >= 0);

		construct_aux(len);
	}

	~scoped_c_str_buffer()
	{
		ATLASSERT(is_valid(m_first) && "pstade::tomato::~scoped_c_str_buffer - range must be null-terminated.");

		m_string.ReleaseBuffer(); 
	}

private:
	StringT& m_string;
	iterator m_first;
	int m_size;

	void construct_aux(int len)
	{
		ATLASSERT(len >= 0);

		m_first = m_string.GetBufferSetLength(len);
		tomato::verify(m_first != pstade::null_ptr, E_OUTOFMEMORY);
		m_size = len + 1; // contains null
		m_first[len] = value_type('\0'); // null-terminated
	}
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


// std::vector specialization
template< class CharT, class AllocT >
struct scoped_c_str_buffer< std::vector<CharT, AllocT> >
{
private:
	typedef std::vector<CharT, AllocT> vector_t;

public:
	typedef CharT *iterator;
	typedef CharT const *const_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef typename boost::range_size<vector_t>::type size_type;
	typedef CharT value_type;

	iterator begin() { return begin_aux(); }
	iterator end() { return end_aux(); }
	const_iterator begin() const { return begin_aux(); }
	const_iterator end() const { return end_aux(); }
	size_type size() const { return boost::size(m_vec); }
	bool empty() const { return false; }

	scoped_c_str_buffer(vector_t& vec) : m_vec(vec)
	{
		construct_aux(boost::size(vec));
	}

	scoped_c_str_buffer(vector_t& vec, size_type len) : m_vec(vec)
	{
		ATLASSERT(len >= 0);

		construct_aux(len);
	}

	~scoped_c_str_buffer()
	{
		typedef typename boost::range_const_iterator<vector_t>::type vec_iter_t;
		vec_iter_t first = boost::const_begin(m_vec);
		vec_iter_t it = std::find(first, boost::const_end(m_vec), value_type('\0'));

		ATLASSERT(it != boost::const_end(m_vec) && "pstade::tomato::~scoped_c_str_buffer - range must be null-terminated.");
		m_vec.resize(std::distance(first, it));
	}

private:
	vector_t& m_vec;
	iterator begin_aux() { return boost::empty(m_vec) ? pstade::null_ptr : &m_vec[0]; }
	iterator end_aux() { return boost::empty(m_vec) ? pstade::null_ptr : &m_vec[0] + boost::size(m_vec); }

	void construct_aux(size_type len)
	{
		ATLASSERT(len >= 0);

		m_vec.resize(len + 1);
		m_vec[len] = value_type('\0');
	}
};


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::tomato
