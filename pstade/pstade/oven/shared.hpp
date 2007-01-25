#ifndef PSTADE_OVEN_SHARED_HPP
#define PSTADE_OVEN_SHARED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/noncopyable.hpp>
#include <boost/pointee.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include <pstade/remove_cvr.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./share_iterator.hpp"


namespace pstade { namespace oven {


// 'callable/function' is useless here,
// because a temporary 'auto_ptr' is const-qualified
// then the ownership cannot be moved. So make it from scratch.


struct op_make_shared
{
    template< class FunCall >
    struct result;

    template< class Fun, class Pointer >
    struct result<Fun(Pointer)>
    {
        typedef typename
            boost::pointee<typename remove_cvr<Pointer>::type>::type
        rng_t;

        typedef
            share_iterator<rng_t>
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Range >
    typename result<void(Range *)>::type
    operator()(Range *prng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename result<op_make_shared(Range *)>::type result_t;
        typedef typename result_t::iterator iter_t;

        boost::shared_ptr<Range> sprng(prng);
        return result_t(
            iter_t(boost::begin(*sprng), sprng),
            iter_t(boost::end(*sprng),   sprng)
        );
    }

    template< class X >
    typename result<void(std::auto_ptr<X>)>::type
    operator()(std::auto_ptr<X> prng) const
    {
        return (*this)(prng.release());
    }
};


PSTADE_CONSTANT(make_shared, (op_make_shared))


namespace shared_detail {


    struct pipe :
        private boost::noncopyable
    { };


    template< class Pointer > inline
    typename boost::result_of<op_make_shared(Pointer)>::type
    operator|(Pointer prng, pipe const&)
    {
        return make_shared(prng);
    }


} // namespace shared_detail


PSTADE_CONSTANT(shared, (shared_detail::pipe))


} } // namespace pstade::oven


#endif
