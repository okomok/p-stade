#ifndef BOOST_BINARY_LITERAL_HPP
#define BOOST_BINARY_LITERAL_HPP

// Matt Calabrese
// rivorus_katarni@yahoo.com
// Sept. 05, 2005

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/push_back.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/control/while.hpp>

// Workaround as Boost.Preprocessor can't "concatenate" a sequence of length 1
#define BOOST_DETAIL_CAT_SIZE_1_SEQUENCE( sequence )                           \
  BOOST_PP_SEQ_ELEM( 0, sequence ) 

#define BOOST_DETAIL_FIXED_SEQ_CAT( sequence )                                 \
  BOOST_PP_IF( BOOST_PP_NOT_EQUAL                                              \
               (                                                               \
                 BOOST_PP_SEQ_SIZE( sequence )                                 \
               , 1                                                             \
               )                                                               \
             , BOOST_PP_SEQ_CAT                                                \
             , BOOST_DETAIL_CAT_SIZE_1_SEQUENCE                                \
             )                                                                 \
             ( sequence ) 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0 0, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_00 0, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_000 0, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0000 0, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1 1, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_01 1, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_001 1, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0001 1, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_10 2, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_010 2, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0010 2, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_11 3, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_011 3, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0011 3, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_100 4, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0100 4, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_101 5, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0101 5, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_110 6, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0110 6, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_111 7, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_0111 7, ( 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1000 8, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1001 9, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1010 A, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1011 B, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1100 C, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1101 D, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1110 E, ( 
#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_1111 F, ( 


#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0000 0, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0001 1, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0010 2, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0011 3, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0100 4, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0101 5, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0110 6, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_0111 7, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1000 8, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1001 9, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1010 A, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1011 B, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1100 C, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1101 D, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1110 E, ( 
#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_1111 F, ( 

#define BOOST_DETAIL_BINARY_LITERAL_ELEMENT_END_NIBBLE                         \
  BOOST_PP_NIL, ( BOOST_PP_NIL ) ( BOOST_PP_NIL 

#define BOOST_DETAIL_CURR_BINARY_LITERAL_SECONDARY_DATA( state )               \
  BOOST_PP_TUPLE_ELEM( 2, 1, state ) 

#define BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_OPERATION( secondary_data )   \
  ( BOOST_PP_CAT( BOOST_DETAIL_BINARY_LITERAL_ELEMENT_                         \
                , BOOST_PP_SEQ_HEAD( secondary_data )                          \
                )                                                              \
  ) ) 

#define BOOST_DETAIL_INIT_INTERMEDIATE_BINARY_LITERAL_OPERATION(secondary_data)\
  ( BOOST_PP_CAT( BOOST_DETAIL_INITIAL_BINARY_LITERAL_ELEMENT_                 \
                , BOOST_PP_SEQ_HEAD( secondary_data )                          \
                )                                                              \
  ) ) 

#define BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_ELEMENT( state )              \
  BOOST_PP_TUPLE_ELEM                                                          \
  ( 2, 0                                                                       \
  , BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_OPERATION                         \
    ( BOOST_DETAIL_CURR_BINARY_LITERAL_SECONDARY_DATA( state ) )               \
  ) 

#define BOOST_DETAIL_INITIAL_INTERMEDIATE_BINARY_LITERAL_ELEMENT( state )      \
  BOOST_PP_TUPLE_ELEM                                                          \
  ( 2, 0                                                                       \
  , BOOST_DETAIL_INIT_INTERMEDIATE_BINARY_LITERAL_OPERATION( state )           \
  ) 

#define BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_SUBSTATE( state )             \
  BOOST_PP_TUPLE_ELEM                                                          \
  ( 2, 1                                                                       \
  , BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_OPERATION                         \
    ( BOOST_DETAIL_CURR_BINARY_LITERAL_SECONDARY_DATA( state ) )               \
  ) 

#define BOOST_DETAIL_INITIAL_INTERMEDIATE_BINARY_LITERAL_SUBSTATE( state )     \
  BOOST_PP_TUPLE_ELEM                                                          \
  ( 2, 1                                                                       \
  , BOOST_DETAIL_INIT_INTERMEDIATE_BINARY_LITERAL_OPERATION( state )           \
  ) 

#define BOOST_DETAIL_BINARY_LITERAL_PREDICATE( s, state )                      \
  BOOST_PP_EQUAL                                                               \
  (                                                                            \
    BOOST_PP_SEQ_SIZE                                                          \
    ( BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_SUBSTATE( state ) )             \
  , 1                                                                          \
  ) 

#define BOOST_DETAIL_CURR_BINARY_LITERAL_HEX_SEQUENCE( state )                 \
  BOOST_PP_TUPLE_ELEM( 2, 0, state ) 

#define BOOST_DETAIL_BINARY_LITERAL_OPERATION( s, state )                      \
  (                                                                            \
    BOOST_PP_SEQ_PUSH_BACK                                                     \
    (                                                                          \
      BOOST_DETAIL_CURR_BINARY_LITERAL_HEX_SEQUENCE( state )                   \
    , BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_ELEMENT( state )                \
    )                                                                          \
  , BOOST_DETAIL_INTERMEDIATE_BINARY_LITERAL_SUBSTATE( state )                 \
  ) 

#define BOOST_DETAIL_INITIAL_BINARY_LITERAL_OPERATION( state )                 \
  (                                                                            \
    ( BOOST_DETAIL_INITIAL_INTERMEDIATE_BINARY_LITERAL_ELEMENT( state ) )      \
  , BOOST_DETAIL_INITIAL_INTERMEDIATE_BINARY_LITERAL_SUBSTATE( state )         \
  ) 

#define BOOST_DETAIL_CREATE_BINARY_LITERAL_HEX_SEQUENCE( nibbles )             \
  BOOST_DETAIL_CURR_BINARY_LITERAL_HEX_SEQUENCE                                \
  (                                                                            \
    BOOST_PP_WHILE( BOOST_DETAIL_BINARY_LITERAL_PREDICATE                      \
                  , BOOST_DETAIL_BINARY_LITERAL_OPERATION                      \
                  , BOOST_DETAIL_INITIAL_BINARY_LITERAL_OPERATION              \
                    ( ( nibbles END_NIBBLE ) )                                 \
                  )                                                            \
  )

#define BOOST_BINARY_LITERAL( nibbles )                                        \
  BOOST_PP_CAT( 0x                                                             \
              , BOOST_DETAIL_FIXED_SEQ_CAT                                     \
                ( BOOST_DETAIL_CREATE_BINARY_LITERAL_HEX_SEQUENCE( nibbles ) ) \
              ) 

#define BOOST_SUFFIXED_BINARY_LITERAL( nibbles, suffix )                       \
  BOOST_PP_CAT( BOOST_BINARY_LITERAL( nibbles ), suffix ) 

#endif
