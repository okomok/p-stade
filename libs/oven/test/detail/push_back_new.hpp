#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_PUSH_BACK_NEW_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_PUSH_BACK_NEW_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prefix.hpp>


namespace pstade { namespace oven { namespace test {


template< class X, class PtrContainer >
struct push_back_new_result
{
    typedef void result_type;

    template< class Value >
    void operator()(Value const& v) const
    {
        m_pc->push_back(new X(v));
    }

    explicit push_back_new_result(PtrContainer& pc) :
        m_pc(&pc)
    { }

private:
    PtrContainer *m_pc;
};


template< class X, class PtrContainer >
push_back_new_result<X, PtrContainer>
push_back_new(PtrContainer& pc)
{
    return push_back_new_result<X, PtrContainer>(pc);
}


} } } // namespace pstade::oven::test


#endif
