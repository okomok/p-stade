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
#include <boost/scoped_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/arg.hpp>


namespace pstade {


struct scoped_global_locale :
    std::locale
{
private:
    typedef std::locale super_t;

public:
    explicit scoped_global_locale(const std::locale& loc) :
        super_t(std::locale::global(loc))
    { }

    explicit scoped_global_locale(const char *name) :
        super_t( std::locale::global(std::locale(name)) )
    { }

    ~scoped_global_locale()
    {
        std::locale::global(*this);
    }
};


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


    typedef boost::base_from_member< boost::scoped_ptr<stream_placeholder> >
    stream_init_t;


} // namespace locale_detail


struct scoped_locale :
    private locale_detail::stream_init_t,
    std::locale,
    private boost::noncopyable
{
private:
    typedef locale_detail::stream_init_t init_t;
    typedef std::locale super_t;

public:
    explicit scoped_locale(const std::locale& loc) :
        super_t(std::locale::global(loc))
    { }

    explicit scoped_locale(const char *name) :
        super_t(std::locale::global(std::locale(name)))
    { }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const std::locale& loc) :
        init_t( new locale_detail::stream_holder<Stream>(stm) ),
        super_t( init_t::member->getloc_() )
    {
        init_t::member->imbue_(loc);
    }

    template< class Stream >
    explicit scoped_locale(Stream& stm, const char *name) :
        init_t( new locale_detail::stream_holder<Stream>(stm) ),
        super_t( init_t::member->getloc_() )
    {
        init_t::member->imbue_(std::locale(name));
    }

    ~scoped_locale()
    {
        if (!init_t::member)
            std::locale::global(*this);
        else
            init_t::member->imbue_(*this);
    }
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
