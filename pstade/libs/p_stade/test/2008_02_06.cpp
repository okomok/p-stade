#include<functional>
#include <vector>
#include <algorithm>
#include <boost/iterator/transform_iterator.hpp>

class T
{
public:
        int _a;
        T(int a) : _a(a) {}
        bool greaterZero() const { return _a > 0; }
};

int main(void)
{
        typedef std::vector<T> Tlist;
        typedef std::const_mem_fun_ref_t<bool,T> Function;
    typedef boost::transform_iterator<Function,
                                     
Tlist::const_iterator> Iterator;
       
        Tlist x;
        Iterator
b(x.begin(),std::mem_fun_ref<bool,T>(&T::greaterZero)),
               
e(x.end(),std::mem_fun_ref<bool,T>(&T::greaterZero));
               
   
        std::lower_bound(b,e,false);  
} 
