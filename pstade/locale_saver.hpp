#ifndef PSTADE_LOCALE_SAVER_HPP
#define PSTADE_LOCALE_SAVER_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the VC8 bug that changing the global locale
// breaks down wide-streams.
// Note that 'boost::basic_ios_locale_saver' has no support
// to save the global locale.


#include <locale>
#include <boost/scoped_ptr.hpp>
#include <pstade/constant.hpp>


namespace pstade {


namespace locale_saver_detail {


    struct iostream_placeholder
    {
        virtual ~iostream_placeholder() { }
        virtual std::locale getloc_() const = 0;
        virtual void imbue_(std::locale const&) = 0;
    };


    template< class IOStream >
    struct iostream_holder :
        iostream_placeholder
    {
        explicit iostream_holder(IOStream& ios) :
            m_held(ios)
        { }

        virtual std::locale getloc_() const
        {
            return m_held.getloc();
        }

        virtual void imbue_(std::locale const& loc)
        {
            m_held.imbue(loc);
        }

    private:
        IOStream& m_held;
    };


    struct global_t
    {
        void imbue(const std::locale& loc) const
        {
            std::locale::global(loc);
        }

        std::locale getloc() const
        {
            return std::locale();
        }
    };

    PSTADE_CONSTANT(global, (global_t))


    template< class = void >
    struct super_
    {
        typedef super_ type;

    protected:
        template< class IOStream >
        super_(IOStream& ios, std::locale const& loc) :
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
    private locale_saver_detail::super_<>::type
{
private:
    typedef locale_saver_detail::super_<>::type super_t;

public:
    explicit locale_saver(std::locale const& loc) :
        super_t(locale_saver_detail::global, loc)
    { }

    explicit locale_saver(char const *name) :
        super_t(locale_saver_detail::global, std::locale(name))
    { }

    template< class IOStream >
    explicit locale_saver(IOStream& ios, std::locale const& loc) :
        super_t(ios, loc)
    { }

    template< class IOStream >
    explicit locale_saver(IOStream& ios, char const *name) :
        super_t(ios, std::locale(name))
    { }

private:
    locale_saver(locale_saver const&);
    locale_saver& operator=(locale_saver const&);
};


} // namespace pstade


#endif
