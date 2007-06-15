#ifndef PSTADE_GRAVY_BOOLEAN_CAST_HPP
#define PSTADE_GRAVY_BOOLEAN_CAST_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/specified.hpp>
#include "./include/windows.hpp"
#include "./include/wtypes.hpp" // VARIANT_BOOL


namespace pstade { namespace gravy {


    namespace boolean_cast_detail {


        template<class Boolean>
        struct values_of;


        template< >
        struct values_of<bool>
        {
            static bool true_()  { return true; }
            static bool false_() { return false; }
        };

        template< >
        struct values_of<BOOL>
        {
            static BOOL true_()  { return TRUE; }
            static BOOL false_() { return FALSE; }
        };

        // It is actually dangerous to apply 'static_cast' to VARIANT_TRUE,
        // because the definition is '#define VARIANT_TRUE ((VARIANT_BOOL)-1)'.
        template< >
        struct values_of<VARIANT_BOOL>
        {
            static VARIANT_BOOL true_()  { return VARIANT_TRUE; }
            static VARIANT_BOOL false_() { return VARIANT_FALSE; }
        };

        template< >
        struct values_of<BOOLEAN>
        {
            static BOOLEAN true_()  { return (BOOLEAN)TRUE; }
            static BOOLEAN false_() { return (BOOLEAN)FALSE; }
        };

        template< >
        struct values_of<LRESULT>
        {
            static LRESULT true_()  { return 1; }
            static LRESULT false_() { return 0; }
        };


    } // namespace boolean_cast_detail


    template<class To>
    struct op_boolean_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From from) const
        {
            return from ?
                boolean_cast_detail::values_of<To>::true_() : boolean_cast_detail::values_of<To>::false_();
        }
    };

    PSTADE_SPECIFIED1(boolean_cast, op_boolean_cast, 1)
    PSTADE_AUXILIARY(0, to_boolean, (automatic< op_boolean_cast<_> >))


} } // namespace pstade::gravy


#endif
