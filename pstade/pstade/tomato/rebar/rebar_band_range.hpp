#ifndef PSTADE_TOMATO_REBAR_REBAR_BAND_RANGE_HPP
#define PSTADE_TOMATO_REBAR_REBAR_BAND_RANGE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/oven/index_range.hpp>
#include "../window/window_ptr.hpp"
#include "../window/window_ref.hpp"
#include "./get_rebar_band_id.hpp"
#include "./rebar_band.hpp"


namespace pstade { namespace tomato {


namespace rebar_band_range_detail {


    struct get_fun
    {
        typedef rebar_band result_type;

        rebar_band operator()(int i) const
        {
            return rebar_band(*m_prebar, tomato::get_rebar_band_id(*m_prebar, i));
        }

        explicit get_fun(window_ref rebar) :
            m_prebar(rebar)
        { }

    private:
        window_ptr m_prebar; // be a ptr for Assignable.
    };


    template< class = void >
    struct super_
    {
        typedef oven::index_range<int, get_fun> type;
    };


} // namespace rebar_band_range_detail


struct rebar_band_range :
    rebar_band_range_detail::super_<>::type
{
private:
    typedef rebar_band_range_detail::super_<>::type super_t;

public:
    explicit rebar_band_range(window_ref rebar) :
        super_t(
            0, WTL::CReBarCtrl(rebar).GetBandCount(),
            rebar_band_range_detail::get_fun(rebar)
        )
    { }
};


} } // namespace pstade::tomato


#endif
