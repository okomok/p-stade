 
#include <boost/bind.hpp> 
/*
namespace boost 
{ 
    template<typename T> 
    class bind_obj 
    { 
        typedef void (T::*pFuncT)(); 
    public: 
        bind_obj( pFuncT pFunc, T *pObj ) 
            : 
            pFunc(pFunc), 
            pObj(pObj) 
            {} 
        void operator () () 
        {} 
    private: 
        pFuncT   pFunc; 
        T        *pObj; 
    }; 


    template<typename T, typename U> 
    class bind_obj1 
    { 
        typedef void (T::*pFuncT)( const U& ); 
    public: 
        bind_obj1( pFuncT pFunc, T *pObj, const U& u ) 
            : 
            pFunc(pFunc), 
            pObj(pObj), 
            u(u) 
            {} 
        void operator () () 
        {} 
    private: 
        pFuncT      pFunc; 
        T           *pObj; 
        const U&    u; 
    }; 


    template<typename T> 
    bind_obj<T> bind( void (T::*pFunc)(), T *pObj ) 
    { 
        return bind_obj<T>( pFunc, pObj ); 
    } 
    template<typename T, typename U> 
    bind_obj1<T, U> bind( void (T::*pFunc)( const U& ), T *pObj, const U& u ) 
    { 
        return bind_obj1<T, U>( pFunc, pObj, u ); 
    } 


} // namespace boost(only for test) 
*/

struct A {}; 
struct B {}; 


struct X 
{ 
    template<typename T, typename U> 
    void f( const T& t ) 
    { 
        //... 
    } 


    template<typename U> 
    void f2() 
    { 
        //... 
    } 


    template<typename F> 
    void do_it( F f ) const 
    { 
        f(); 
    } 


    struct Y 
    { 
        Y( X& x )
        { 
            /*__1__*/x.do_it( boost::bind<void, X, const A&>(&X::f<A, B>, &x, A()) ); 
            /*__2__*/x.do_it( boost::bind<void, X>(&X::f2<B>, &x) ); 
        }
    }; 


    X() 
    { 
        Y(*this); 
    } 



}; 



int main() 
{ 
    X x; 
    return 0; 


} 
