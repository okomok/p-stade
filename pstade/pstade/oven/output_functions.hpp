#ifndef PSTADE_OVEN_OUTPUT_FUNCTIONS_HPP
#define PSTADE_OVEN_OUTPUT_FUNCTIONS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Ideally, you should prefer Boost.Phoenix2 or Lambda.
// 'dummy_output_iterator' can be written with 'unused' and this.


#include <iosfwd> // basic_ostream/streambuf
#include <boost/utility/addressof.hpp>
#include "./range_value.hpp"


namespace pstade { namespace oven {


// push_back
//

template< class Sequence >
struct push_back_fun
{
    typedef void result_type;
    typedef typename range_value<Sequence>::type value_type;

    explicit push_back_fun(Sequence& seq) :
        m_pseq(boost::addressof(seq))
    { }

    void operator()(value_type const& val) const
    {
        m_pseq->push_back(val);
    }

private:
    Sequence *m_pseq; // must be a pointer for assignability.
};

template< class Sequence > inline
push_back_fun<Sequence> const
push_back(Sequence& seq)
{
    return push_back_fun<Sequence>(seq);
}


// push_front
//

template< class Sequence >
struct push_front_fun
{
    typedef void result_type;
    typedef typename range_value<Sequence>::type value_type;

    explicit push_front_fun(Sequence& seq) :
        m_pseq(boost::addressof(seq))
    { }

    void operator()(value_type const& val) const
    {
        m_pseq->push_front(val);
    }

private:
    Sequence *m_pseq; // must be a pointer for assignability.
};

template< class Sequence > inline
push_front_fun<Sequence> const
push_front(Sequence& seq)
{
    return push_front_fun<Sequence>(seq);
}


// operator<<
//

template< class OStream >
struct stream_output_fun
{
    typedef void result_type;

    explicit stream_output_fun(OStream& os) :
        m_pos(boost::addressof(os))
    { }

    template< class Value >
    void operator()(Value const& val) const
    {
        *m_pos << val;
    }

private:
    OStream *m_pos;
};

template< class OStream > inline
stream_output_fun<OStream> const
stream_output(OStream& os)
{
    return stream_output_fun<OStream>(os);
}


// sputc
//

template< class CharT, class Traits >
struct sputc_fun
{
    typedef void result_type;
    typedef std::basic_ostream<CharT, Traits>   ostream_type;
    typedef std::basic_streambuf<CharT, Traits> streambuf_type;

    explicit sputc_fun(ostream_type& os) :
        m_pb(os.rdbuf())
    { }

    explicit sputc_fun(streambuf_type *pb) :
        m_pb(pb)
    { }

    void operator()(CharT const& ch) const
    {
        m_pb->sputc(ch);
    }

private:
    streambuf_type *m_pb;
};

template< class CharT, class Traits > inline
sputc_fun<CharT, Traits> const
sputc(std::basic_ostream<CharT, Traits>& os)
{
    return sputc_fun<CharT, Traits>(os);
}

template< class CharT, class Traits > inline
sputc_fun<CharT, Traits> const
sputc(std::basic_streambuf<CharT, Traits> *pb)
{
    return sputc_fun<CharT, Traits>(pb);
}


} } // namespace pstade::oven


#endif
