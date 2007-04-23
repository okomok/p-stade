#ifndef PSTADE_OVEN_WRITER_HPP
#define PSTADE_OVEN_WRITER_HPP


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
// An object which is passed to 'typeof(writer(s))::operator='
// must be OutputStreamable. If not, you can ensure it using 'transformed'.


// References:
//
// [1] Takeshi Mouri, ostream_iterator, Hamigaki C++ Libraries, 2006
//     http://hamigaki.sourceforge.jp/doc/html/ostream_iterator.html


#include <boost/shared_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include "./passer.hpp"


namespace pstade { namespace oven {


namespace writer_detail {


    template< class OStream >
    struct write_onto
    {
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

        typedef OStream ostream_type;
        typedef typename OStream::char_type char_type;
        typedef typename OStream::traits_type traits_type;

        write_onto(OStream& s, char_type const *delimiter) :
            m_ps(boost::addressof(s)), m_delimiter(delimiter),
            m_beginning(new bool(true))
        { }

        OStream& ostream() const
        {
            return *m_ps;
        }

        // as "adaptor"; 'adapted_to' kicks in!
        OStream& base() const
        {
            return *m_ps;
        }

    private:
        OStream *m_ps; // be a pointer for Assignable.
        char_type const *m_delimiter;
        boost::shared_ptr<bool> m_beginning;
    };


    template< class OStream >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_passer(write_onto<OStream>)
            >::type
        result_type;

        result_type operator()(OStream& s, typename OStream::char_type const *delimiter = 0) const
        {
            return passer(write_onto<OStream>(s, delimiter));
        }
    };


} // namespace writer_detail


PSTADE_FUNCTION(writer, (writer_detail::baby<_>))


} } // namespace pstade::oven


#endif
