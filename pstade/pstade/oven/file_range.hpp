#ifndef PSTADE_OVEN_FILE_RANGE_HPP
#define PSTADE_OVEN_FILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace file_range_detail {


    template< class CharT >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::file_iterator<CharT>
        > type;
    };


    template< class Super, class CharT >
    Super make(std::string const& path)
    {
        boost::spirit::file_iterator<CharT> it(path);
        if (!it)
            return Super(it, it);

        return Super(it, it.make_end());
    }


} // namespace file_range_detail


template< class CharT = char >
struct file_range :
    file_range_detail::super_<CharT>::type,
    private as_lightweight_proxy< file_range<CharT> >
{
    typedef CharT char_type;

private:
    typedef typename file_range_detail::super_<CharT>::type super_t;

public:
    explicit file_range(std::string const& path) :
        super_t(file_range_detail::make<super_t, CharT>(path))
    { }

    bool is_open() const
    {
        return this->begin();
    }
};


} } // namespace pstade::oven


#endif
