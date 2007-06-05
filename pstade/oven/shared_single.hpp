#ifndef PSTADE_OVEN_SHARED_SINGLE_HPP
#define PSTADE_OVEN_SHARED_SINGLE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/pointee.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable_by_value.hpp>
#include <pstade/constant.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./indirected.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace shared_single_detail {


    struct new_array1 :
        callable_by_value<new_array1>
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


} // namespace shared_single_detail


struct op_shared_single :
    callable_by_value<op_shared_single>
{
    template< class Myself, class Ptr >
    struct apply :
        boost::result_of<
            op_make_indirected<>(
                typename boost::result_of<
                    op_shared(
                        typename boost::result_of<
                            shared_single_detail::new_array1(
                                typename boost::result_of<
                                    op_to_shared_ptr(Ptr&)
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
                    shared_single_detail::new_array1()(
                        to_shared_ptr(p)
                    )
                )
            );
    }
};


PSTADE_CONSTANT(shared_single, (op_shared_single))


} } // namespace pstade::oven


#endif
