#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lexical_cast.hpp>
#include <boost/utility/addressof.hpp>


namespace pstade {


template< class TargetT, class SourceT > inline
TargetT lexical_cast(SourceT const& src)
{
    return boost::lexical_cast<TargetT>(src);
}


namespace lexical_detail {


    template< class SourceT >
    struct temp
    {
        explicit temp(SourceT const& src) :
            m_psrc(boost::addressof(src))
        { }

        template< class TargetT >
        operator TargetT() const
        {
            return pstade::lexical_cast<TargetT>(*m_psrc);
        }

    private:
        SourceT const *m_psrc;
    };


} // namespace lexical_detail


template< class SourceT > inline
lexical_detail::temp<SourceT> const
lexical(SourceT const& src)
{
    return lexical_detail::temp<SourceT>(src);
}


} // namespace pstade


#endif
