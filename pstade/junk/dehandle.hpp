#ifndef PSTADE_DEHANDLE_HPP
#define PSTADE_DEHANDLE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional_fwd.hpp>
#include <pstade/apple/boost/smart_ptr_fwd.hpp>
#include <pstade/egg/defer.hpp>
#include <pstade/pod_constant.hpp>


namespace pstade_extension {

    template<class X>
    struct Handle;

}


namespace pstade {


    namespace dehandle_detail {


        template<class H>
        struct base
        {
            typedef
                pstade_extension::Handle<H>
            ext_t;

            typedef typename
                ext_t::object
            result_type;

            result_type operator()(H &h) const
            {
                return ext_t::dehandle(h);
            }
        };


    } // namespace dehandle_detail


    typedef PSTADE_EGG_DEFER((dehandle_detail<boost::mpl::_1>)) T_dehandle;
    PSTADE_POD_CONSTANT((T_dehandle), dehandle) = PSTADE_EGG_DEFERRED;


} // namespace pstade


namespace pstade_extension {


    // "identity" by default
    //

    template<class X>
    struct Handle
    {
        typedef X &object;

        object dehandle(X &x)
        {
            return x;
        }
    };


    // pointer
    //

    template<class T>
    struct Handle< T * >
    {
        typedef T &object;

        object dehandle(T * &x)
        {
            return *x;
        }
    };

    template<class T>
    struct Handle< T * const >
    {
        typedef T &object;

        object dehandle(T * const &x)
        {
            return *x;
        }
    };


    // shared_ptr
    //

    template<class T>
    struct Handle< boost::shared_ptr<T> >
    {
        typedef T &object;

        object dehandle(boost::shared_ptr<T> &x)
        {
            return *x;
        }
    };

    template<class T>
    struct Handle< boost::shared_ptr<T> const >
    {
        typedef T &object;

        object dehandle(boost::shared_ptr<T> const &x)
        {
            return *x;
        }
    };


    // boost::optional
    //

    template<class T>
    struct Handle< boost::optional<T> >
    {
        typedef T &object;

        object dehandle(boost::optional<T> &x)
        {
            return *x;
        }
    };

    template<class T>
    struct Handle< boost::optional<T> const >
    {
        typedef T const &object;

        object dehandle(boost::optional<T> const &x)
        {
            return *x;
        }
    };

    template<class T>
    struct Handle< boost::optional<T &> >
    {
        typedef T &object;

        object dehandle(boost::optional<T &> &x)
        {
            return *x;
        }
    };

    template<class T>
    struct Handle< boost::optional<T &> const >
    {
        typedef T &object;

        object dehandle(boost::optional<T &> const &x)
        {
            return *x;
        }
    };


} // namespace pstade_extension


#endif
