// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



// A Defect Report:
//     value_of invocation around transform_view doesn't always work.
//


#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/list.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/utility/result_of.hpp>
#include <string>

namespace fusion = boost::fusion;



// 1. Background
//
// Making a fusion_zip_iterator which is a Fusion version of boost::zip_iterator.
// This iterator is internally used by make_fusion_zip_range.
// For example,
//
// std::cout <<
//    make_fusion_zip_range( fusion::make_list(std::string("123"), std::string("abc")) );
//
// outputs: {(1 a),(2 b),(3 c)}

// For simplicity, assume you've already written a right fusion_zip_iterator.
// Note that, in general, it is a bad idea for iterator adaptor to hold 
// a reference to a Container/Range, because input Range may be a temporary proxy
// something like boost::iterator_range.
// So, this iterator must hold not a View but a Vector. Ditto boost::zip_iterator.
template <typename FusionVectorOfStlIterators>
struct fusion_zip_iterator
{
    explicit fusion_zip_iterator(FusionVectorOfStlIterators const& iters)
        : m_stl_iters(iters)
    {}

    FusionVectorOfStlIterators m_stl_iters;

    // iterator implementations
    // ...
};

// Let's make a fusion_zip_iterator object holding begin iterators.
// For simplicity, Boost.Range isn't used in this example.

// result_of-conforming FunctionObject to get begin iterator.
struct T_mybegin
{
    template <typename Signature>
    struct result;

    template <typename This, typename Container>
    struct result<This(Container&)> // mutable lvalue
    {
        typedef typename Container::iterator type;
    };

    template <typename This, typename Container>
    struct result<This(Container const&)> // const lvalue
    {
        typedef typename Container::const_iterator type;
    };

    template <typename This, typename Container>
    struct result<This(Container)> // rvalue
    {
        typedef typename Container::const_iterator type;
    };

    template <typename Container>
    typename Container::iterator operator()(Container& c) const
    {
        return c.begin();
    }

    template <typename Container>
    typename Container::const_iterator operator()(Container const& c) const
    {
        return c.begin();
    }
};

T_mybegin const mybegin = {};

template <typename SequenceOfContainers, typename Begin>
fusion_zip_iterator<
    typename fusion::result_of::as_vector<
        fusion::transform_view<SequenceOfContainers, Begin>
    >::type
>
make_fusion_zip_iterator(SequenceOfContainers& seq, Begin beg)
{
    return
        fusion_zip_iterator<
            typename fusion::result_of::as_vector<
                fusion::transform_view<SequenceOfContainers, Begin>
            >::type
        >(
            fusion::as_vector(
                fusion::transform_view<SequenceOfContainers, Begin>(seq, beg)
            )
        );
}


// Surprisingly, this doesn't compile for now.
void test_mutability_of_stl_iters()
{
    fusion::list<std::string, std::string> seq("abc", "efg");

#if 0
    // compile error: you cannot assign to a variable that is const.
    *fusion::at_c<0>(make_fusion_zip_iterator(seq, mybegin).m_stl_iters) = 'x';
    BOOST_TEST(*fusion::at_c<0>(make_fusion_zip_iterator(seq, mybegin).m_stl_iters) == 'x');
#endif
}



// 2. Problem
//

// The problem is that fusion::as_vector calls boost::result_of(through fusion::value_of)
// in non-conforming manner.
// In this case, `result_of<T_mybegin(std::string)>` is called, which means its arument is rvalue.
// my_begin can't get a mutable STL iterator from rvalue Container.



// 3. A current workaround
//

// A "cheated" mybegin is needed for as_vector.
struct T_mybegin_cheat
{
    template <typename Signature>
    struct result;

    template <typename This, typename Container>
    struct result<This(Container&)> // mutable lvalue
    {
        typedef typename Container::iterator type;
    };

    template <typename This, typename Container>
    struct result<This(Container const&)> // const lvalue
    {
        typedef typename Container::const_iterator type;
    };

    template <typename This, typename Container>
    struct result<This(Container)> // rvalue
    {
        typedef typename Container::iterator type; // cheating!
    };

    template <typename Container>
    typename Container::iterator operator()(Container& c) const
    {
        return c.begin();
    }

    template <typename Container>
    typename Container::const_iterator operator()(Container const& c) const
    {
        return c.begin();
    }
};

T_mybegin_cheat const mybegin_cheat = {};

void test_mutability_of_stl_iters_cheat()
{
    fusion::list<std::string, std::string> seq("abc", "efg");

    // ok!
    *fusion::at_c<0>(make_fusion_zip_iterator(seq, mybegin_cheat).m_stl_iters) = 'x';
    BOOST_TEST(*fusion::at_c<0>(make_fusion_zip_iterator(seq, mybegin_cheat).m_stl_iters) == 'x');
}

// This workaround is clearly a bad resolution.
// You have to write a cheated FunctionObject which is not result_of-conforming.
// Also, transform_view and as_vector is tightly-bonded.
// (Notice transform_view with mybegin_cheat is broken.)



// 4. Proposed Resolution.
//

// The prbolem is that the default behavior of transform_view's value_of
// is unsatisfactory for some FunctionObjects.
// So, transform_view should take an optional MetafunctionClass for value_of implementation.


struct use_default; // may be any name.

template <typename Seq, typename Fun, typename ValueOf = use_default>
struct transform_view;



// 5. value_of implementation of transform_view
//

// Notation:
//    * Assume `I` is an iterator of `Seq`.
//    * Assume `J` is a `transform_view<Seq, Fun, ValueOf>` iterator whose underlying iterator is `I`.
//    * Assume `V` is a metafunction which represents the default behavior.
//    * Assume `W` is `mpl::apply1<ValueOf, fusion::result_of::deref<I>::type, fusion::result_of::value_of<I>::type>`.

// Valid Expression:
//     * `result_of::value_of<J>::type`

// Valid Expression's semantics:
//     * `mpl::eval_if< boost::is_same<ValueOf, use_default>, V, W>::type`

// Precondition:
//    * Value Expression's semantics is a valid expression.

// Notice:
//    * `W` uses both `deref` and `value_of`. That's fusion.
//    * `mpl::eval_if` must be used instead of `mpl::if_`, because `V::type` may be ill-formed.



// 6. Example of ValueOf template argument
//

// ValueOf of mybegin will be something like this:
struct mybegin_value_of
{
    template <typename Ref, typename Value>
    struct apply :
        boost::result_of<T_mybegin(Ref)>
    {};
};



//
// END.


int main()
{
    test_mutability_of_stl_iters();
    test_mutability_of_stl_iters_cheat();
    return boost::report_errors();
}
