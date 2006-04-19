#ifndef PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP
#define PSTADE_SAUSAGE_DETAIL_CUSTOMIZATION_OF_TYPE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/remove_rcv.hpp>
#include "../customization.hpp"


namespace pstade { namespace sausage { namespace detail {


PSTADE_HAS_TYPE(pstade_sausage_enumerate_argument_type)
PSTADE_HAS_TYPE(pstade_sausage_tag)


template< class T >
struct customization_tag_is_specialized :
    boost::mpl::not_<
        boost::is_same<typename customization_tag<T>::type, default_way_tag>
    >
{ };


template< class T >
struct get_intrusive_tag :
    boost::mpl::identity<typename T::pstade_diet_tag>
{ };


template< class T >
struct customization_of
{
private:
    typedef typename remove_rcv<T>::type bare_t;

    typedef typename
    boost::mpl::eval_if< customization_tag_is_specialized<bare_t>,
        customization_tag<bare_t>,
        boost::mpl::eval_if< has_pstade_sausage_enumerate_argument_type<bare_t>,
            boost::mpl::identity<intrusive_way_tag>,
            boost::mpl::eval_if< has_pstade_sausage_tag<bare_t>,
                get_intrusive_tag<bare_t>,
                boost::mpl::eval_if< apple::is_boost_range<bare_t>,
                    boost::mpl::identity<boost_range_tag>,
                    boost::mpl::identity<bare_t> // use the type as tag
                >
            >
        >
    >::type tag_t;

public:
    typedef customization<tag_t> type;
};


} } } // namespace pstade::sausage::detail


#endif
