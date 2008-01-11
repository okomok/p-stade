#ifndef PSTADE_OVEN_STREAM_WRITER_HPP
#define PSTADE_OVEN_STREAM_WRITER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright Takeshi Mouri 2006.
//  Use, modification, and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This name comes from (24.5.2/1).
// An object which is passed to 'typeof(stream_writer(s))::operator='
// must be OutputStreamable. If not, you can ensure it using 'converter'.


// References:
//
// [1] Takeshi Mouri, ostream_iterator, Hamigaki C++ Libraries, 2006
//     http://hamigaki.sourceforge.jp/doc/html/ostream_iterator.html


#include <iterator> // ostreambuf_iterator
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/function_output_iterator.hpp"


namespace pstade { namespace oven {


// stream_writer
//

namespace stream_writer_detail {

    template< class OStream >
    struct proc
    {
    private:
        typedef typename OStream::char_type char_t;

    public:
        typedef void result_type;

        template< class OutputStreamable >
        void operator()(OutputStreamable const& x) const
        {
            if (m_delimiter) {
                if (*m_beginning)
                    *m_beginning = false;
                else
                    *m_ps << m_delimiter;
            }

            *m_ps << x;
        }

        proc(OStream& s, char_t const *delimiter) :
            m_ps(boost::addressof(s)), m_delimiter(delimiter),
            m_beginning(new bool(true))
        { }

        typedef OStream& base_type;

        OStream& base() const
        {
            return *m_ps;
        }

    private:
        OStream *m_ps;
        char_t const *m_delimiter;
        boost::shared_ptr<bool> m_beginning;
    };

    template< class OStream >
    struct base
    {
        typedef
            detail::function_output_iterator< proc<OStream> >
        result_type;

        result_type operator()(OStream& s, typename OStream::char_type const *delimiter = 0) const
        {
            return result_type(proc<OStream>(s, delimiter));
        }
    };

} // namespace stream_writer_detail

typedef PSTADE_EGG_DEFER((stream_writer_detail::base<boost::mpl::_>)) T_stream_writer;
PSTADE_POD_CONSTANT((T_stream_writer), stream_writer) = PSTADE_EGG_DEFERRED();


// streambuf_writer
//

namespace streambuf_writer_detail {

     struct little
    {
        template< class Myself, class OStream >
        struct apply
        {
            typedef typename
                boost::remove_pointer<OStream>::type
            stream_t;
          
            typedef
                std::ostreambuf_iterator<
                    typename stream_t::char_type,
                    typename stream_t::traits_type
                >
            type;
        };

        template< class Result, class CharT, class Traits >
        Result call(std::basic_ostream<CharT, Traits>& s) const
        {
            return Result(s);
        }

        template< class Result, class CharT, class Traits >
        Result call(std::basic_streambuf<CharT, Traits> *p) const
        {
            return Result(p);
        }
    };

} // namespace streambuf_writer_detail

typedef egg::function<streambuf_writer_detail::little> T_streambuf_writer;
PSTADE_POD_CONSTANT((T_streambuf_writer), streambuf_writer) = {{}};


// std_stream_writer
//

namespace std_stream_writer_detail {

    template< class OStream >
    struct proc
    {
        OStream *m_ps;
        typename OStream::char_type const *m_delimiter;

        typedef void result_type;

        template< class OutputStreamable >
        void operator()(OutputStreamable const& x) const
        {
            *m_ps << x;

            if (m_delimiter)
                *m_ps << m_delimiter;
        }

        typedef OStream& base_type;

        OStream& base() const
        {
            return *m_ps;
        }
    };

    template< class OStream >
    struct base
    {
        typedef
            detail::function_output_iterator< proc<OStream> >
        result_type;

        result_type operator()(OStream& s, typename OStream::char_type const *delimiter = 0) const
        {
            proc<OStream> p = {boost::addressof(s), delimiter};
            return result_type(p);
        }
    };

} // namespace std_stream_writer_detail

typedef PSTADE_EGG_DEFER((std_stream_writer_detail::base<boost::mpl::_>)) T_std_stream_writer;
PSTADE_POD_CONSTANT((T_std_stream_writer), std_stream_writer) = PSTADE_EGG_DEFERRED();


} } // namespace pstade::oven


#endif
