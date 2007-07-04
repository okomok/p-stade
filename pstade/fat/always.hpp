#ifndef PSTADE_FAT_ALWAYS_HPP
#define PSTADE_FAT_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/object.hpp>


namespace pstade { namespace fat {


    namespace always_detail {


        template<class X>
        struct result_
        {
            X *m_px;

            typedef X& result_type;

            X& operator()() const
            {
                return *m_px;
            }
        };


        struct baby
        {
            template<class Myself, class X>
            struct apply
            {
                typedef result_<X> type;
            };

            template<class Result, class X>
            Result call(X& x) const
            {
                Result r = { boost::addressof(x) };
                return r;
            }
        };


    } // namespace always_detail


    typedef egg::function<always_detail::baby> op_always;
    PSTADE_EGG_OBJECT((op_always), always) = { {} };


} } // namespace pstade::fat


#endif
