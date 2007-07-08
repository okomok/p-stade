#ifndef PSTADE_SAUSAGE_YIELD_RANGE_HPP
#define PSTADE_SAUSAGE_YIELD_RANGE_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/generator.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/lightweight_copyable.hpp>
#include <pstade/pod_constant.hpp>
#include "./yield_iterator.hpp"


namespace pstade { namespace sausage {


namespace yield_range_detail {


    template< class Routine >
    struct super_ :
        oven::iter_range<
            yield_iterator<Routine>
        >
    { };


} // namespace yield_range_detail


template< class Routine >
struct yield_range :
    yield_range_detail::super_<Routine>::type,
    private oven::lightweight_copyable< yield_range<Routine> >
{
    typedef yield_range type;

private:
    typedef typename yield_range_detail::super_<Routine>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit yield_range(Routine const& rou) :
        super_t(iter_t(rou), iter_t())
    { }
};


typedef
    egg::generator<
        yield_range< egg::deduce<boost::mpl::_1, egg::as_value> > const
    >::type
op_make_yield_range;

PSTADE_POD_CONSTANT((op_make_yield_range), make_yield_range)
    = PSTADE_EGG_GENERATOR_INITIALIZER();

PSTADE_POD_CONSTANT((egg::result_of_pipable<op_make_yield_range>::type), yielded)
    = PSTADE_EGG_PIPABLE_RESULT_INITIALIZER(PSTADE_EGG_GENERATOR_INITIALIZER);


} } // namespace pstade::sausage


#endif
