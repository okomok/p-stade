#ifndef PSTADE_OVEN_DETAIL_MONAD_HPP
#define PSTADE_OVEN_DETAIL_MONAD_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <vector>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "../concatenated.hpp"
#include "../memoized.hpp"
#include "../regular.hpp"
#include "../shared_single.hpp"
#include "../transformed.hpp"


namespace pstade { namespace oven { namespace detail {


struct baby_monad_bind
{
    template< class Myself, class Range, class UnaryFun >
    struct apply :
        result_of<
            op_make_concatenated(
                typename result_of<
                    op_make_memoized(
                        typename result_of<
                            op_make_transformed(Range& rng, typename result_of<op_regular(UnaryFun&)>::type)
                        >::type
                    )
                >::type
            )
        >
    { };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        return make_concatenated(
            // Once you call 'shared', it won't concatenatable without memoization,
            // because a new range is created every dereference.
            make_memoized(
                // It is nice to regularize 'fun', which is usually a LambdaExpression that isn't Assignable.
                make_transformed(rng, regular(fun))
            )
        );
    }
};

typedef egg::function<baby_monad_bind> op_monad_bind;
PSTADE_POD_CONSTANT((op_monad_bind), monad_bind) = {{}};


// Use 'shared' instead of 'shared_single'
// to synchronize the result type with 'monad_zero'.
//
// Todo: 'std::vector' is too "heavy"?

struct baby_monad_unit
{
    template< class Myself, class Value >
    struct apply :
        result_of<
            op_shared(std::vector<typename pass_by_value<Value>::type> *)
        >
    { };

    template< class Result, class Value >
    Result call(Value& v) const
    {
        typedef std::vector<typename pass_by_value<Value>::type> vec_t;

        // "share" it to avoid dangling; lambda expressions usually return "value".
        std::auto_ptr<vec_t> p(new vec_t(boost::addressof(v), boost::addressof(v) + 1));
        return shared(p.release());
    }
};

typedef egg::function<baby_monad_unit> op_monad_unit;
PSTADE_POD_CONSTANT((op_monad_unit), monad_unit) = {{}};


template< class Value >
struct xp_monad_zero
{
    typedef typename
        pass_by_value<Value>::type
    val_t;

    typedef typename
        result_of<
            op_shared(std::vector<val_t> *)
        >::type
    result_type;

    result_type operator()() const
    {
        std::auto_ptr< std::vector<val_t> > p(new std::vector<val_t>());
        return shared(p.release());
    }
};


} } } // namespace pstade::oven::detail


#endif
