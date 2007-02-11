#ifndef PSTADE_OVEN_MULTI_PASSED_HPP
#define PSTADE_OVEN_MULTI_PASSED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/spirit/iterator/multi_pass.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace memo_table_detail {


    struct placeholder
    {
        virtual ~placeholder()
        { }
    };

    template< class Iterator >
    struct holder :
        placeholder
    {
        holder(std::auto_ptr<Iterator> pfirst, std::auto_ptr<Iterator> plast) :
            m_pfirst(pfirst), m_plast(plast)
        { }

    private:
        std::auto_ptr<Iterator> m_pfirst;
        std::auto_ptr<Iterator> m_plast;
    };
    

} // namespace memo_table_detail


struct memo_table :
    private boost::noncopyable
{
    template< class Iterator >
    void set(std::auto_ptr<Iterator> pfirst, std::auto_ptr<Iterator> plast)
    {
        m_pimpl.reset(new memo_table_detail::holder<Iterator>(pfirst, plast));
    }

private:
    std::auto_ptr<memo_table_detail::placeholder> m_pimpl;
};


template<
    class InputPolicy     = boost::use_default,
    class OwnershipPolicy = boost::use_default,
    class CheckingPolicy  = boost::use_default,
    class StoragePolicy   = boost::use_default
>
struct op_make_multi_passed :
    callable< op_make_multi_passed<InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy> >
{
    template< class Myself, class InputIterRange, class FirstOwners = void >
    struct apply
    {
        // InputIterRange seems the undocumented concept by Boost.Spirit.

        typedef
            boost::spirit::multi_pass<
                typename range_iterator<InputIterRange>::type,
                typename use_default_to<InputPolicy,     boost::spirit::multi_pass_policies::input_iterator>::type,
                typename use_default_to<OwnershipPolicy, boost::spirit::multi_pass_policies::ref_counted>::type,
                typename use_default_to<CheckingPolicy,  boost::spirit::multi_pass_policies::buf_id_check>::type,
                typename use_default_to<StoragePolicy,   boost::spirit::multi_pass_policies::std_deque>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class InputIterRange >
    Result call(InputIterRange& rng) const
    {
        return Result(rng);
    }

    template< class Result, class InputIterRange >
    Result call(InputIterRange& rng, memo_table& tb) const
    {
        typedef typename Result::iterator iter_t;

        // first owners
        std::auto_ptr<iter_t> pfirst( new iter_t(boost::begin(rng)) );
        std::auto_ptr<iter_t> plast ( new iter_t(boost::end(rng)) );

        Result result(*pfirst, *plast);
        tb.set(pfirst, plast);

        return result;
    }
};


PSTADE_CONSTANT(make_multi_passed, (op_make_multi_passed<>))
PSTADE_PIPABLE(multi_passed, (op_make_multi_passed<>))


} } // namespace pstade::oven


#endif
