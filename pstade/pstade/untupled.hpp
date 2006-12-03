#ifndef PSTADE_UNTUPLED_HPP
#define PSTADE_UNTUPLED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/compose.hpp>
#include <pstade/tie.hpp>


namespace pstade {


    namespace untupled_detail {


        struct baby
        {
            template< class Myself, class Function >
            struct apply :
                boost::result_of<compose_fun(Function&, tie_fun&)>
            { };

            template< class Result, class Function >
            Result call(Function& fun)
            {
                return pstade::compose(fun, tie);
            }
        };


    } // namespace untupled_detail


    PSTADE_EGG_FUNCTION(untupled, untupled_detail::baby)


} // namespace pstade


#endif
