#ifndef PSTADE_INDIRECT_HPP
#define PSTADE_INDIRECT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/indirect_reference.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/function.hpp>


namespace pstade {


    template<class I>
    struct indirect_value_impl :
        boost::indirect_reference<I>
    { };

    template<class T>
    struct indirect_value_impl< boost::optional<T> >
    {
        typedef T type;
    };


    template<class Indirectable>
    struct indirect_value :
        indirect_value_impl<
            typename boost::remove_cv<Indirectable>::type
        >
    { };


    namespace indirect_detail {


        template<class Indirectable>
        struct baby
        {
            typedef typename
                affect<
                    Indirectable&,
                    typename indirect_value<Indirectable>::type
                >::type
            result_type;

            result_type operator()(Indirectable& i) const
            {
                return *i;
            }
        };


    } // namespace indirect_detail


    PSTADE_FUNCTION(indirect, (indirect_detail::baby<_>))


} // namespace pstade


#endif
