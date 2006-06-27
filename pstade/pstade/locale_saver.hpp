#ifndef PSTADE_LOCALE_SAVER_HPP
#define PSTADE_LOCALE_SAVER_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround for:
//
// Changing the global locale breaks down VC8 wide-streams.


// See:
//
// boost::basic_ios_locale_saver


#include <locale>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/instance.hpp>


namespace pstade {


namespace locale_saver_detail {


    struct iostream_placeholder
    {
        virtual ~iostream_placeholder() { }
        virtual std::locale getloc_() const = 0;
        virtual void imbue_(const std::locale& ) = 0;
    };


    template< class IOStream >
    struct iostream_holder :
        iostream_placeholder
    {
        explicit iostream_holder(IOStream& ios) :
            m_held(ios)
        { }

        virtual std::locale getloc_() const
        { return m_held.getloc(); }

        virtual void imbue_(const std::locale& loc)
        { m_held.imbue(loc); }

    private:
        IOStream& m_held;
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

        template< class IOStream >
        super_(IOStream& ios, const std::locale& loc) :
            m_pios(new iostream_holder<IOStream>(ios)),
            m_saved(m_pios->getloc_())
        {
            m_pios->imbue_(loc);
        }

        ~super_()
        {
            m_pios->imbue_(m_saved);
        }

    private:
        boost::scoped_ptr<iostream_placeholder> m_pios;
        std::locale m_saved;
    };


} // namespace locale_saver_detail


struct locale_saver :
    locale_saver_detail::super_<>::type,
    private boost::noncopyable
{
private:
    typedef locale_saver_detail::super_<>::type super_t;

public:
    explicit locale_saver(const std::locale& loc) :
        super_t(locale_saver_detail::global, loc)
    { }

    explicit locale_saver(const char *name) :
        super_t(locale_saver_detail::global, std::locale(name))
    { }

    template< class IOStream >
    explicit locale_saver(IOStream& ios, const std::locale& loc) :
        super_t(ios, loc)
    { }

    template< class IOStream >
    explicit locale_saver(IOStream& ios, const char *name) :
        super_t(ios, std::locale(name))
    { }
};


} // namespace pstade


#endif
