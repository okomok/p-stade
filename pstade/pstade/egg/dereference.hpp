#ifndef PSTADE_EGG_DEREFERENCE_HPP
#define PSTADE_EGG_DEREFERENCE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


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
    struct dereference_value_impl :
        boost::indirect_reference<X>
    { };

    template<class X>
    struct dereference_value_impl<X const> :
        dereference_value_impl<X>
    { };

    template<class T>
    struct dereference_value_impl< boost::optional<T> >
    {
        typedef T type;
    };


    template<class Ptr_>
    struct dereference_value :
        dereference_value_impl<Ptr_>
    { };


    namespace dereference_detail {


        template<class Ptr_>
        struct base
        {
            typedef typename
                affect<
                    Ptr_&,
                    typename dereference_value<Ptr_>::type
                >::type
            result_type;

            result_type operator()(Ptr_& ptr) const
            {
                return *ptr;
            }
        };


    } // namespace dereference_detail


    typedef PSTADE_EGG_ADAPT((dereference_detail::base<boost::mpl::_>)) op_dereference;
    PSTADE_POD_CONSTANT((op_dereference), dereference) = PSTADE_EGG_ADAPT_INITIALIZER();


} } // namespace pstade::egg


#endif
