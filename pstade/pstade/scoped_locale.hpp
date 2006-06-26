#ifndef PSTADE_SCOPED_LOCALE_HPP
#define PSTADE_SCOPED_LOCALE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/instance.hpp>


namespace pstade {


namespace scoped_locale_detail {


    struct stream_placeholder
    {
        virtual ~stream_placeholder() { }
        virtual std::locale getloc_() const = 0;
        virtual void imbue_(const std::locale& ) = 0;
    };


    template< class Stream >
    struct stream_holder :
        stream_placeholder
    {
        explicit stream_holder(Stream& stm) :
            m_held(stm)
        { }

        virtual std::locale getloc_() const
        { return m_held.getloc(); }

        virtual void imbue_(const std::locale& loc)
        { m_held.imbue(loc); }

    private:
        Stream& m_held;
    };


    struct global_t
    {
        void imbue(const std::locale& loc)
        {
            std::locale::global(loc);
        }

        std::locale getloc() const
        {
            return std::locale();
        }
    };

    PSTADE_INSTANCE(global_t, global, value)


    template< class = void >
    struct super_
    {
        typedef super_ type;

        template< class Stream >
        explicit super_(Stream& stm, const std::locale& loc) :
            m_pstm( new stream_holder<Stream>(stm) ),
            m_saved( m_pstm->getloc_() )
        {
            m_pstm->imbue_(loc);
        }

        ~super_()
        {
            m_pstm->imbue_(m_saved);
        }

        std::locale getloc() const
        {
            return m_pstm->getloc_();
        }

        operator std::locale() const
        {
            return getloc();
        }

    private:
        boost::scoped_ptr<stream_placeholder> m_pstm;
        std::locale m_saved;
    };


} // namespace scoped_locale_detail


struct scoped_locale :
    scoped_locale_detail::super_<>::type,
    private boost::noncopyable
{
private:
    typedef scoped_locale_detail::super_<>::type super_t;

public:
    explicit scoped_locale(const std::locale& loc) :
        super_t(scoped_locale_detail::global, loc)
    { }

    explicit scoped_locale(const char *name) :
        super_t(scoped_locale_detail::global, std::locale(name))
    { }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const std::locale& loc) :
        super_t(stm, loc)
    { }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const char *name) :
        super_t(stm, std::locale(name))
    { }
};


} // namespace pstade


#endif
