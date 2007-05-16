#ifndef PSTADE_LOCALE_HPP
#define PSTADE_LOCALE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <locale>
#include <boost/iterator/zip_iterator.hpp> // detail::tuple_impl_specific
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/arg.hpp>


namespace pstade {


namespace locale_detail {


    struct stream_placeholder
    {
        virtual ~stream_placeholder() { }
        virtual std::locale getloc_() = 0;
        virtual void imbue_(const std::locale& ) = 0;
    };


    template< class Stream >
    struct stream_holder :
        stream_placeholder
    {
        explicit stream_holder(Stream& stm) :
            m_held(stm)
        { }

        virtual std::locale getloc_()
        { return m_held.getloc(); }

        virtual void imbue_(const std::locale& loc)
        { m_held.imbue(loc); }

    private:
        Stream& m_held;
    };


    struct global_stream
    {
        void imbue(std::locale& loc)
        {
            std::locale::global(loc);
        }

        std::locale getloc() const
        {
            return std::locale();
        }
    };


    struct scoped_locale_super
    {
        template< class Stream >
        explicit scoped_locale(Stream& stm, const std::locale& loc) :
            m_pstm( new locale_detail::stream_holder<Stream>(stm) ),
            m_saved( m_pstm->getloc_() )
        {
            m_pstm->imbue_(loc);
        }

        ~scoped_locale_super()
        {
            if (!m_pstm)
                std::locale::global(m_saved);
            else
                m_pstm->imbue_(m_saved);
        }

        operator std::locale()
        {
            if (!m_pstm)
                return std::locale();
            else
                return m_pstm->getloc_();
        }

    private:
        boost::scoped_ptr<locale_detail::stream_placeholder> m_pstm;
        std::locale m_saved;
    };


} // namespace locale_detail


struct scoped_locale :
    scoped_locale_super
    private boost::noncopyable
{
    explicit scoped_locale(const std::locale& loc) :
        scoped_locale_super(locale_detail::global_stream, loc)
    { }

    explicit scoped_locale(const char *name) :
        scoped_locale_super(locale_detail::global_stream, std::locale(name))
    { }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const std::locale& loc) :
        scoped_locale_super(stm, loc)
    { }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const char *name) :
        m_pstm( new locale_detail::stream_holder<Stream>(stm) ),
        m_saved( m_pstm->getloc_() )
    {
        m_pstm->imbue_(std::locale(name));
    }

    ~scoped_locale()
    {
        if (!m_pstm)
            std::locale::global(m_saved);
        else
            m_pstm->imbue_(m_saved);
    }

    operator std::locale()
    {
        if (!m_pstm)
            return std::locale();
        else
            return m_pstm->getloc_();
    }

private:
    boost::scoped_ptr<locale_detail::stream_placeholder> m_pstm;
    std::locale m_saved;
};


namespace locale_detail {


    struct imbue_fun
    {
        explicit imbue_fun(const std::locale& loc) :
            m_ploc(boost::addressof(loc))
        { }

        template< class Stream >
        void operator()(Stream& stm)
        {
            stm.imbue(*m_ploc);
        }

    private:
        const std::locale *m_ploc;
    };


} // namespace locale_detail


inline
void set_wstreams_locale(const std::locale& loc)
{
    using namespace std;
    namespace bdt = boost::detail::tuple_impl_specific;

    bdt::tuple_for_each(
        pstade::arg(boost::tie(wcin, wcout, wcerr, wclog)),
        locale_detail::imbue_fun(loc)
    );
}


inline
void set_wstreams_locale(const char *name)
{
    pstade::set_wstreams_locale(std::locale(name));
}


} // namespace pstade


#endif
