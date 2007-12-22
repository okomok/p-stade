
#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>

char & to_lvalue(boost::tuple<char &, int &> const &t)
{
    return boost::get<0>(t);
}

template<class Iterator>
void check_category(Iterator)
{
    // failed.
    BOOST_MPL_ASSERT((boost::is_convertible<
        typename std::iterator_traits<Iterator>::iterator_category,
        std::random_access_iterator_tag
    >));
}

int main()
{
    std::string rng1;
    std::vector<int> rng2;

    ::check_category(
        boost::make_transform_iterator( // *Still* InputIterator
            boost::make_zip_iterator( // InputIterator
                boost::make_tuple(rng1.begin(), rng2.begin())
            ),
            &::to_lvalue
        )
     );
}
