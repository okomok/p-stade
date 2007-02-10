#ifndef PSTADE_OVEN_AS_SINGLE_HPP
#define PSTADE_OVEN_AS_SINGLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The constant-iterator is the same as the mutable-iterator.
// Const-ness of this range must be independent from const-ness of the 'X'.


#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/constant.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./indirected.hpp"
#include "./iter_range.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace as_single_detail {


    template< class X >
    struct baby
    {
        typedef
            iter_range<X *> const
        result;

        result call(X& x)
        {
            return result(boost::addressof(x), boost::addressof(x) + 1);
        }
    };

    PSTADE_FUNCTION(normal, (baby<_>))


} // namespace as_single_detail


PSTADE_AUXILIARY0(as_single, (as_single_detail::op_normal))


namespace as_shared_single_detail {


    // As mentioned at "./shared.hpp", we must implement
    // something like 'auxiliary0' from scratch.


    struct op_as_shared_single
    {
        template< class FunCall >
        struct result;

        template< class Fun, class Pointer >
        struct result<Fun(Pointer)>
        {
            typedef
                boost::shared_ptr<
                    typename shared_pointee<Pointer>::type
                >
            sp_t;

            typedef
                std::vector<sp_t>
            rng_t;

            typedef
                typename boost::result_of<
                    op_make_indirected<>(
                        typename boost::result_of<
                            op_make_shared(rng_t *)
                        >::type
                    )
                >::type
            type;
        };

        template< class Pointer >
        typename result<void(Pointer)>::type
        operator()(Pointer p) const
        {
            typedef result<void(Pointer)> result_;
            typename result_::sp_t sp(to_shared_ptr(p));
            return
                make_indirected(
                    make_shared(
                        new typename result_::rng_t(boost::addressof(sp), boost::addressof(sp) + 1)
                    )
                );
        }
    };


    template< class Pointer > inline
    typename boost::result_of<op_as_shared_single(Pointer&)>::type
    operator|(Pointer p, op_as_shared_single const& fun)
    {
        return fun(p);
    }


} // namespace as_shared_single_detail


using as_shared_single_detail::op_as_shared_single;
PSTADE_CONSTANT(as_shared_single, (op_as_shared_single))


} } // namespace pstade::oven


#endif
