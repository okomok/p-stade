#ifndef PSTADE_TYPED_STREAM_HPP
#define PSTADE_TYPED_STREAM_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>


namespace pstade {


namespace typed_stream_detail {


    template< class Value >
    struct iplaceholder
    {
        virtual ~iplaceholder() { }
        virtual void input(Value&) = 0;
    };

    template< class Value, class IStream >
    struct iholder :
        iplaceholder<Value>
    {
        explicit iholder(IStream& os) :
            m_held(os)
        { }

        virtual void input(Value& val)
        {
            m_held >> val;
        }

    private:
        IStream& m_held;
    };


    template< class Value >
    struct oplaceholder
    {
        virtual ~oplaceholder() { }
        virtual void output(Value const&) = 0;
    };

    template< class Value, class OStream >
    struct oholder :
        oplaceholder<Value>
    {
        explicit oholder(OStream& os) :
            m_held(os)
        { }

        virtual void output(Value const& val)
        {
            m_held << val;
        }

    private:
        OStream& m_held;
    };


} // namespace typed_stream_detail


template< class Value >
struct typed_istream :
    private boost::noncopyable
{
    template< class IStream >
    explicit typed_istream(IStream& is) :
        m_pis(new typed_stream_detail::iholder<Value, IStream>(is))
    { }
    
    typed_istream& operator>>(Value& val)
    {
        m_pis->input(val);
        return *this;
    }

private:
    boost::scoped_ptr< typed_stream_detail::iplaceholder<Value> > m_pis;
};


template< class Value >
struct typed_ostream :
    private boost::noncopyable
{
    template< class OStream >
    explicit typed_ostream(OStream& os) :
        m_pos(new typed_stream_detail::oholder<Value, OStream>(os))
    { }
    
    typed_ostream& operator<<(Value const& val)
    {
        m_pos->output(val);
        return *this;
    }

private:
    boost::scoped_ptr< typed_stream_detail::oplaceholder<Value> > m_pos;
};


template< class Value >
struct typed_iostream :
    private boost::noncopyable
{
    template< class IOStream >
    explicit typed_iostream(IOStream& ios) :
        m_pis(new typed_stream_detail::iholder<Value, IOStream>(ios)),
        m_pos(new typed_stream_detail::oholder<Value, IOStream>(ios))
    { }
    
    typed_iostream& operator>>(Value& val)
    {
        m_pis->input(val);
        return *this;
    }

    typed_iostream& operator<<(Value const& val)
    {
        m_pos->output(val);
        return *this;
    }

private:
    boost::scoped_ptr< typed_stream_detail::iplaceholder<Value> > m_pis;
    boost::scoped_ptr< typed_stream_detail::oplaceholder<Value> > m_pos;
};


} // namespace pstade


#endif
