#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/pipable.hpp>
#include "./checked.hpp"
#include "./concepts.hpp"
#include "./identities.hpp"
#include "./multi_passed.hpp"


namespace pstade { namespace oven {


namespace memoized_detail {


    // For no reason, 'multi_pass_policies::input_iterator'
    // regards the default-constructed iterator as the end iterator,
    // which is not preferable. So by using 'check_iterator'...

    struct input
    {
        template< class Iterator >
        struct inner
        {
            typedef typename boost::iterator_value<Iterator>::type value_type;
            typedef typename boost::iterator_difference<Iterator>::type difference_type;
            typedef typename boost::iterator_pointer<Iterator>::type pointer;
            typedef typename boost::iterator_reference<Iterator>::type reference;

        private:
            struct data_t
            {
                data_t(Iterator const& it) :
                    m_it(it), m_initialized(false)
                { }

                Iterator m_it;
                bool m_initialized;
                value_type m_value;
            };

           friend struct data_t;

        protected:
            explicit inner() :
                m_pdata(PSTADE_NULLPTR)
            { }

            explicit inner(Iterator const& it) :
                m_pdata(new data_t(it))
            { }

            void destroy()
            {
                boost::checked_delete(m_pdata);
                m_pdata = PSTADE_NULLPTR;
            }

            bool same_input(inner const& other) const
            {
                return m_pdata == other.m_pdata;
            }

            void swap(inner& other)
            {
                boost::spirit::impl::mp_swap(m_pdata, other.m_pdata);
            }

        private:
            void initialize() const
            {
                if (m_pdata && !m_pdata->m_initialized) {
                    m_pdata->m_value = *m_pdata->m_it;
                    m_pdata->m_initialized = true;
                }
            }

        public:
            reference get_input() const
            {
                BOOST_ASSERT(m_pdata != PSTADE_NULLPTR);
                initialize();
                return m_pdata->m_value;
            }

            void advance_input()
            {
                BOOST_ASSERT(m_pdata != PSTADE_NULLPTR);
                m_pdata->m_initialized = false;
                ++m_pdata->m_it;
            }

            bool input_at_eof() const
            {
                return !m_pdata || m_pdata->m_it.is_end();
            }

        private:
            data_t *m_pdata;
        }; // inner
    }; // input


} // namespace memoized_detail


struct op_make_memoized :
    callable<op_make_memoized>
{
    // If 'multi_pass_policies::first_owner' is passed,
    // it is impossible to be a conforming ForwardRange;
    // a singular iterator may take over the ownership,
    // which seems a bug of 'boost::multi_pass'.
    // The only workaround is applying 'memoized' twice!?
    template< class Myself, class Range, class MemoTable = void >
    struct apply :
        boost::result_of<
            op_make_identities(
                typename boost::result_of<
                    op_make_multi_passed<
                        memoized_detail::input,
                        boost::spirit::multi_pass_policies::first_owner
                    >(typename boost::result_of<op_make_checked(Range&)>::type)
                >::type,
                boost::single_pass_traversal_tag
            )
        >
    { };

    template< class Result, class Range >
    Result call(Range& rng, memo_table& tb) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        return
            make_identities(
                op_make_multi_passed<
                    memoized_detail::input,
                    boost::spirit::multi_pass_policies::first_owner
                >()(make_checked(rng), tb),
                boost::single_pass_traversal_tag()
            );
    }

    template< class Myself, class Range >
    struct apply<Myself, Range> :
        boost::result_of<
            op_make_multi_passed<
                memoized_detail::input
            >(typename boost::result_of<op_make_checked(Range&)>::type)
        >
    { };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        return
            op_make_multi_passed<
                memoized_detail::input
            >()(make_checked(rng));
    }
};


PSTADE_CONSTANT(make_memoized, (op_make_memoized))
PSTADE_PIPABLE(memoized, (op_make_memoized))


} } // namespace pstade::oven


#endif
