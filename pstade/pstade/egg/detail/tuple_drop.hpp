#ifndef PSTADE_EGG_DETAIL_TUPLE_DROP_HPP
#define PSTADE_EGG_DETAIL_TUPLE_DROP_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/affect.hpp>


namespace pstade { namespace egg { namespace detail {


    // drop n xs | n <= 0  = xs
    // drop _ []           = []
    // drop n (_:xs)       = drop (n-1) xs

    template<int N, class Tuple_>
    struct tuple_drop_aux
    {
        typedef typename Tuple_::tail_type tail_t;

        template<class Tuple>
        struct result_ :
            tuple_drop_aux<N-1, tail_t>::template result_<typename affect_const<Tuple, tail_t>::type>
        { };

        template<class Tuple>
        static typename result_<Tuple>::type call_(Tuple& t)
        {
            return tuple_drop_aux<N-1, tail_t>::call_(t.get_tail());
        }
    };

    template<class Tuple_>
    struct tuple_drop_aux<0, Tuple_>
    {
        template<class Tuple>
        struct result_
        {
            typedef Tuple& type;
        };

        template<class Tuple>
        static Tuple& call_(Tuple& t)
        {
            return t;
        }
    };

    // needed cuz t.get_tail() doesn't return reference when t is one element tuple.
    template< >
    struct tuple_drop_aux<0, boost::tuples::null_type>
    {
        template<class Tuple>
        struct result_
        {
            typedef boost::tuples::null_type type;
        };

        static boost::tuples::null_type call_(boost::tuples::null_type t)
        {
            return t;
        }
    };


    template<class N, class Tuple>
    struct result_of_tuple_drop :
        tuple_drop_aux<N::value, typename boost::remove_const<Tuple>::type>::template result_<Tuple>
    { };

    template<class N, class Tuple> inline
    typename result_of_tuple_drop<N, Tuple>::type
    tuple_drop_call(Tuple& t)
    {
        return tuple_drop_aux<N::value, typename boost::remove_const<Tuple>::type>::call_(t);
    }


    template<class N>
    struct little_tuple_drop
    {
        template<class Me, class Tuple>
        struct apply :
            result_of_tuple_drop<N, Tuple>
        { };

        template<class Re, class Tuple>
        Re call(Tuple& t) const
        {
            return detail::tuple_drop_call<N>(t);
        }
    };

    template<class N, class Strategy>
    struct X_tuple_drop :
        function<little_tuple_drop<N>, Strategy>
    { };

    template<int N, class Strategy>
    struct X_tuple_drop_c :
        X_tuple_drop<boost::mpl::int_<N>, Strategy>
    { };


} } } // namespace pstade::egg::detail


#endif
