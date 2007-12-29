#ifndef PSTADE_TOMATO_REBAR_BANDS_HPP
#define PSTADE_TOMATO_REBAR_BANDS_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/pipable.hpp>
#include <pstade/gravy/window_ptr.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/oven/indexing.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./get_rebar_band_id.hpp"
#include "./rebar_band.hpp"
#include "./wtl/ctrls.hpp" // CReBarCtrl


namespace pstade { namespace tomato {


    namespace rebar_bands_detail {


        struct T_get
        {
            typedef rebar_band result_type;

            rebar_band operator()(int i) const
            {
                return rebar_band(*m_prebar, tomato::get_rebar_band_id(*m_prebar, i));
            }

            explicit T_get(gravy::window_ref rebar) :
                m_prebar(rebar)
            { }

        private:
            gravy::window_ptr m_prebar; // be a ptr for Assignable.
        };


    } // namespace rebar_bands_detail


    struct T_make_rebar_bands
    {
        typedef
            result_of<oven::T_indexing(int, UINT, rebar_bands_detail::T_get)>::type
        result_type;

        result_type operator()(gravy::window_ref rebar) const
        {
            return oven::indexing(0, WTL::CReBarCtrl(rebar).GetBandCount(), rebar_bands_detail::T_get(rebar));
        }
    };


    PSTADE_POD_CONSTANT((T_make_rebar_bands), make_rebar_bands) = {};
    PSTADE_POD_CONSTANT((egg::result_of_pipable<T_make_rebar_bands>::type), rebar_bands)
        = PSTADE_EGG_PIPABLE({});


} } // namespace pstade::tomato


#endif
