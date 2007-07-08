#ifndef PSTADE_EGG_INDIRECT_HPP
#define PSTADE_EGG_INDIRECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// This name will be changed, following boost::proto.


// Note:
//
// These will be replaced by <boost/numeric/functional.hpp>.


// References:
//
// [1] OptionalPointee Concept
//     http://www.boost.org/libs/utility/OptionalPointee.html


#include <boost/indirect_reference.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <pstade/affect.hpp>
#include <pstade/pod_constant.hpp>
#include "./adapt.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct indirect_value_impl :
        boost::indirect_reference<X>
    { };

    template<class X>
    struct indirect_value_impl<X const> :
        indirect_value_impl<X>
    { };

    template<class T>
    struct indirect_value_impl< boost::optional<T> >
    {
        typedef T type;
    };


    template<class Indirectable>
    struct indirect_value :
        indirect_value_impl<Indirectable>
    { };


    namespace indirect_detail {


        template<class Indirectable>
        struct base
        {
            typedef typename
                affect<
                    Indirectable&,
                    typename indirect_value<Indirectable>::type
                >::type
            result_type;

            result_type operator()(Indirectable& ind) const
            {
                return *ind;
            }
        };


    } // namespace indirect_detail


    typedef PSTADE_EGG_ADAPT((indirect_detail::base<boost::mpl::_>)) op_indirect;
    PSTADE_POD_CONSTANT((op_indirect), indirect) = PSTADE_EGG_ADAPT_INITIALIZER();


} } // namespace pstade::egg


#endif
