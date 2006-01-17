#pragma once

#if !defined(PSTADE_CFG_NO_STD_IOSTREAM)


#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/utility/base_from_member.hpp>

namespace pstade { namespace oven {


template< class CharT = char >
struct file_range :
	private boost::base_from_member< boost::spirit::file_iterator<CharT> >,
	boost::iterator_range< boost::spirit::file_iterator<CharT> >
{
private:
	typedef boost::spirit::file_iterator<CharT> iter_t;
	typedef boost::base_from_member<iter_t> initializer_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit file_range(const std::string& path) :
		initializer_t(path),
		super_t(
			initializer_t::member,
			initializer_t::member ? initializer_t::member.make_end() : initializer_t::member
		)
	{ }

	bool is_open() const
	{ return initializer_t::member; }
};


} } // namespace pstade::oven


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class CharT > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::file_range<CharT> *&, boost::foreach::tag)
{ return 0; }


#endif // !defined(PSTADE_CFG_NO_STD_IOSTREAM)
