#ifndef PSTADE_OVEN_IO_HPP
#define PSTADE_OVEN_IO_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/tuple/tuple_io.hpp>
// <boost/fusion/sequence/io.hpp>


#include <locale> // isspace
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/function.hpp>
#include <pstade/nonassignable.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace io_detail {


    enum mn_t
    {
        mn_open, mn_close, mn_delimiter, mn_SIZE
    };


    inline
    int mn_id(int mn)
    {
        static int const index[mn_SIZE] = {
            std::ios::xalloc(), std::ios::xalloc(), std::ios::xalloc()
        };

        return index[mn];
    }


    template< class Stream, class CharT >
    void set_mn_char(Stream& s, mn_t const& mn, CharT const& ch)
    {
        s.iword(mn_id(mn)) = static_cast<long>(ch);
    }

    template< class Stream >
    typename Stream::char_type get_mn_char(Stream& s, mn_t const& mn)
    {
        typedef typename Stream::char_type char_t;
        char_t ch = static_cast<char_t>( s.iword(mn_id(mn)) );

        if (ch)
            return ch;

        // defaults
        switch (mn) {
            case mn_open:
                ch = s.widen('{');
                break;
            case mn_close: 
                ch = s.widen('}');
                break;
            case mn_delimiter:
                ch = s.widen(',');
                break;
            default:
                BOOST_ASSERT(false);
                break;
        }

        return ch;
    }

    template< class IStream >
    void eat_mn_char(IStream& is, mn_t const& mn)
    {
        typename IStream::char_type const ch = (get_mn_char)(is, mn);

        if (std::isspace(ch, is.getloc()))
            return;

        if (is.get() != ch) {
            is.unget();
            is.setstate(std::ios::failbit);
        }
    }


    template< class IStream, class Iterator >
    void in(IStream& is, Iterator first, Iterator const& last)
    {
        bool is_beginning = true;
        for ( ; first != last; ++first) {
            if (!is_beginning)
                (eat_mn_char)(is, mn_delimiter);
            else
                is_beginning = false;

            if (!is.good())
                break;

            is >>
                boost::implicit_cast<
                    typename boost::iterator_value<Iterator>::type&
                >(*first);
        }
    }


    template< class OStream, class Iterator >
    void out(OStream& os, Iterator first, Iterator const& last)
    {
        typename OStream::char_type const delim = (get_mn_char)(os, mn_delimiter);

        bool is_beginning = true;
        for ( ; first != last; ++first) {
            if (!is_beginning)
                os << delim;
            else
                is_beginning = false;

            os <<
                boost::implicit_cast<
                    typename boost::iterator_value<Iterator>::type const&
                >(*first);
        }
    }


    template< class CharT >    
    struct manipulator :
        private nonassignable
    {
        manipulator(mn_t const& mn, CharT const& ch) :
            m_mn(mn), m_ch(ch)
        { }

        mn_t const m_mn;
        CharT const m_ch;
    };

    template< class CharT, class Traits > inline
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, manipulator<CharT> const& m) 
    {
        io_detail::set_mn_char(is, m.m_mn, m.m_ch);
        return is;
    }

    template< class CharT, class Traits > inline
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, manipulator<CharT> const& m)
    {
        io_detail::set_mn_char(os, m.m_mn, m.m_ch);
        return os;
    }


#define PSTADE_baby_manipulator(Name) \
    template< class CharT > \
    struct BOOST_PP_CAT(baby_, Name) \
    { \
        typedef \
            manipulator< \
                typename boost::remove_cv<CharT>::type \
            > const \
        result; \
        \
        result call(CharT& ch) \
        { \
            return result(BOOST_PP_CAT(mn_, Name), ch); \
        } \
    }; \
/**/

    PSTADE_baby_manipulator(open)
    PSTADE_baby_manipulator(close)
    PSTADE_baby_manipulator(delimiter)

#undef  PSTADE_baby_manipulator


} // namespace io_detail


template< class Iterator, class CharT, class Traits >
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, iter_range<Iterator> const& rng)
{
    if (!is.good())
        return is;

    io_detail::eat_mn_char(is, io_detail::mn_open);
    io_detail::in(is, boost::begin(rng), boost::end(rng));
    io_detail::eat_mn_char(is, io_detail::mn_close);

    return is;
}


template< class Iterator, class CharT, class Traits >
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, iter_range<Iterator> const& rng)
{
    CharT const l = io_detail::get_mn_char(os, io_detail::mn_open);
    CharT const r = io_detail::get_mn_char(os, io_detail::mn_close);

    os << l;   
    io_detail::out(os, boost::begin(rng), boost::end(rng));
    os << r;

    return os;
}


PSTADE_FUNCTION(range_open,      (io_detail::baby_open<_>))
PSTADE_FUNCTION(range_close,     (io_detail::baby_close<_>))
PSTADE_FUNCTION(range_delimiter, (io_detail::baby_delimiter<_>))


} } // namespace pstade::oven


#endif
