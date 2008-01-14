
//#define _SECURE_SCL 0

#include <algorithm>
#include <vector>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

struct my_tag {};

template<class X>
struct is_my_tag : boost::mpl::false_{};

template<>
struct is_my_tag<my_tag> : boost::mpl::true_{};


template<class I, class J>
void foo(I, J) {}

template<class I>
void foo(I, my_tag) {}

template<class _BidIt1,
	class _BidIt2,
	class _BidIt3> inline
_BidIt3 bar(_BidIt1 _First1, _BidIt1 _Last1, _BidIt2 _First2, _BidIt2 _Last2, _BidIt3 _Dest, my_tag)
{
    return 0;
}
		
template<class _BidIt1, class _BidIt2, class _BidIt3, class _Pr>
inline
typename boost::enable_if<is_my_tag<_BidIt3>, _BidIt3>::type
bar(_BidIt1 _First1, _BidIt1 _Last1, _BidIt2 _First2, _BidIt2 _Last2, _BidIt3 _Dest, _Pr _Pred)
{
    return 0;
}


int main()
{
    {
        char *p = 0;
        ::bar(p, p, p, p, p, my_tag());
    }
#if 0
    {
        char *p = 0;
        ::foo(p, my_tag());
    }
    {
        std::vector<int> v;
        v.push_back(1); v.push_back(1); v.push_back(1); v.push_back(1);
        std::inplace_merge(v.begin(), v.begin()+1, v.begin()+2);
    }
#endif
#if 0
    {
        int *p = 0;
        std::inplace_merge(p, p, p);
    }
    {
        char *p = 0;
        std::inplace_merge(p, p, p);
    }
#endif
}
