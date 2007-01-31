#ifndef PSTADE_OVEN_ZIPPED_HPP
#define PSTADE_OVEN_ZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./begin_end.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace zipped_detail {


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    namespace mpl = boost::mpl;
    namespace tuples = boost::tuples;


    // The parameter of 'detail::tuple_meta_transform' is const-qualified,
    // which is redundant here. Thus, until Boost.Fusion comes, we define...

    // <cut-and-paste>
    //

      template<typename Fun>
      tuples::null_type BOOST_TUPLE_ALGO(tuple_transform)
          (tuples::null_type const&, Fun BOOST_TUPLE_ALGO_TERMINATOR)
      { return tuples::null_type(); }

      template<typename Tuple, typename Fun>
      typename tuple_meta_transform<
          typename boost::remove_const<Tuple>::type // FIXED
        , Fun
      >::type

      BOOST_TUPLE_ALGO(tuple_transform)(
        /*const*/ Tuple& t, // FIXED
        Fun f
        BOOST_TUPLE_ALGO_RECURSE
      )
      { 
          typedef typename tuple_meta_transform<
              BOOST_DEDUCED_TYPENAME Tuple::tail_type
            , Fun
          >::type transformed_tail_type;

        return tuples::cons<
            BOOST_DEDUCED_TYPENAME mpl::apply1<
                Fun, BOOST_DEDUCED_TYPENAME Tuple::head_type
             >::type
           , transformed_tail_type
        >( 
            f(boost::tuples::get<0>(t)), (tuple_transform)(t.get_tail(), f) // FIXED
        );
      }

#ifdef BOOST_TUPLE_ALGO_DISPATCH
      template<typename Tuple, typename Fun>
      typename tuple_meta_transform<
          typename boost::remove_const<Tuple>::type
        , Fun
      >::type
      
      tuple_transform(
        /*const*/ Tuple& t, // FIXED
        Fun f
      )
      {
          return (tuple_transform_impl)(t, f, 1); // FIXED
      }
#endif

    //
    // </cut-and-paste>


    template< class RangeTuple >
    struct with_apply
    {
        template< class Range > // 'Range' is what 'value_at' returns.
        struct apply :
            boost::result_of<
                op_begin(typename affect<RangeTuple&, Range>::type)
            >
        { };
    };


    template< class RangeTuple >
    struct begin_fun :
        with_apply<RangeTuple>
    {
        template< class Range >
        typename range_iterator<Range>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    template< class RangeTuple >
    struct end_fun :
        with_apply<RangeTuple>
    {
        template< class Range >
        typename range_iterator<Range>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeTuple >
    struct baby
    {
        typedef
            boost::zip_iterator<
                typename tuple_meta_transform<
                    typename boost::remove_const<RangeTuple>::type,
                    with_apply<RangeTuple>
                >::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(RangeTuple& tup)
        {
            return result(
                iter_t( (tuple_transform)(tup, begin_fun<RangeTuple>()) ),
                iter_t( (tuple_transform)(tup, end_fun<RangeTuple>()) )
            );
        }
    };


} // namespace zipped_detail


PSTADE_FUNCTION(make_zipped, (zipped_detail::baby<_>))
PSTADE_PIPABLE(zipped, (op_make_zipped))


} } // namespace pstade::oven


#endif
