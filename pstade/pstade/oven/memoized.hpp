#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./checked.hpp"
#include "./concepts.hpp"
#include "./multi_passed.hpp"


namespace pstade { namespace oven {


namespace memoized_detail {


    // See:
    // boost::spirit::multi_pass_policies::input_iterator
    //
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


    template< class Range >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_make_multi_passed<input>(typename boost::result_of<op_make_checked(Range&)>::type)
            >::type
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return op_make_multi_passed<input>()(make_checked(rng));
        }
    };


} // namespace memoized_detail


PSTADE_FUNCTION(make_memoized, (memoized_detail::baby<_>))
PSTADE_PIPABLE(memoized, (op_make_memoized))


} } // namespace pstade::oven


#endif
