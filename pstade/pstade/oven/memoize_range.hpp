#ifndef PSTADE_OVEN_MEMOIZE_RANGE_HPP
#define PSTADE_OVEN_MEMOIZE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nullptr.hpp>
#include "./check_range.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./multi_pass_range.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace memoize_range_detail {


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
                data_t(Iterator it) :
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

            explicit inner(Iterator it) :
                m_pdata(new data_t(it))
            { }

            void destroy()
            {
                delete m_pdata;
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
    struct super_
    {
        typedef multi_pass_range<
            check_range<Range> const,
            input
        > type;
    };


} // namespace memoize_range_detail


template< class Range >
struct memoize_range :
    memoize_range_detail::super_<Range>::type
{
private:
    typedef typename memoize_range_detail::super_<Range>::type super_t;

public:
    explicit memoize_range(Range& rng) :
        super_t(check_range<Range>(rng))
    { }
};


namespace memoize_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct result
        {
            typedef memoize_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace memoize_range_detail


PSTADE_EGG_FUNCTION(make_memoize_range, memoize_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(memoized, memoize_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::memoize_range, 1)


#endif
