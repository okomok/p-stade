#ifndef PSTADE_HAMBURGER_LINE_HPP
#define PSTADE_HAMBURGER_LINE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./rectangle.hpp"


namespace pstade { namespace hamburger {


struct line
{
    explicit line(LONG first, LONG last) :
        m_first(first), m_last(last)
    { }

    LONG begin() const
    { return m_first; }

    LONG end() const
    { return m_last; }

    line& operator+=(LONG d)
    {
        m_first += d;
        m_last += d;
        return *this;
    }

    line& operator-=(LONG d)
    {
        return operator+=(-d);
    }

 private:
    LONG m_first, m_last;
};


inline
rectangle make_rectangle(line horz, line vert)
{
    return hamburger::rectangle(horz.begin(), vert.begin(), horz.end(), vert.end());
}


inline
line make_horizontal(rectangle rc)
{
    return hamburger::line(rc.left, rc.right);
}


inline
line make_vertical(rectangle rc)
{
    return hamburger::line(rc.top, rc.bottom);
}


} } // namespace pstade::hamburger


#endif
