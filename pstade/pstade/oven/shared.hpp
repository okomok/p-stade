#ifndef PSTADE_OVEN_SHARED_HPP
#define PSTADE_OVEN_SHARED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/pointee.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./share_iterator.hpp"


namespace pstade { namespace oven {


// 'callable/function' is useless here,
// because a temporary 'auto_ptr' is const-qualified
// then the ownership cannot be moved. So make it from scratch.


struct op_make_shared :
    provide_sig
{
    template< class FunCall >
    struct result;

    template< class Fun, class Ptr >
    struct result<Fun(Ptr)>
    {
        typedef typename
            boost::result_of<op_to_shared_ptr(Ptr)>::type
        sprng_t;

        typedef
            share_iterator<sprng_t>
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Ptr >
    typename result<void(Ptr)>::type
    operator()(Ptr prng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<typename boost::pointee<Ptr>::type>));

        typename boost::result_of<op_to_shared_ptr(Ptr)>::type
            sprng = to_shared_ptr(prng);
        return make_iter_range(
            make_share_iterator(boost::begin(*sprng), sprng),
            make_share_iterator(boost::end(*sprng),   sprng)
        );
    }
};


PSTADE_CONSTANT(make_shared, (op_make_shared))


namespace shared_detail {


    struct pipe :
        private boost::noncopyable
    { };


    template< class Ptr > inline
    typename boost::result_of<op_make_shared(Ptr)>::type
    operator|(Ptr prng, pipe const&)
    {
        return make_shared(prng);
    }


} // namespace shared_detail


PSTADE_CONSTANT(shared, (shared_detail::pipe))


} } // namespace pstade::oven


#endif
