#ifndef PSTADE_OVEN_FILE_RANGE_HPP
#define PSTADE_OVEN_FILE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/utility/base_from_member.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class CharT = char >
struct file_range :
    private boost::base_from_member< boost::spirit::file_iterator<CharT> >,
    boost::iterator_range< boost::spirit::file_iterator<CharT> >
{
private:
    typedef boost::spirit::file_iterator<CharT> iter_t;
    typedef boost::base_from_member<iter_t> iter_bt;
    typedef boost::iterator_range<iter_t> super_t;

public:
    explicit file_range(std::string path) :
        iter_bt(path),
        super_t(
            iter_bt::member,
            iter_bt::member ? iter_bt::member.make_end() : iter_bt::member
        )
    { }

    bool is_open() const
    { return iter_bt::member; }
};


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::file_range, 1)


#endif
