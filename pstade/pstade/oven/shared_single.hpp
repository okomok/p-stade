#ifndef PSTADE_OVEN_SHARED_SINGLE_HPP
#define PSTADE_OVEN_SHARED_SINGLE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/pointee.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/to_shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./indirected.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace shared_single_detail {


    struct baby_new_array1
    {
        template< class Myself, class Ptr >
        struct apply
        {
            typedef
                boost::array<Ptr, 1> *
            type;
        };

        template< class Result, class Ptr >
        Result call(Ptr p) const
        {
            typedef typename boost::pointee<Result>::type array_t;
            array_t arr = { { p } };
            return new array_t(arr);
        }
    };

    typedef egg::function<baby_new_array1, egg::by_value> new_array1;


    struct baby
    {
        template< class Myself, class Ptr >
        struct apply :
            result_of<
                op_make_indirected(
                    typename result_of<
                        op_shared(
                            typename result_of<
                                new_array1(
                                    typename result_of<
                                        egg::op_to_shared_ptr(Ptr&)
                                    >::type
                                )
                            >::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Ptr >
        Result call(Ptr p) const
        {
            return
                make_indirected(
                    shared(
                        new_array1()(
                            egg::to_shared_ptr(p)
                        )
                    )
                );
        }
    };


} // namespace shared_single_detail


typedef egg::function<shared_single_detail::baby, egg::by_value> op_shared_single;
PSTADE_POD_CONSTANT((op_shared_single), shared_single) = {{}};


} } // namespace pstade::oven


#endif
