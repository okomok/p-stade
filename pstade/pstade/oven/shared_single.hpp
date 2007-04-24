#ifndef PSTADE_OVEN_SHARED_SINGLE_HPP
#define PSTADE_OVEN_SHARED_SINGLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/pointee.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./indirected.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace shared_single_detail_ {


    struct new_array1 :
        callable<new_array1>
    {
        template< class Myself, class Ptr >
        struct apply
        {
            typedef
                boost::array<typename pass_by_value<Ptr>::type, 1> *
            type;
        };

        template< class Result, class Ptr >
        Result call(Ptr& p) const
        {
            typedef typename boost::pointee<Result>::type array_t;
            array_t arr = { { p } };
            return new array_t(arr);
        }
    };


    // As mentioned at "./shared.hpp", we must implement
    // something like 'auxiliary0' from scratch.

    struct op :
        provide_sig
    {
        template< class Ptr >
        struct result_aux :
            boost::result_of<
                op_make_indirected<>(
                    typename boost::result_of<
                        op_make_shared(
                            typename boost::result_of<
                                new_array1(
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

        template< class Ptr >
        typename result_aux<Ptr>::type
        operator()(Ptr p) const
        {
            return
                make_indirected(
                    make_shared(
                        new_array1()(
                            to_shared_ptr(p)
                        )
                    )
                );
        }

        template< class FunCall >
        struct result;

        template< class Fun, class Ptr >
        struct result<Fun(Ptr)> :
            result_aux<typename pass_by_value<Ptr>::type>
        { };
    };


    template< class Ptr > inline
    typename boost::result_of<op(Ptr&)>::type
    operator|(Ptr p, op fun)
    {
        return fun(p);
    }


} // namespace shared_single_detail_


typedef shared_single_detail_::op op_shared_single;
PSTADE_CONSTANT(shared_single, (op_shared_single))


} } // namespace pstade::oven


#endif
