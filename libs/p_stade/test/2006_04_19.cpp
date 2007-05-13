#include <stdio.h>      // printf()

#include <algorithm>    // std::random_shuffle()
#include <vector>       // std::vector<>
#include <list>         // std::list<>

int main()
{
    static const int  SIZE_TBL[] = { 10000, 50000, 100000, 200000 } ;

    for ( int s=0, z=sizeof(SIZE_TBL)/sizeof(SIZE_TBL[0]) ; s<z ; ++s )
    {
        std::vector< int >  data( SIZE_TBL[s] ) ;

        for ( int i=0 ; i<SIZE_TBL[s] ; ++i )
            data[i] = i+1 ;

        std::random_shuffle( data.begin(), data.end() ) ; // “K“–‚É‚©‚«¬‚º‚Ä

        std::list< int >  list( data.begin(), data.end() ) ; // list‚É“]‘—

        // list‚Ì‰Šúó‘Ô‚ğ•\¦
        printf( "init, size: %d, %d .. %d\n", list.size(), list.front(), list.back() ) ;

        list.sort() ;

        // sort()Œã‚Ìó‘Ô‚ğ•\¦
        printf( "sort, size: %d, %d .. %d\n", list.size(), list.front(), list.back() ) ;
    }
    //end for s

    return 0 ;
}