++++++++++++++++++++++++++
The Biscuit Parser Library
++++++++++++++++++++++++++


:Author: MB and Christopher Diggins(original author)
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 1.02.8



.. image:: ./doc/logo.png
   :alt: Biscuit



.. epigraph::

	"*If your slave commits a fault, do not smash his teeth with your fists; give him some of the biscuit which famous Rhodes has sent you.*"
	
	-- Marcus Valerius Martialis



.. contents:: **Table of Contents**
.. section-numbering::



Motivation
----------
I was looking for a small and unstrict xml parser.
`Boost.Spirit`_ and `Boost.Xpressive`_ showed a lot of functionality but made big executables.
On the other hand, YARD_ written by `Christopher Diggins`_ was simple, small and fast.
In time, I found that YARD_ and `Boost.Range`_ could be binded. It was named Biscuit.



Introduction
------------
Biscuit is an object-oriented recursive-descent parser generator framework
implemented using class templates. The templates allow us to author
Extended Backus-Normal Form (EBNF) in C++. Additional information is available at YARD_.

A simple EBNF grammar snippet::

	group      ::= '(' expression ')'
	factor     ::= integer | group
	term       ::= factor (('*' factor) | ('/' factor))*
	expression ::= term (('+' term) | ('-' term))*

is approximated using Biscuit's facilities as seen in this code snippet::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\introduction_0.ipp

Through the magic of the lazy template instantiation, these are perfectly valid types.
The production rule ``expression`` is a type that has a static member function ``parse``.
As ``parse`` will be instantiated later by Algorithms_, all you have to do is to declare a type.

Direct recurring types [#]_ also are valid::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\introduction_1.ipp

Note that left-recursions are not allowed, though compilers might detect them if templates are easy.


.. [#] ``typedef`` is not available for such usage but can define a non-recurring parser inside a function unlike ``struct``.


Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 0.97.x`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Quick Start
-----------
#. Include Biscuit headers::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\quick_start_1.ipp

#. Define your own Parser_ type::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\quick_start_2.ipp

#. Call Algorithms_ [#]_::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\quick_start_3.ipp


.. [#] An unqualified call may trigger an unintentional ADL. You must always add ``biscuit::``.



Basic Concepts
--------------


User State
^^^^^^^^^^
A ``UserState`` is any type that is passed to Algorithms_ or Ranges_ as the second argument.
Non-const rvalues are disallowed as ``UserState``.
If no object is passed to Algorithms_, this type is ``null_state_type``.


Parser
^^^^^^
A ``Parser`` is any type that has the static member function::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\basic_concept_parser.ipp


Parsing Range
^^^^^^^^^^^^^
A ``ParsingRange`` is a `Forward Range`_ that is passed to Algorithms_ or Ranges_ as the first argument and
the ``value_type`` of the `Forward Range`_ must be `Equality Comparable`__.

__ http://www.sgi.com/tech/stl/EqualityComparable.html


Parsing SubRange
^^^^^^^^^^^^^^^^^
A ``ParsingSubRange`` [#]_ is a ``boost::iterator_range<boost::range_result_iterator<ParsingRange>::type>``.


Semantic Action
^^^^^^^^^^^^^^^
A ``SemanticAction`` is a `Default Constructible`_ `Functor`_ and
the expression ``a(r, us)`` must be valid, where ``a`` is an object of type `Semantic Action`_, 
``r`` is an object of type `Parsing SubRange`_ and ``us`` is an object of type `User State`_.


Value Functor
^^^^^^^^^^^^^
A ``ValueFunctor`` is a `Default Constructible`_ `Functor`_ and
the expression ``v(us)`` must be valid, where ``v`` is an object of type `Value Functor`_ and
``us`` is an object of type `User State`_.


.. [#] `Parsing SubRange`_ is not defined as ``boost::sub_range`` for broken compilers,
       but you can catch it using ``boost::sub_range<ParsingRange>``. Note that
       ``boost::sub_range`` is not always assignable under eVC4 and VC8 because of their bugs.



Predefined Parsers
------------------
Some Parser_ templates are predefined as a means for Parser_ composition and embedding.


Primitives 
^^^^^^^^^^
The table below lists EBNF and their equivalents in Biscuit.

	==================== ======================================================= ==================================================
	EBNF (or Perl)       Biscuit                                                 Meaning
	==================== ======================================================= ==================================================
	``.``                ``any`` [#]_                                            any object
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``^``                ``begin``                                               beginning of parsing range
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``$``                ``end``                                                 end of parsing range
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A | B``            ``or_<A, B>``                                           alternation of A and B
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A B``              ``seq<A, B>``                                           sequence of A and B
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A*``               ``star<A>``                                             zero or more times, greedy
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A+``               ``plus<A>``                                             one or more times, greedy
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A?``               ``opt<A>``                                              zero or one time, greedy
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A & B``            ``and_<A, B>``                                          match A, and the matching-range matches B
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A - B``            ``minus<A, B>``                                         match A, but the matching-range doesn't match B
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``(A)``              ``capture<1, A>``                                       capture a back-reference
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\1``               ``backref<1>``                                          a previously captured back-reference
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A{n,m}``           ``repeat<A, n, m>``                                     between n and m times, greedy
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A*? B``            ``star_until<A, B>``                                    zero or more As, non-greedy, and B
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``A*? (?=B)``        ``star_before<A, B>``                                   same as ``star_until< A, before<B> >``
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``(?=A)``            ``before<A>``                                           positive look-ahead assertion
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``(?!A)``            ``not_< before<A> >``                                   negative look-ahead assertion
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``a``                ``char_<'a'>``                                          a character
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``b``                ``wchar<L'b'>``                                         a wide-character
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``c``                ``bchar<long,0x63>``                                    a type-specified character
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``Diggins``          ``chseq<'D','i','g','g','i','n','s'>``                  a string
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``MB``               ``wchseq<L'M',L'B'>``                                   a wide-string
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``MB``               ``bchseq<long,0x4d,0x42>``                              a type-specified string
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``[0-9]``            ``chrng<'0','9'>``                                      characters in range '0' through '9'
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``[abc]``            ``chset<'a','b','c'>``                                  characters 'a','b' or 'c'
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``[0-9abc]``         ``or_< chrng<'0','9'>, chset<'a','b','c'> >``           characters 'a','b','c' or in range '0' though '9'
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``[^abc]``           ``not_< chset<'a','b','c'> >`` [#]_                     not characters 'a','b' or 'c'
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``/Diggins/i``       ``ichseq<'D','i','g','g','i','n','s'>``                 a case-insensitive string, locale-insensitive
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\w``               ``alnum``                                               a word
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\W``               ``not_<alnum>``                                         not a word
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\d``               ``digit``                                               a digit
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\D``               ``not_<digit>``                                         not a digit
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\s``               ``space``                                               a space
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``\S``               ``not_<space>``                                         not a space
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``$``                ``eol``                                                 a literal newline or end of parsing range
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``???``              ``line``                                                character sequence before ``eol``
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``???``              ``identity<A>``                                         same as A, delay definition of A when deriving
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``???``              ``eps``                                                 match the empty range
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``???``              ``nothing``                                             never match anything
	==================== ======================================================= ==================================================

YARD_ and Biscuit have no back-tracking on star operations. Instead ``star_until`` or ``star_before`` are available.
The default template arity is twenty. 
If you want more arity, define ``PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS`` and ``PSTADE_BISCUIT_LIMIT_PARSER_ARITY``
before Biscuit headers. VC++7.1 limits ``PSTADE_BISCUIT_LIMIT_PARSER_ARITY`` to 64.
Note that the big arity tends to make internal compiler errors.


Literal
^^^^^^^
The C++ Standard doesn't allow you to pass a string literal to templates.
``chseq`` template parameter arity is limited. For that workaround, ``PSTADE_BISCUIT_SEQ_LITERAL`` macro is provided::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\predefined_parsers_literal.ipp

``PSTADE_BISCUIT_SEQ_LITERAL`` defines a `Parser`_ whose name is the first argument by using
the string literal that is passed as the second argument.


Actor
^^^^^
``actor`` template creates a Parser_ that triggers a `Semantic Action`_ object::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\predefined_parsers_actor.ipp

`Parsing SubRange`_ can be assigned to ``boost::sub_range<ParsingRange>`` idiomatically.
If a `Parsing Range`_ is mutable, its `Parsing SubRange`_ also is mutable.
Note that a copy of ``boost::sub_range`` is only copies of two iterators.


Directives
^^^^^^^^^^
Directives_ are also Parser_\s which contain some ports of `Boost.Spirit`_'s Directives__.

	==================== ======================================================= ==================================================
	Boost.Spirit         Biscuit                                                 Meaning
	==================== ======================================================= ==================================================
	``lexeme_d[A]``      impossible                                              turn off white space skipping
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``as_lower_d[A]``    ``as_lower<A>``                                         parsing range is transformed to lower-case
	-------------------- ------------------------------------------------------- --------------------------------------------------
	???                  ``as_filtered<A, Parser>``                              parsing range is filtered using parser
	-------------------- ------------------------------------------------------- --------------------------------------------------
	???                  ``as_transformed<A, UnaryFunction>`` [#]_               parsing range is transformed using functor
	-------------------- ------------------------------------------------------- --------------------------------------------------
	???                  ``lazy_actions<A>``                                     suppress non-intended actions by parsing twice
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``no_actions[A]``    ``no_actions<A>``                                       semantic actions not fire
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``longest_d[A|B]``   ``longest<A, B>``                                       choose the longest match
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``shortest_d[A|B]``  ``shortest<A, B>``                                      choose the shortest match
	-------------------- ------------------------------------------------------- --------------------------------------------------
	``limit_d[A]``       ``require<A, Predicate>`` [#]_                          parsing range requires predicate is constrained
	==================== ======================================================= ==================================================

.. [#] There is a debate over whether or not to define Parser_\s as class templates even if no parameters.
       If you want such parsers, define ``PSTADE_BISCUIT_CFG_NULLARY_CLASS_TEMPLATE_PARSER`` before Biscuit headers.

.. [#] ``not_`` can be applied only to one character Parser_ with a few exceptions.

.. [#] ``UnaryFunction`` requirements are the same as `boost::transform_iterator`__\'s.

.. [#] ``Predicate`` must conform to `Semantic Action`_ and the valid expression must be convertible to ``bool``.


__ http://spirit.sourceforge.net/distrib/spirit_1_8_2/libs/spirit/doc/directives.html
__ http://www.boost.org/libs/iterator/doc/transform_iterator.html



Algorithms
----------
Algorithms of Biscuit work on `Forward Range`_. 
Note that Parser_\s don't know ``value_type`` of the range.
For instance, a Parser_ ``chseq`` works properly if ``value_type`` of the
range is comparable with ``char``.


``match``
^^^^^^^^^
``biscuit::match`` returns ``true`` if a Parser_ runs through the range; otherwise ``false``::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\algorithms_match.ipp

Notice that a null-terminated string is no longer a model of Range with Boost 1.35.
``oven::null_terminate_range`` is provided for the workaround.


``search``
^^^^^^^^^^
``biscuit::search`` returns the first occurence of the matching `Parsing SubRange`_.
If not found, it returns ``boost::make_iterator_range(boost::end(r), boost::end(r))``, 
where ``r`` is an object of type `Parsing Range`_::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\algorithms_search.ipp


``parse``
^^^^^^^^^
While ``biscuit::match`` returns only whether or not to succeed,
``biscuit::parse`` returns `Parsing SubRange`_ that a Parser_ runs through.
If a parsing fails, it returns ``boost::make_iterator_range(boost::begin(r), boost::begin(r))``, 
where ``r`` is an object of type `Parsing Range`_.



Ranges
------


``filter_range``
^^^^^^^^^^^^^^^^
``filter_range`` is a `Forward Range`_ that is filtered by Parser_::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\ranges_filter_range_0.ipp

A chain of ``filter_range`` works properly::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\ranges_filter_range_1.ipp

``filter_range`` is a model of `Forward Range`_ that can be passed to Algorithms_.
That's why Biscuit doesn't provide anything like `Boost.Spirit`_'s Scanner__.

`Range adapter`__ syntax also is supported by ``filtered``::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\ranges_filter_range_2.ipp

__ http://spirit.sourceforge.net/distrib/spirit_1_8_2/libs/spirit/doc/scanner.html
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1871.html#range-adapters-part-4


``token_range``
^^^^^^^^^^^^^^^
``token_range`` is a `Forward Range`_ whose ``value_type`` is a matching `Parsing SubRange`_::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\ranges_token_range_0.ipp

Outputs::

	/* c comment no.1 */
	/* c comment no.2 */
	/* c comment no.3 */

As ``token_range`` conforms to `Forward Range`_,
``BOOST_FOREACH`` planned to be a member of `Boost`_ works properly.



Capturing
---------
``capture`` and ``backref`` create Parser_ for the capturing.
results_xxx [#]_ Algorithms_ are provided for accessing matching results after parsing::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\capturing_0.ipp

``match_results<r>``, where ``r`` is a `Parsing Range`_, conforms to
`Pair Associative Container`__ and `Unique Associative Container`__
except for their constructor expressions, whose ``key_type`` is ``int`` and
``mapped_type`` is `Parsing SubRange`_ of ``r``.

__ http://www.sgi.com/tech/stl/PairAssociativeContainer.html
__ http://www.sgi.com/tech/stl/UniqueAssociativeContainer.html


.. [#] You may want to use ``match_results`` as `User State`_, so the overloading was rejected.



Dynamics
--------
Biscuit doesn't make any assumption about ``value_type`` of `Parsing Range`_, but 
non-type template parameters are so limited.
What if ``value_type`` of `Parsing Range`_ is not ``char`` but Screamer type of your dungeon game?
What if matching patterns are loaded on runtime for your mouse-gesture program?
The only way is to extract values from `User State`_.


``valseq``
^^^^^^^^^^
``valseq`` makes a sequential Parser_ from `Value Functor`_\s::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\valseq_0.ipp


``valset``
^^^^^^^^^^
``valset`` makes an alternation Parser_ from `Value Functor`_\s::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\valset_0.ipp


``seq_range``
^^^^^^^^^^^^^
``seq_range`` is more flexible than `valseq`_.
``seq_range<V>`` makes a sequential Parser_, where ``V`` is a `Value Functor`_
whose function call expression must be, whether reference or not, a `Forward Range`_ whose ``value_type`` is comparable with `Parsing Range`_'s::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\seq_range_0.ipp


``set_range``
^^^^^^^^^^^^^
``set_range`` is provided in a similar way::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\set_range_0.ipp



Debugging
---------
Biscuit emulates `Boost.Spirit`_'s debugging__::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\debugger_0.ipp

__ http://spirit.sourceforge.net/distrib/spirit_1_8_2/libs/spirit/doc/debugging.html

``debugger`` Parser_ uses the type-name of the first argument for outputs 
which automatically disappear on release-compile.

Outputs::

	1+2
	struct calculator_debug::start: "1+2"
	  struct calculator_debug::expression: "1+2"
	    struct calculator_debug::term: "1+2"
	      struct calculator_debug::factor: "1+2"
	        struct calculator_debug::integer: "1+2"
	push    1
	        /struct calculator_debug::integer: "+2"
	      /struct calculator_debug::factor: "+2"
	    /struct calculator_debug::term: "+2"
	    struct calculator_debug::term: "2"
	      struct calculator_debug::factor: "2"
	        struct calculator_debug::integer: "2"
	push    2
	        /struct calculator_debug::integer: ""
	      /struct calculator_debug::factor: ""
	    /struct calculator_debug::term: ""
	popped 1 and 2 from the stack. pushing 3 onto the stack.
	  /struct calculator_debug::expression: ""
	/struct calculator_debug::start: ""
	-------------------------
	Parsing succeeded
	result = 3
	-------------------------



Error Handling
--------------
Biscuit emulates `Boost.Spirit`_'s `Error Handling`__::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\error_handling_0.ipp

__ http://spirit.sourceforge.net/distrib/spirit_1_8_3/libs/spirit/doc/error_handling.html

`Semantic Action`_\s aside, the exception-safety of Biscuit depends on `Parsing Range`_.
In turn, if operators of the `Parsing Range`_ provide the basic exception-safety, Biscuit provides it.
If the operators provide the strong exception-safety, Biscuit provides it.



Bake in Oven
------------
`Oven`__ is the `Boost.Range`_ extension library.
It provides some predefined ranges for Biscuit::

	D:\p-stade.sourceforge.net\pstade\libs\biscuit\doc\inline\bake_biscuit_in_oven_0.ipp

__ OvenR_



Points of Interest
------------------
YARD_ and Biscuit are the examples of "composing inlined algorithms" that `Boost.MPL TODO list`__ shows.
Biscuit parsers are expression templates that are made by hand, which tend to make smaller executables.
`Boost.Spirit`_ and `Boost.Xpressive`_ automatically create expression templates by using operator overloads.
In my opinion, such overloads couldn't increase readability as expected.

__ http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?MPL_TODO_List



References
----------
- `Forum at Code Project`__
- `P-Stade`_
- `Christopher Diggins`_
- YARD_
- `A Regular Expression Tokenizer using the YARD Parser`__
- `Parsing XML in C++ using the YARD Parser`__
- `C++ Template Metaprogramming`_
- `C++ Templates - The Complete Guide`_
- `Boost C++ Libraries`_
- `Boost.MPL`_
- `Boost.Range`_
- `Boost.RangeEx`_
- `Boost.Spirit`_
- `Boost.Xpressive`_
- `Hassle Free Clip Art.com`_

__ http://www.codeproject.com/cpp/biscuit.asp
__ http://www.codeproject.com/cpp/yard-tokenizer.asp
__ http://www.codeproject.com/cpp/yard-xml-parser.asp



Release Notes
-------------

Version 1.02.0 - 1.02.5
^^^^^^^^^^^^^^^^^^^^^^^
- Namespace moved to ``pstade::biscuit``.
- Updated the document.
- Used ``iterator_range`` as ``match_results`` for broken VC8.
- Added tests.
- Fixed a bug of ``capture`` when directives_ applied.
- Fixed a bug of ``biscuit::match``.
- Added Boost.Jam files.
- Added workaround for the forwarding problem.
- Fixed fatal bugs of ``token_range``.

Version 1.02.6
^^^^^^^^^^^^^^
- Added ``PSTADE_BISCUIT_SYMBOL``.

Version 1.02.7
^^^^^^^^^^^^^^
- Rearranged `Basic Concepts`_.

Version 1.02.8
^^^^^^^^^^^^^^
- Renamed ``PSTADE_BISCUIT_SYMBOL`` to ``PSTADE_BISCUIT_SEQ_LITERAL``.
- Fixed a few bugs.
- Deprecated ``biscuit::iterate``.


.. include:: ../../doc/refs.rst

