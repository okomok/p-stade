//  istream_line_iterator.hpp: a wrapper iterator for getline()

//  Copyright Takeshi Mouri 2006.
//  Use, modification, and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://hamigaki.sourceforge.jp/libs/iterator for library home page.

#ifndef HAMIGAKI_ITERATOR_ISTREAM_LINE_ITERATOR_HPP
#define HAMIGAKI_ITERATOR_ISTREAM_LINE_ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <iosfwd>
#include <string>

namespace hamigaki
{

template<
    class CharT,
    class Traits=std::char_traits<CharT>,
    class Allocator=std::allocator<CharT>
>
class istream_line_iterator
    : public boost::iterator_facade<
        istream_line_iterator<CharT,Traits,Allocator>,
        const std::basic_string<CharT,Traits,Allocator>,
        boost::single_pass_traversal_tag
    >
{
    friend class boost::iterator_core_access;

public:
    typedef CharT char_type;
    typedef Traits traits_type;
    typedef Allocator allocator_type;
    typedef std::basic_istream<CharT,Traits> istream_type;
    typedef std::basic_string<CharT,Traits,Allocator> string_type;

    istream_line_iterator() : in_ptr_(0)
    {
    }

    explicit istream_line_iterator(istream_type& is)
        : in_ptr_(&is), delim_(is.widen('\n'))
    {
        increment();
    }

    istream_line_iterator(istream_type& is, CharT delim)
        : in_ptr_(&is), delim_(delim)
    {
        increment();
    }

private:
    istream_type* in_ptr_;
    CharT delim_;
    string_type line_;

    const string_type& dereference() const
    {
        return line_;
    }

    void increment()
    {
        if (!std::getline(*in_ptr_, line_, delim_))
            in_ptr_ = 0;
    }

    bool equal(const istream_line_iterator& rhs) const
    {
        return in_ptr_ == rhs.in_ptr_;
    }
};

} // namespace hamigaki

#endif // HAMIGAKI_ITERATOR_ISTREAM_LINE_ITERATOR_HPP
