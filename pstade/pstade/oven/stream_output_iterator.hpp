#ifndef PSTADE_OVEN_STREAM_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_STREAM_OUTPUT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A modern 'std::ostream_iterator'


#include <iosfwd> // basic_ostream
#include <iterator> // output_iterator_tag
#include <boost/utility/addressof.hpp>


namespace pstade { namespace oven {


template< class CharT, class Traits >
struct stream_output_iterator
{
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void pointer;
    typedef void difference_type;
    typedef std::basic_ostream<CharT, Traits> ostream_type;

    struct reference
    {
        explicit reference(ostream_type& os) :
            m_os(os)
        { }

        template< class Value >
        reference& operator=(const Value& val)
        {
            m_os << val;
            return *this;
        }

    private:
        ostream_type& m_os;
    };

    reference operator *() const { return reference(*m_pos); }
    stream_output_iterator& operator++() { return *this; }
    stream_output_iterator operator++(int) { return *this; }

    explicit stream_output_iterator(ostream_type& os) :
        m_pos(boost::addressof(os))
    { }

private:
    ostream_type *m_pos;
};


template< class CharT, class Traits > inline
stream_output_iterator<CharT, Traits> const
stream_outputter(std::basic_ostream<CharT, Traits>& os)
{
    return stream_output_iterator<CharT, Traits>(os);
}


} } // namespace pstade::oven


#endif
