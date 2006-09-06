#ifndef PSTADE_USTRING_HPP
#define PSTADE_USTRING_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <vector>
#include <boost/cstdint.hpp> // uint8_t, uint32_t
#include <boost/mpl/bool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/basic_ostream_fwd.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/null_terminate_range.hpp>


namespace pstade {


typedef boost::uint32_t
ucs4_t;


typedef boost::uint8_t
utf8cp_t;


namespace ustring_detail {


    template< class = void >
    struct super_
    {
        typedef std::vector<ucs4_t> type;
    };


} // namespace ustring_detail


struct ustring :
    ustring_detail::super_<>::type
{
private:
    typedef ustring_detail::super_<>::type super_t;

public:
    explicit ustring()
    { }

    explicit ustring(super_t::size_type n) :
        super_t(n)
    { }

    explicit ustring(super_t::size_type n, super_t::value_type const& t) :
        super_t(n, t)
    { }

    template< class Iterator >
    explicit ustring(Iterator f, Iterator l) :
        super_t(f, l)
    { }

    template< class Range >
    explicit ustring(Range const& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    // The copy-initialization prefers copy constructor and converts argument to ustring.
    // But operator= doesn't, so be strict.
    template< class Range > 
    typename boost::enable_if<apple::is_boost_range<Range>,
    ustring&>::type operator=(Range const& rng)
    {
        assign(boost::begin(rng), boost::end(rng));
        return *this;
    }

    // implicit conversions
    //
    ustring(char const *psz) :
        super_t(psz, oven::null_terminate_range_detail::end(psz))
    { }

    ustring(wchar_t const *psz) :
        super_t(psz, oven::null_terminate_range_detail::end(psz))
    { }
};


// truncated!
//
template<class CharT, class Traits >
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, ustring str)
{
    os << oven::copy_range< std::basic_string<CharT, Traits> >(str);
    return os;
}

template<class CharT, class Traits >
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& os, ustring& str)
{
    std::basic_string<CharT, Traits> tmp;
    os >> tmp;
    str = pstade::ustring(tmp);
    return os;
}


} // namespace pstade


namespace pstade { namespace apple {


template< >
struct is_sequence_impl<pstade::ustring> :
    boost::mpl::true_
{ };


} } // namespace pstade::apple


#endif
