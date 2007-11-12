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
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/by_cref.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/remove_cvr.hpp>
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
            T_make_concatenated(
                typename result_of<
                    T_make_memoized(
                        typename result_of<
                            T_make_transformed(Range& rng, typename result_of<T_regular(UnaryFun&)>::type)
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

typedef egg::function<baby_monad_bind> T_monad_bind;
PSTADE_POD_CONSTANT((T_monad_bind), monad_bind) = {{}};


// Use 'shared' instead of 'shared_single'
// to synchronize the result type with 'monad_zero'.
//
// Todo: 'std::vector' is too "heavy"?

struct baby_monad_unit
{
    template< class Myself, class Value >
    struct apply :
        result_of<
            T_shared(std::vector<typename boost::remove_cv<Value>::type> *)
        >
    { };

    template< class Result, class Value >
    Result call(Value& v) const
    {
        typedef std::vector<typename boost::remove_cv<Value>::type> vec_t;

        // "share" it to avoid dangling; lambda expressions usually return "value".
        std::auto_ptr<vec_t> p(new vec_t(boost::addressof(v), boost::addressof(v) + 1));
        return shared(p.release());
    }
};

typedef egg::function<baby_monad_unit, egg::by_cref> T_monad_unit;
PSTADE_POD_CONSTANT((T_monad_unit), monad_unit) = {{}};


template< class Value >
struct X_monad_zero
{
    typedef X_monad_zero function_type;

    typedef typename
        result_of<
            T_shared(std::vector<typename remove_cvr<Value>::type> *)
        >::type
    result_type;

    result_type operator()() const
    {
        typedef std::vector<typename remove_cvr<Value>::type> vec_t;

        // empty range
        std::auto_ptr<vec_t> p(new vec_t());
        return shared(p.release());
    }
};


} } } // namespace pstade::oven::detail


#endif
