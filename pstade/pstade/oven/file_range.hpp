#ifndef PSTADE_OVEN_FILE_RANGE_HPP
#define PSTADE_OVEN_FILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/file_iterator.hpp>
#include <pstade/implicitly_defined.hpp>
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"


namespace pstade { namespace oven {


template< class CharT >
struct file_range;


namespace file_range_detail {


    template< class CharT >
    struct super_
    {
        typedef
            iter_range<boost::spirit::file_iterator<CharT>,
                lightweight_copyable< file_range<CharT> >
            >
        type;
    };


    template< class Super, class CharT >
    Super make(std::string path)
    {
        boost::spirit::file_iterator<CharT> it(path);
        if (!it)
            return Super(it, it);

        return Super(it, it.make_end());
    }


} // namespace file_range_detail


template< class CharT = char >
struct file_range :
    file_range_detail::super_<CharT>::type
{
    typedef CharT char_type;

private:
    typedef typename file_range_detail::super_<CharT>::type super_t;

public:
    explicit file_range(std::string path) :
        super_t(file_range_detail::make<super_t, CharT>(path))
    { }

    bool is_open() const
    {
        return this->begin();
    }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(file_range, super_t)
};


} } // namespace pstade::oven


#endif
