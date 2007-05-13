#ifndef PSTADE_PROPERTY_HPP
#define PSTADE_PROPERTY_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


template< class T, class SetFtor, class GetFtor >
struct property
{
private:
    typedef property self_t;

public:
    explicit property(SetFtor sfun, GetFtor gfun) :
        m_sfun(sfun), m_gfun(gfun)
    { }

    self_t& operator=(const T& v)
    { m_sfun(v); }

    operator T()
    { return m_gfun(); }

private:
    SetFtor m_sfun; GetFtor m_gfun;
};


} // namespace pstade


#endif
