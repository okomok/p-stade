

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_OVEN_DETAIL_TO_XXX_PARAMS)
    #error 'PSTADE_OVEN_DETAIL_TO_XXX_PARAMS' must be defined before.
#endif

#include <boost/preprocessor/tuple/elem.hpp>
#define PSTADE_name BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_OVEN_DETAIL_TO_XXX_PARAMS)
#define PSTADE_func BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_OVEN_DETAIL_TO_XXX_PARAMS)


#include <locale>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "../concepts.hpp"
#include "../range_value.hpp"
#include "../transformed.hpp"


namespace pstade { namespace oven {


namespace BOOST_PP_CAT(PSTADE_name, _detail) {


    template< class Char >
    struct convert
    {
        typedef Char result_type;

        Char operator()(Char const& ch) const
        {
            return PSTADE_func(ch, m_loc);
        }

        explicit convert(std::locale const& loc) :
            m_loc(loc)
        { }

    private:
        std::locale m_loc;
    };


} // namespace BOOST_PP_CAT(PSTADE_name, _detail)


struct BOOST_PP_CAT(op_, PSTADE_name) :
    callable<BOOST_PP_CAT(op_, PSTADE_name)>
{
    template< class Myself, class Range, class Locale = std::locale const >
    struct apply :
        boost::result_of<
            op_make_transformed<>(
                Range&,
                BOOST_PP_CAT(PSTADE_name, _detail)::convert<typename range_value<Range>::type>
            )
        >
    { };

    template< class Result, class Range >
    Result call(Range& rng, std::locale const& loc) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        return make_transformed(
            rng,
            BOOST_PP_CAT(PSTADE_name, _detail)::convert<typename range_value<Range>::type>(loc)
        );
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, std::locale());
    }
};


PSTADE_ADL_BARRIER(PSTADE_name) { // for 'boost'
    PSTADE_CONSTANT(BOOST_PP_CAT(make_, PSTADE_name), (BOOST_PP_CAT(op_, PSTADE_name)))
    PSTADE_PIPABLE(PSTADE_name, (BOOST_PP_CAT(op_, PSTADE_name)))
}


} } // namespace pstade::oven


#undef  PSTADE_name
#undef  PSTADE_func
#undef  PSTADE_OVEN_DETAIL_TO_XXX_PARAMS

