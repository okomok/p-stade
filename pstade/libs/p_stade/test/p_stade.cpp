#include <boost/oven/merged.hpp>
#include <boost/oven/partitioned.hpp>
#include <boost/oven/any_range.hpp>
#include <boost/oven/io.hpp>


template<typename Predicate >
range merge_sort(range rng, Predicate prd)
{
    typename boost::result_of<op_make_paritioned(rng&, Predicate&)>::type
        xs_ys = make_paritioned(rng, prd);

    return
        make_merged(
            merge_sort(boost::get<0>(xs_ys)),
            merge_sort(boost::get<1>(xs_ys))
        );
}



int main()
{





}