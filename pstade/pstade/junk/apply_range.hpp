#ifndef PSTADE_OVEN_APPLY_RANGE_HPP
#define PSTADE_OVEN_APPLY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/lambda.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/arg.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


namespace apply_range_detail {


    // Workaround:
    // Lambda functor 'operator()' needs reference.
    // If you pass 'boost::begin(rng)' to 'operator()' directly,
    // the iterator can't avoid to be const-qualified reference.
    // Thus, ++bll::_1 becomes impossible.
    //
    template< class Range, int i >
    struct base_iterator
    {
        typedef boost::base_from_member<
            typename boost::range_result_iterator<Range>::type, i
        > type;
    };

    
    // Workaround:
    // Placeholder's RET must be reference irrelevantly.
    // That is, 'bll::ret<iter_t>(bll::_1)(it);' makes static assertion failure.
    // so don't touch it. 
    //
    template< class RET> inline
    const boost::lambda::lambda_functor< boost::lambda::placeholder<boost::lambda::FIRST> >&
    ret(const boost::lambda::lambda_functor< boost::lambda::placeholder<boost::lambda::FIRST> >& a1)
    {
        return a1;
    }

    // normal call
    template< class RET, class Arg > inline const 
        boost::lambda::lambda_functor<
            boost::lambda::lambda_functor_base<
               boost::lambda::explicit_return_type_action<RET>, 
                boost::tuple< boost::lambda::lambda_functor<Arg>
            >
        > 
    >
    ret(const boost::lambda::lambda_functor<Arg>& a1)
    {
        return boost::lambda::ret<RET>(a1);
    }


} // namespace apply_range_detail


template< class Range, class BinaryFun1, class BinaryFun2 >
struct apply_range :
    private apply_range_detail::base_iterator<Range, 1>::type,
    private apply_range_detail::base_iterator<Range, 2>::type,
    private apply_range_detail::base_iterator<Range, 3>::type,
    private apply_range_detail::base_iterator<Range, 4>::type,
    sub_range_base<Range>::type
{
private:
    typedef typename apply_range_detail::base_iterator<Range, 1>::type f_iter1_bt;
    typedef typename apply_range_detail::base_iterator<Range, 2>::type l_iter1_bt;
    typedef typename apply_range_detail::base_iterator<Range, 3>::type f_iter2_bt;
    typedef typename apply_range_detail::base_iterator<Range, 4>::type l_iter2_bt;
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit apply_range(Range& rng, BinaryFun1 f1, BinaryFun2 f2) :
        f_iter1_bt(boost::begin(rng)), l_iter1_bt(boost::end(rng)),
        f_iter2_bt(boost::begin(rng)), l_iter2_bt(boost::end(rng)),
        super_t(
            // 'iter_t(' lets compile-errors readable.
            iter_t( apply_range_detail::ret<iter_t>(f1)(f_iter1_bt::member, l_iter1_bt::member) ),
            iter_t( apply_range_detail::ret<iter_t>(f2)(f_iter2_bt::member, l_iter2_bt::member) )
        )
    { }
};


namespace apply_range_detail {


    struct baby_generator
    {
        template< class Range, class BinaryFun1, class BinaryFun2 >
        struct result
        {
            typedef typename boost::remove_cv<BinaryFun1>::type f1_t;
            typedef typename boost::remove_cv<BinaryFun2>::type f2_t;
            typedef const apply_range<Range, f1_t, f2_t> type;
        };

        template< class Result, class Range, class BinaryFun1, class BinaryFun2 >
        Result call(Range& rng, BinaryFun1 f1, BinaryFun2 f2)
        {
            return Result(rng, f1, f2);
        }
    };


} // namespace apply_range_detail


PSTADE_EGG_FUNCTION(make_apply_range, apply_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(applied, apply_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::apply_range, 3)


#endif
