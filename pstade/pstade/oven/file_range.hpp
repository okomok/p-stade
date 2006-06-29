#ifndef PSTADE_OVEN_FILE_RANGE_HPP
#define PSTADE_OVEN_FILE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace file_range_detail {


    template< class Value >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::file_iterator<Value>
        > type;
    };


    template< class Value >
    typename super_<Value>::type make_super(std::string path)
    {
        boost::spirit::file_iterator<Value> it(path);
        if (!it)
            return boost::make_iterator_range(it, it);

        return boost::make_iterator_range(it, it.make_end());
    }


} // namespace file_range_detail


template< class Value = char >
struct file_range :
    file_range_detail::super_<Value>::type
{
private:
    typedef typename file_range_detail::super_<Value>::type super_t;

public:
    explicit file_range(std::string path) :
        super_t(file_range_detail::make_super<Value>(path))
    { }

    bool is_open() const
    { return boost::begin(*this); }
};


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::file_range, 1)


#endif
