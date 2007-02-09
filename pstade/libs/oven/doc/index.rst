++++++++++++++++++++++
The Oven Range Library
++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: Shunsuke Sogame
:Contact: pstade.mb@gmail.com
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.93.3



.. epigraph::

	"*Oh Paulie!*"
	
	-- Adrian



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
Oven provides an experimental Range Adaptor implementation of `Range Library Proposal`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\introduction.ipp

All the types and functions are defined in ``namespace pstade::oven`` at ``<pstade/oven.hpp>``
unless otherwise specified.


Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 1.02.0`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition SP1
- Microsoft Visual C++ .NET Version 7.1 SP1
- GCC 3.4.4


Specification
-------------
This document is based on the following specifications.

- ``rng``: any range
- ``fwdRng``: any `Forward Range`_
- ``biRng``: any `Bidirectional Range`_
- ``rndRng``: any `Random Access Range`_
- ``pred``: any `Predicate`_
- ``rfun``: any `Function Object`_ which can be used with ``boost::result_of``.
- If ``xxx(a1,..,aN)`` is a valid expression and ``xxx`` is not a type name, ``xxx`` is a `Function Object`_
  whose type name is ``op_xxx`` to support ``boost::result_of`` and Boost.Lambda.

Note that the function type is not supported as ``rfun``. Instead, add ``&`` to make it a function **pointer**::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\specification.ipp

All the ranges Oven defines are InputStreamable and OutputStreamable if ``<pstade/oven/io.hpp>`` is included.


Range Algorithms
----------------
Oven provides some range-based algorithms.
``<pstade/oven/functions.hpp>`` includes all the following functions unless otherwise specified.


STL Algorithms
^^^^^^^^^^^^^^
Oven has all the range-based STL algorithms, which are ported from `Boost.RangeEx`_ with some compiler workarounds::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\stl_algorithms.ipp


- Header: ``<pstade/oven/algorithm.hpp>`` and ``<pstade/oven/numeric.hpp>``
- Valid expression: ``algo(rng,a0,a1,..,aN)``, where ``algo`` is a `Function Object`_.
- Precondition: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,..,aN)`` is a valid expression, where ``algo`` is one of the STL algorithms.
- Returns: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,..,aN)``


``adapted_to/to_base``
^^^^^^^^^^^^^^^^^^^^^^
``adapted_to`` gets the ``base_type`` iterator of adapted iterators::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\adapted_to_base.ipp


- Header: ``<pstade/oven/adapted_to_base.hpp>``
- Valid expression: ``base = oven::adapted_to<BaseIter>(it);`` or ``BaseIter base = it|to_base;``
- Precondition: The type of ``base`` is ``BaseIter``, and ``it`` is an adapted iterator.

``to_base`` adds the automatic type deduction to ``adapted_to``.


``begin/end``
^^^^^^^^^^^^^
``begin/end`` is a pipable version of ``boost::begin/end``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\begin_end.ipp


- Header: ``<pstade/oven/begin_end.hpp>``
- Valid expression: ``rng|begin`` and ``rng|end``
- Precondition: ``boost::begin(rng)`` and ``boost::end(rng)`` is a valid expression.
- Returns: ``boost::begin(rng)`` and ``boost::end(rng)`` respectively.


``compile``
^^^^^^^^^^^
Pending...


``copied``
^^^^^^^^^^
``copied`` adds the automatic type deduction to `copy_range`_ which
calls the range constructor of the STL Sequences::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copied.ipp

.. _copy_range: http://www.boost.org/libs/range/doc/utility_class.html#copy_range


- Header: ``<pstade/oven/copy_range.hpp>``
- Valid expression: ``Seq seq = rng|copied;``
- Precondition: ``Seq seq = boost::copy_range<Seq>(rng);`` is a valid expression.
- Effect: ``Seq seq = boost::copy_range<Seq>(rng);``

Note that ``Seq seq(rng|copied);`` is not a valid expression.


``distance``
^^^^^^^^^^^^
The upcoming `Boost.Range`_ will replace ``boost::size`` by ``boost::distance``.
``oven::distance`` that is the same as ``boost::distance`` makes your code portable::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\distance.ipp


- Header: ``<pstade/oven/distance.hpp>``
- Valid expression: ``distance(rng);``
- Precondition: ``std::distance(boost::begin(rng),boost::end(rng));`` is a valid expression.
- Returns: ``std::distance(boost::begin(rng),boost::end(rng))``


``equals``
^^^^^^^^^^
``equals`` is the range-based ``std::equal`` that takes two ranges as the arguments.
Note that the size of two ranges is also checked out::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\equals.ipp


- Header: ``<pstade/oven/equals.hpp>``
- Valid expression: ``equals(rng1,rng2);``
- Precondition: ``equal(rng1,boost::begin(rng2));`` is a valid expression.
- Returns: ``true`` if and only if the ``oven::equal(rng1,boost::begin(rng2))`` and ``boost::size(rng1) == boost::size(rng2)`` returns ``true``.


Utilities
---------
Some helper function objects are given to fill the gap between Oven and other libraries.


``innumerable``
^^^^^^^^^^^^^^^
As discribed below, the function object `generation`_ needs is slightly different from
the Generator concept defined by the Standard.
``innumerable`` turns the Generator function object into the Standard conforming one,
which creates an infinite range, working with `generation`_.

- Header: ``<pstade/oven/generation.hpp>``
- Valid expression: ``innumerable(rfun)``
- Returns: A `generation`_ conforming function object.


``regular``
^^^^^^^^^^^
Boost.Lambda functors are neither DefaultConstructible nor CopyAssignable.
An iterator holding such a functor cannot conform to even InputIterator.
``regular`` converts it to comfortable one for iterators.

- Header: ``<pstade/oven/regular.hpp>``
- Valid expression: ``regular(lambdaFunctor)``
- Returns: A `Function Object`_ which is DefaultConstructible and CopyAssignable.

In principle, call ``regular`` before a lambda functor is passed to `Range Adaptors`_.


``shared_regular``
^^^^^^^^^^^^^^^^^^
``shared_regular`` converts a non-Copyable function object type to Copyable one.

- Header: ``<pstade/oven/regular.hpp>``
- Valid expression: ``shared_regular(p)``.
- Precondition: ``boost::shared_ptr`` is constructible from ``p``.
- Returns: A `Function Object`_ which is DefaultConstructible and CopyAssignable.



Ranges
------
Oven provides some predefined range types.
``<pstade/oven/ranges.hpp>`` includes every range header unless otherwise specified.


``any_range``
^^^^^^^^^^^^^
Though Oven supports ``boost::result_of``, it is sometimes cumbersome to get the type of
the adapted range. ``any_range`` behaves as the type erasure of ranges::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\any_range.ipp


- Header: ``<pstade/oven/any_range.hpp>``
- Valid expression: ``any_range<Reference,TraversalTag> any_(rng);`` and ``any_range<Reference,TraversalTag> any_ = rng;``
  , where the iterators of ``any_`` are ``Interoperatable`` if and only if ``rng``\s are the same type.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `any_iterator`__

__ http://thbecker.net/free_software_utilities/type_erasure_for_cpp_iterators/start_page.html


``array_range``
^^^^^^^^^^^^^^^
``array_range`` is a non-Copyable `Random Access Range`_ which delivers
a range presentation of dynamically allocated arrays::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\array_range.ipp


- Header: ``<pstade/oven/array_range.hpp>``
- Valid expression: ``array_range<T> rng(sz);``
- Precondition: ``new T[sz];`` is a valid expression.


``directory_range``
^^^^^^^^^^^^^^^^^^^
``directory_range`` is a `Single Pass Range`_ which accesses the contents of a directory::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directory_range.ipp


- Header: ``<pstade/oven/directory_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``directory_range rng(p);`` and ``wdirectory_range wrng(wp);``
- Precondition: The type of ``p`` is ``boost::filesystem::path`` and
  the type of ``wp`` is ``boost::filesystem::wpath``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `directory_iterator`__

__ http://www.boost.org/libs/filesystem/doc/operations.htm#directory_iterator


``empty_range``
^^^^^^^^^^^^^^^
``empty_range`` is a `Random Access Range`_ which is always empty::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\empty_range.ipp
	

- Header: ``<pstade/oven/empty_range.hpp>``
- Valid expression: ``empty_range<T> rng;``


``file_range``
^^^^^^^^^^^^^^
``file_range`` is a constant `Random Access Range`_ for files::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\file_range.ipp


- Header: ``<pstade/oven/file_range.hpp>``
- Valid expression: ``file_range<C> rng;`` and ``rng.is_open();``
- Precondition: ``boost::spirit::file_iterator<C>`` is a valid expression.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `file_iterator`__

__ http://www.boost.org/libs/spirit/doc/file_iterator.html

The member ``is_open()`` returns ``true`` if and only if the file opening is succeeded.
If ``is_open()`` is not ``true``, the range is empty.


Range Makers
------------
Oven provides some predefined functions which produce a range.
All the range returned from the following makers are CopyConstructible and Inheritable.
``<pstade/oven/functions.hpp>`` includes every maker header unless otherwise specified.


``as_array``
^^^^^^^^^^^^
The current Boost.Range regards char array as literal, which ``as_array`` works around.

- Header: ``<pstade/oven/as_array.hpp>``
- Valid expression: ``as_array(arr)`` and ``arr|as_array``
- Effect: same as `TR2 as_array`__

__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-array


``as_c_str``
^^^^^^^^^^^^
``as_c_str`` makes a `Random Access Range`_ from null-terminated c-style string::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\as_c_str.ipp


- Header: ``<pstade/oven/as_c_str.hpp>``
- Valid expression2: ``as_c_str(x)`` and ``x|as_c_str``.
- Returns: If  ``x`` is convertible to a char pointer, ``[x,x+strlen(psz))``; otherwise, ``[boost::begin(x),oven::find(x,0))``.


``as_literal``
^^^^^^^^^^^^^^
``as_literal`` makes a `Random Access Range`_ from character array.
``as_literal`` doesn't support any pointer type but array type. So it is safe and fast. Compare it with ``as_c_str``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\as_literal.ipp

- Header: ``<pstade/oven/as_literal.hpp>``
- Valid expression1: ``as_literal(x)`` and ``x|as_literal``
- Returns:If ``x`` is an array,  ``[&x[0],&x[0]+sz-1)`` where ``sz`` is the size of ``arr``; otherwise, ``x`` as is.

Note that ``as_literal`` doesn't use ``strlen``. `TR2 as_literal`__ does.

__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-literal


``as_single``
^^^^^^^^^^^^^
``as_single`` makes a `Random Access Range`_ which delivers a range presentation of one object::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\as_single.ipp


- Header: ``<pstade/oven/as_single.hpp>``
- Valid expression: ``as_single(v)`` and ``v|as_single``
- Returns: A range which behaves as if it were ``[&v,&v+1)``.


``as_shared_single``
^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/as_single.hpp>``
- Valid expression: ``as_shared_single(p)`` and ``p|as_shared_single``
- Precondition: ``boost::shared_ptr`` is constructible from ``p``.
- Returns: A range which behaves as if it were ``[&*p,&*p+1)``.


``counting``
^^^^^^^^^^^^
``counting`` introduces the replacement of ``for`` loop::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\counting.ipp


- Header: ``<pstade/oven/counting.hpp>``
- Valid expression: ``counting(n, m)``, where ``n`` and ``m`` is Incrementable.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `counting_iterator`__

__ http://www.boost.org/libs/iterator/doc/counting_iterator.html


``generation``
^^^^^^^^^^^^^^^^^^
``generation`` returns a range whose iterators were originally written as `generator_iterator`__::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\generation.ipp

__ http://www.boost.org/libs/utility/generator_iterator.htm


- Header: ``<pstade/oven/generation.hpp>``
- Valid expression: ``generation(rfun)``
- Precondition:``rfun`` call returns initialized ``boost::optional`` if range is not end; Otherwise, returns uninitialized one.
- Returns: A `Single Pass Range`_ whose values are the results of invoking ``rfun``.

If you have a Standard conforming Generator, you can convert it to ``generation`` conforming one by using `innumerable`_.


``indexing``
^^^^^^^^^^^^
Pending...


``iteration``
^^^^^^^^^^^^^^^^^
``iteration`` makes an infinite range where the first item is calculated by applying
the function on the first argument, the second item by applying the function on the previous result and so on::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\iteration.ipp
	

- Header: ``<pstade/oven/iteration.hpp>``
- Valid expression: ``iteration(x,fun)``
- Returns: An infinite `Single Pass Range`_ of repeated applications of ``fun`` to ``x``.


``recursion``
^^^^^^^^^^^^^
``recursion``, collaborating with `any_range`_, creates a recursive range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\recursion.ipp


- Header: ``<pstade/oven/recursion.hpp>``
- Valid expression: ``recursion(anyRng)``, where ``anyRng`` is an ``any_range`` object.
- Returns: An infinite range up to  `Bidirectional Range`_.


``repeated``
^^^^^^^^^^^^
``repeated`` makes a `Random Access Range`_ where all values are the first argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\repeated.ipp

- Header: ``<pstade/oven/repeated.hpp>``
- Valid expression: ``v|repeated(c)`` and ``make_repeated(v,c)``
- Returns: A range which behaves as if it were ``as_single(v)|cycled(c)``.


``stream_input``
^^^^^^^^^^^^^^^^
``stream_input`` makes a `Single Pass Range`_ from ``std::cout`` etc::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\stream_input.ipp


- Valid expression: ``oven::stream_input<V>(stm)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `istream_iterator`__

__ http://www.sgi.com/tech/stl/istream_iterator.html


``streambuf_input``
^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/stream_input.hpp>``
- Valid expression: ``oven::streambuf_input(stm)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``istreambuf_iterator``



Range Adaptors
--------------
A Range Adaptor delivers an altered presentation of one or more underlying ranges.
Range Adaptors are lazy, meaning that their elements are only computed on demand.
The underlying ranges are not modified.
Additional information is available at `Range Library Proposal`_.
``<pstade/oven/adaptors.hpp>`` includes all the following Range Adaptors unless otherwise specified.

Note that all the range returned from the following adaptors are CopyConstructible and Inheritable.
Also, if ``a0|xxx(a1,..,aN)`` is a valid expression, then  ``make_xxx(a0,..,aN)`` too is a valid expression
which has the same effect.


``adjacent_filtered``
^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/adjacent_filtered.hpp>``
- See: `Range Library Proposal`_.


``adjacent_transformed``
^^^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/adjacent_transformed.hpp>``
- Valid expression: ``fwdRng|adjacent_transformed(rfun)``
- Precondition: ``boost::empty(fwdRng) == false``
- Returns: A range where adjacent pairs of ``fwdRng`` are transformed by using ``rfun``.


``advanced``
^^^^^^^^^^^^
- Header: ``<pstade/oven/advanced.hpp>``
- Valid expression: ``fwdRng|advanced(d1,d2)``
- Precondition: ``fwdRng`` must be a `Bidirectional Range`_ if either ``d1`` or ``d2`` is negative.
- Returns: ``[boost::next(boost::begin(fwdRng),d1),boost::next(boost::end(fwdRng),d2))``.


``always``
^^^^^^^^^^^^^
``always`` returns a range which does not change as the base range vary::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\always.ipp


- Header: ``<pstade/oven/always.hpp>``
- Valid expression: ``unusedRng|always(rng)``
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``appended``
^^^^^^^^^^^^
``appended`` returns a range which is appended with its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\appended.ipp


- Header: ``<pstade/oven/appended.hpp>``
- Valid expression: ``rng|appended(v)``
- Returns: A range which behaves as if it were ``rng|jointed(as_single(v))``.


``applied``
^^^^^^^^^^^
``applied``, taking a `Function Object`_ which represents an algorithm, creates the range adaptor::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\applied.ipp


- Header: ``<pstade/oven/applied.hpp>``
- Valid expression1: ``rng|applied(f1,f2)``, where ``f1(rng)`` and ``f2(rng)`` must return iterators that are convertible to ``rng``\'s.
- Valid expression2: ``rng|applied(f)``, where ``f(rng)`` must return a range whose iterators are convertible to  ``rng``\'s.
- Returns: ``[f1(rng),f2(rng))``, or ``[boost::begin(r),boost::end(r))`` where ``r = f(rng)``, respectively.


``broken_into``
^^^^^^^^^^^^^^^
``broken_into`` is the adaptor version of ``boost::tokenizer``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\broken_into.ipp


- Header: ``<pstade/oven/broken_into.hpp>``
- Valid expression: ``rng|broken_into<t>(f)``, where ``f`` is a ``TokenizerFunction``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::token_iterator``.


``checked``
^^^^^^^^^^^
``checked`` adds the bounds checking ability to the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\checked.ipp


- Header: ``<pstade/oven/checked.hpp>``
- Valid expression: ``rng|checked``
- Effect: Throws ``check_error`` derived from ``std::range_error`` if iterators go out of ``rng``.
- Returns: ``[boost::begin(rng),boost::end(rng))``


``cleared``
^^^^^^^^^^^
``cleared`` returns a range which is always empty::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\cleared.ipp


- Header: ``<pstade/oven/cleared.hpp>``
- Valid expression: ``rng|cleared``
- Returns: ``[boost::end(rng),boost::end(rng))``.


``concatenated``
^^^^^^^^^^^^^^^^
``concatenated`` accepts a range whose ``value_type`` is a range and concatenates them::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\concatenated.ipp

- Header: ``<pstade/oven/concatenated.hpp>``
- Valid expression: ``rngs|concatenated``
- Specification: ``SegmentIterator`` is an iterator of ``rngs``, and ``LocalIterator`` is an iterator of the range which the dereference of ``SegmentIterator`` returns.
- Precondition: The ``LocalIterator`` must be valid after copying of ``SegmentIterator``.



``constants``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/constants.hpp>``
- Valid expression: ``rng|constants``
- Returns: ``[boost::end(rng),boost::end(rng))`` whose iterators are constant.


``const_lvalues``
^^^^^^^^^^^^^^^^^
``const_lvalues`` turns the associated ``reference`` type of the base range into reference type,
which makes iterators of `Forward Range`_ conform to Forward Iterator.
Thus, STL that doesn't know traversal concepts can choose effective algorithms.


- Header: ``<pstade/oven/const_lvalues.hpp>``
- Valid expression: ``rng|const_lvalues``
- Precondition: ``value_type`` of ``rng`` is CopyConstructible, Assignable and DefaultConstructible.
- Returns: ``[boost::begin(rng),boost::end(rng))`` whose iterators are constant.


``copied_out``
^^^^^^^^^^^^^^
``copied_out`` makes a side-effect that copies the base range to its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copied_out.ipp


- Header: ``<pstade/oven/copied_out.hpp>``
- Valid expression: ``rng|copied_out(it)``
- Precondition: ``oven::copy(rng,it)`` is a valid expression.
- Effect: ``oven::copy(rng,it)``
- Returns: ``rng``.


``cycled``
^^^^^^^^^^^^
``cycled`` creates a circular range from the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\cycled.ipp


- Header: ``<pstade/oven/cycled.hpp>``
- Valid expression: ``rng|cycled(n)``
- Returns: A constant range that repeats ``[boost::begin(rng),boost::end(rng))`` ``n`` times.


``delimited``
^^^^^^^^^^^^^
``delimited`` adds a delimiter to the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\delimited.ipp


- Header: ``<pstade/oven/delimited.hpp>``
- Valid expression: ``rngs|delimited(delim)``, where ``delim`` is a Range to specify the delimiter.
- Returns: A range which behaves as if it were ``rngs|transformed(with)|concatenated``, where ``with`` is a `Function Object`_ which calls ``make_jointed`` to joint ``delim``.

Note that ``delimited`` prepends the delimiter. ``dropped`` is useful to remove it.


``directed``
^^^^^^^^^^^^
``directed`` returns a range whose values are iterators of the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directed.ipp


- Header: ``<pstade/oven/directed.hpp>``
- Valid expression: ``rng|directed``
- Returns: A range which behaves as if it were ``counting(boost::begin(rng),boost::end(rng))``.


``dropped``
^^^^^^^^^^^
``dropped`` returns the suffix of the base range after the first ``n`` elements::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped.ipp


- Header: ``<pstade/oven/dropped.hpp>``
- Valid expression: ``rng|dropped(n)``
- Precondition: ``0 <= n``
- Returns: ``[boost::next(boost::begin(rng),std::min(n,distance(rng))),boost::end(rng))``


``dropped_while``
^^^^^^^^^^^^^^^^^
``dropped_while`` returns the remaining suffix of the base range of elements that satisfy `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped_while.ipp


- Header: ``<pstade/oven/dropped_while.hpp>``
- Valid expression: ``rng|dropped_while(pred)``
- Returns: ``[oven::find_if(rng, not_(pred)),boost::end(rng))``


``filtered``
^^^^^^^^^^^^
``filtered`` returns a range which is filtered by using a `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\filtered.ipp

Note that a non-assignable lambda functor makes ``filtered`` non-conforming, so
it needs `regular`_ to be applied before it is passed.


- Header: ``<pstade/oven/filtered.hpp>``
- See: `Range Library Proposal`_.


``firsts``
^^^^^^^^^^
- Header: ``<pstade/oven/firsts.hpp>``
- Valid expression: ``rng|firsts``
- Returns: A range which behaves as if it were ``rng|map_keys``.


``got_at``
^^^^^^^^^^
Pending...

- Header: ``<pstade/oven/got_at.hpp>``
- Valid expression: ``rng|got_at<N>()`` or ``rng|got_at_c<N>()``, where ``value_type`` of ``rng`` is a Fusion Sequence.


``identities``
^^^^^^^^^^^^^^
``identities`` returns a range which is identical to the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\identities.ipp


- Header: ``<pstade/oven/identities.hpp>``
- Valid expression: ``rng|identities`` and ``rng|identities(trv)``, where ``trv`` is a traversal tag object.
- Precondition: ``rng``\'s traversal tag is convertible to ``trv``.
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``indirected``
^^^^^^^^^^^^^^
``indirected`` adapts the base range by applying an extra dereference inside of ``operator*()``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\indirected.ipp


- Header: ``<pstade/oven/indirected.hpp>``
- See: `Range Library Proposal`_.


``jointed``
^^^^^^^^^^^
``jointed`` returns a range which is jointed with its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\jointed.ipp


- Header: ``<pstade/oven/jointed.hpp>``
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``reference`` type of ``rng2`` is convertible to ``rng1``\'s without creating a rvalue.
- Returns: A range that joints ``[boost::begin(rng1),boost::end(rng1))`` and ``[boost::begin(rng2),boost::end(rng2))``.


``map_keys``
^^^^^^^^^^^^
``map_keys`` returns a range whose values are the keys of the base associative container::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_keys.ipp


- Header: ``<pstade/oven/map_keys.hpp>``
- See: `Range Library Proposal`_.


``map_values``
^^^^^^^^^^^^^^
``map_values`` returns a range whose values are the mapped values of the base associative container::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_values.ipp


- Header: ``<pstade/oven/map_values.hpp>``
- See: `Range Library Proposal`_.


``matches``
^^^^^^^^^^^
- Header: ``<pstade/oven/matches.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|matches(re)`` or ``biRng|matches(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::regex_iterator``.


``memoized``
^^^^^^^^^^^^
``memoized`` returns a range whose values are cached for speed, preparing for repeated dereferences.
Note that ``memoized`` can return a `Forward Range`_ even if the base range is a `Single Pass Range`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\memoized.ipp


- Header: ``<pstade/oven/memoized.hpp>``
- Valid expression: ``rng|memoized``
- Precondition: ``rng`` is referentially transparent.
- Returns: A `Forward Range`_ whose values are memoized.


``merged``
^^^^^^^^^^
``merged`` combines two sorted ranges into a single sorted range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\merged.ipp


- Header: ``<pstade/oven/merged.hpp>``
- Valid expression: ``rng1|merged(rng2)`` and ``rng1|merged(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant range up to `Forward Range`_ which behaves as if they were made by ``std::merge``.


``permuted``
^^^^^^^^^^^^
- Header: ``<pstade/oven/permuted.hpp>``
- Valid expression: ``rndRng|permuted(rng)``
- Precondition: ``rng`` is a range of the indices of ``rndRng``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::permutation_iterator``.


``pointed``
^^^^^^^^^^^
``pointed`` provides an interface to have a conversation with legacy APIs::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\pointed.ipp


- Header: ``<pstade/oven/pointed.hpp>``
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is a template instantiation of ``std::vector``.
- Returns:  ``[&*boost::begin(vec),&*boost::begin(vec)+oven::distance(vec))`` if ``vec`` is not empty; otherwise, ``[0,0)``.


``popped``
^^^^^^^^^^
- Header: ``<pstade/oven/popped.hpp>``
- Valid expression: ``fwdRng|popped``
- Precondition: ``boost::empty(fwdRng) == false``
- Returns: ``[boost::begin(fwdRng),boost::next(boost::begin(fwdRng),oven::distance(fwdRng)-1))``


``prepended``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/prepended.hpp>``
- Valid expression: ``rng|prepended(v)``
- Returns: A range which behaves as if it were ``as_single(v)|jointed(rng)``.


``reversed``
^^^^^^^^^^^^
- Header: ``<pstade/oven/reversed.hpp>``
- See: `Range Library Proposal`_.


``rotated``
^^^^^^^^^^^
- Header: ``<pstade/oven/rotated.hpp>``
- Valid expression: ``fwdRng|rotated(fun)``
- Returns: ``[fun(fwdRng),boost::end(fwdRng))|jointed([boost::begin(fwdRng),fun(fwdRng)))``


``scanned``
^^^^^^^^^^^
``scanned`` is similar to ``oven::accumulate``, but returns a range of successive reduced values from the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\scanned.ipp


- Header: ``<pstade/oven/scanned.hpp>``
- Valid expression: ``rng|scanned(init,fun)``, where the type of ``init`` is DefaultConstructible, CopyConstructible and CopyAssignable.
- Precondition: ``fun(s,r)`` is a valid expression, where the type of ``s`` is the same as ``init`` and ``r`` is the iterator dereference of ``rng``.
- Returns: A range up to `Forward Range`_ which behaves as if it were made by ``std::partial_sum``.


``seconds``
^^^^^^^^^^^
- Header: ``<pstade/oven/seconds.hpp>``
- Valid expression: ``rng|seconds``
- Returns: A range which behave as if it were ``rng|map_values``.


``set_cap``
^^^^^^^^^^^
- Header: ``<pstade/oven/set_cap.hpp>``
- Valid expression: ``rng1|set_cap(rng2)`` and ``rng1|set_cap(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant range up to `Forward Range`_ which behaves as if they were made by ``std::set_intersection``.


``set_cup``
^^^^^^^^^^^
- Header: ``<pstade/oven/set_cup.hpp>``
- Valid expression: ``rng1|set_cup(rng2)`` and ``rng1|set_cup(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant range up to `Forward Range`_ which behaves as if they were made by ``std::set_union``.


``set_delta``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/set_delta.hpp>``
- Valid expression: ``rng1|set_delta(rng2)`` and ``rng1|set_delta(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant range up to `Forward Range`_ which behaves as if they were made by ``std::set_symmetric_difference``.


``set_minus``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/set_minus.hpp>``
- Valid expression: ``rng1|set_minus(rng2)`` and ``rng1|set_minus(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant range up to `Forward Range`_ which behaves as if they were made by ``std::set_difference``.


``shared``
^^^^^^^^^^
``shared``, taking a pointer to heap-allocated range, makes a range whose iterators manage its lifetime::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\shared.ipp

- Header: ``<pstade/oven/shared.hpp>``
- Valid expression: ``p|shared``
- Precondition: ``boost::shared_ptr`` is constructible from ``p``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in `shared_container_iterator`__.

__ http://www.boost.org/libs/utility/shared_container_iterator.html

You can find a more elaborate example at ``<pstade/oven/sorted.hpp>``.


``sliced``
^^^^^^^^^^
``sliced`` provides the column view of the base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\sliced.ipp

- Header: ``<pstade/oven/sliced.hpp>``
- Valid expression: ``rndRng|sliced(start,stride)``
- Precondition: ``d == 0 || d % stride == 0`` and ``0 <= start && start < stride``, where ``d = oven::distance(rndRng);``

Note that this effect is different from `Range Library Proposal`_\'s, which is the role of `advanced`_ or `window`_.


``string_found``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/string_found.hpp>``
- Valid expression: ``rng|string_found(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::algorithm::find_iterator``.


``string_split``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/string_split.hpp>``
- Valid expression: ``rng|string_split(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::algorithm::split_iterator``.


``taken``
^^^^^^^^^
``taken``, applied to the base range, returns the prefix of the range of length ``n``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken.ipp


- Header: ``<pstade/oven/taken.hpp>``
- Valid expression: ``rng|taken(n)``
- Precondition: ``0 <= n``
- Returns: A range up to `Forward Range`_ which behaves as if it were ``[boost::begin(rng),boost::next(boost::begin(rng),std::min(n, distance(rng))))``.

``taken_while``
^^^^^^^^^^^^^^^
``taken_while``, applied to a `Predicate`_ and the base range, returns the longest
prefix (possibly empty) of the range of elements that satisfy `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken_while.ipp


- Header: ``<pstade/oven/taken_while.hpp>``
- Valid expression: ``rng|taken_while(pred)``
- Returns: A range up to `Forward Range`_ which behaves as if it were ``[boost::begin(rng),oven::find_if(rng,not_(pred)))``


``tokenized``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/tokenized.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- See: `Range Library Proposal`_.


``transformed``
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/transormed.hpp>``
- Valid expression: ``rng|transformed(rfun)``
- See: `Range Library Proposal`_.


``uniqued``
^^^^^^^^^^^
- Header: ``<pstade/oven/uniqued.hpp>``
- See: `Range Library Proposal`_.


``unzipped``
^^^^^^^^^^^^
``unzipped`` reverses ``zipped``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\unzipped.ipp


- Header: ``<pstade/oven/unzipped.hpp>``
- Valid expression: ``tuples|unzipped``, where ``tuples`` is a range whose value_type is ``boost::tuple``.
- Returns: A ``boost::tuple`` whose elements are unzipped ranges.


``utf8_decoded``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/utf8_decoded.hpp>``
- Valid expression: ``biRng|utf8_decoded``
- Returns: A `Bidirectional Range`_ whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.


``window``
^^^^^^^^^^
- Header: ``<pstade/oven/window.hpp>``
- Valid expression: ``fwdRng|window(n,m)``
- Returns: ``[boost::next(boost::begin(rng),n),boost::next(boost::begin(rng),m))``.


``with_position``
^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/with_position.hpp>``
- Valid expression: ``rng|with_position``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::position_iterator``.


``xpressive_matches``
^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_matches.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_matches(re)`` or ``biRng|xpressive_matches(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_iterator``.


``xpressive_tokenized``
^^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_tokenized.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_tokenized(re)`` or ``biRng|xpressive_tokenized(re,subMatches,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_token_iterator``.


``zipped``
^^^^^^^^^^
``zipped`` takes a tuple of ranges and returns a range of corresponding tuples.
If one input range is short, excess elements of the longer range are discarded::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\zipped.ipp


- Header: ``<pstade/oven/zipped.hpp>``
- Valid expression: ``rngs|zipped``, where ``rngs`` is a ``boost::tuple`` of ranges.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::zip_iterator``.


``zipped_with``
^^^^^^^^^^^^^^^
``zipped_with`` generalises ``zipped`` by zipping with the `Function Object`_,
given as the first argument, instead of a tupling::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\zipped_with.ipp


- Header: ``<pstade/oven/zipped_with.hpp>``
- Valid expression: ``rngs|zipped_with(rfun)``, where ``rngs`` is a ``boost::tuple`` of ranges.
- Precondition1: The arity of ``rfun`` is the length of ``rngs``.
- Returns: A range whose values are zipped by using ``rfun``.



Output Iterator Adaptors
------------------------

``to_counter``
^^^^^^^^^^^^^^
``to_counter`` takes an initial count and increments it every output.
`adapted_to/to_base`_ can extract the result of the counting::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\to_counter.ipp


- Header: ``<pstade/oven/to_counter.hpp>``
- Valid expression: ``to_counter(i)``, where ``i`` is an ``Incrementable``.
- Returns: An ``OutputIterator`` which counts the output.


``to_function``
^^^^^^^^^^^^^^^
``to_function`` returns an ``OutputIterator`` which is a port of `boost::function_output_iterator`__
with some workarounds.

__ http://www.boost.org/libs/iterator/doc/function_output_iterator.html

- Header: ``<pstade/oven/to_function.hpp>``
- Valid expression: ``to_function(fun)``
- Returns: An ``OutputIterator`` which behaves as if it were ``boost::function_output_iterator``.


``to_stream``
^^^^^^^^^^^^^
``to_stream`` returns an ``OutputItertor`` which is a shorthand version of ``std::ostream_iterator``.
It needs no an explicit template parameter to specify the ``value_type`` to output,
but one precondition below must be kept. Generally, the ``reference`` of ``InputIterator`` must be
the same as ``value_type`` of it.


- Header: ``<pstade/oven/to_stream.hpp>``
- Valid expression: ``to_stream(os)``
- Precondition: The type to be assigned to dereference of an iterator which ``to_stream`` returns must be an ``OutputStreamable``.
- Returns: An ``OutputIterator`` which behave as if it were ``std::ostream_iterator``.


``to_utf8_encoder``
^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/to_utf8_encoder.hpp>``
- Valid expression: ``to_utf8_encoder(oit)``, where ``oit`` is an ``OutputIterator``.
- Returns: An ``OutputIterator`` which behave as if it were ``boost::utf8_output_iterator``.



Extending Boost.Range
---------------------
`The extension way of Boost.Range`__ seems to assume future C++ ability ``decltype``.
For now, it is not practical to apply the way to the large library something like MFC.
Oven provides yet another extension way, which is similar to
`Conceptualizing the Range-Based for Loop`__ proposal to simplify the Boost.Range one::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\extension.ipp


1. Specialize ``::pstade_oven_extension::Range``.
2. Define template ``associate``, ``begin`` and ``end``.
3. Call the macro, in global namespace, to act as a bridge between Oven and Boost.Range.

__ http://www.boost.org/libs/range/doc/boost_range.html#minimal_interface
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2049.pdf


Note that the const overloads can be sometimes omitted like above.
Also, ``Range`` has the second template parameter for ``pstade::enable_if``.
``boost::size`` is automatically extended by Oven.


- Header: ``<pstade/oven/extension.hpp>``
- Valid expression1: ``PSTADE_OVEN_EXTENSION_OF_TYPE(X)``
- Valid expression2: ``PSTADE_OVEN_EXTENSION_OF_TEMPLATE(X,N)``, where ``N`` is the number of template arguments. Only valid if all template arguments are typenames.
- Valid expression3: ``PSTADE_OVEN_EXTENSION_OF_TEMPLATE(X,S)``, where ``S`` is a sequence of template arguments. Must be used when integral or template template parameters are present.
- Precondition: ``X`` is a Boost.Preprocessor Sequence of type name.



MFC/ATL Extension
-----------------
Oven provides `Boost.Range`_ support for MFC/ATL collection and string types.
See `Oven Range MFC/ATL Extension`__.


__ ./doc/ms/mfc_atl.html



Acknowledgments
---------------
- `P-Stade`_
- `Boost C++ Libraries`_
- `Boost.Range`_
- `Boost.RangeEx`_
- `Boost.View`__
- `Range Library Core`__
- `Range Library Proposal`_
- `Proposal for new string algorithms in TR2`__
- `Cradle - A C++ Sandbox`__
- `RangeLib - The Boost Iterable Range Library`__
- `VTL (View Template Library)`__

__ http://www.flll.jku.at/staff/private/roland/view/
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2068.html
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html
__ http://sourceforge.jp/projects/cradle/
__ http://www.torjo.com/rangelib/index.html
__ http://www.zib.de/weiser/vtl/



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Released initial version.

Version 0.90.1 - 0.90.6
^^^^^^^^^^^^^^^^^^^^^^^
- Updated this document.
- Implemented `Range Algorithms`_.
- Added some `Ranges`_ and `Range Adaptors`_.
- Added some `Range Adaptors`_.
- Changed the header of `permuted`_.
- Changed the header of ``pointed``.
- Changed a valid expression of `zipped`_.
- Changed `checked`_ to throw exception.
- Renamed ``found`` to `string_found`_.
- Changed the header of `Range Algorithms`_.
- Added ``base_iterator``.
- Added some `Range Adaptors`_.
- Renamed ``accumulated`` to `scanned`_.
- Added workaround for `Standard Library Defect #198`__.
- Changed `constants`_ semantics, and added `always`_ instead.
- Changed `utf8_decoded`_ valid expression.
- `shared`_ accepts ``auto_ptr``.

__ http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198

Version 0.90.7 - 0.90.9
^^^^^^^^^^^^^^^^^^^^^^^
- Added ``matched``, ``xpressive_matched`` and ``xpressive_tokenized``.
- Renamed ``base_iterator`` to ``to_base``.
- Renamed ``copied`` adaptor to ``copied_to``.
- Added `concatenated`_.
- Renamed ``copied_to`` to ``copied_out``.
- Fixed a bug of ``transformed`` and ``concatenated``.
- Added ``generated``.
- No longer supports function types as ``rfun``.
- Changed `utf8_decoded`_ valid expression.

Version 0.91.0 - 0.91.3
^^^^^^^^^^^^^^^^^^^^^^^
- Added `Output Iterator Adaptors`_.
- Renamed ``generated`` to ``generation``.
- Renamed ``positioned`` to ``with_position``.
- Renamed ``matched`` to ``matches``.
- Renamed ``xpressive_matched`` to ``xpressive_matches``.
- Added `Extending Boost.Range`_.
- Rejected ``out_placed`` and ``sorted``.
- Added ``literal_range`` and ``c_str_range``.
- ``null_terminated`` no longer supports c-string.
- Added ``as_single`` to ``single_range``'\s valid expressions.
- Added ``begins/ends``.
- Added ``merged``, ``set_cup``, ``set_cap``, ``set_minus`` and ``set_delta``.
- Added ``rotated``.
- Removed ``stridden`` and changed effects of ``sliced``.
- Added ``through_window``.
- Added ``popped``.
- Changed the valid expression of ``array_protect_range`` and ``literal_range``.
- Added ``to_function``.
- Renamed ``shifted`` to ``advanced``.

Version 0.91.4 - 0.91.9
^^^^^^^^^^^^^^^^^^^^^^^
- Added ``any_range``.
- Removed ``popped`` and changed the valid expression of ``advanced``.
- Removed ``generation`` as adaptor and added it as range.
- ``taken`` and ``taken_while`` supports `Single Pass Range`_.
- Added ``iterate_range``.
- Added ``adjacent_transformed``.
- Added ``popped_back``.
- Changed ``counting_range`` valid expressions.
- Renamed ``repeated`` to ``cycled``.
- Added ``repeat_range``.
- Renamed ``popped_back`` to ``popped``.
- Changed the valid expressions of ``zipped`` and ``zipped_with``.
- Ported to VC++7.1 SP1.
- Added MFC/ATL support.

Version 0.92.0 - 0.92.3
^^^^^^^^^^^^^^^^^^^^^^^
- Renamed ``counting_range`` to ``count_range``, and added a valid expression.
- Removed the valid expression ``advanced(d)``.
- Renamed ``tie`` to ``pack``.
- Added ``boost::result_of`` support to range-based algorithms.
- Renamed `Extending Boost.Range`_ macros.
- Renamed ``adaptor_to`` to ``adapted_to``.

Version 0.93.0
^^^^^^^^^^^^^^
- Changed the names of some functions and headers.
- Added ``delimited``.

Version 0.93.1
^^^^^^^^^^^^^^
- Renamed ``begins/ends`` to ``begin/end``.
- ``adjacent_transformed`` rejects empty range.
- Changed template parameter of ``any_range``.
- Replaced ``regularized`` with ``regular``.
- Removed ``to_regularized_function``.
- ``scanned`` range contains the ``init`` as the first element.

Version 0.93.2
^^^^^^^^^^^^^^
- ``taken`` and ``taken_while`` behave lazily.
- ``taken`` and ``taken_while`` now return only up to ForwardRange.
- ``dropped`` and ``taken`` accept ``n`` which is larger than the distance.
- Removed ``null_terminated``.
- ``as_c_str`` accepts a range.
- ``zipped`` and ``zipped_with`` accept any tuple.
- Removed ``generation_copied``.
- Added ``shared_regular`` and ``innumerable``.

Version 0.93.3
^^^^^^^^^^^^^^
- Added ``recursion``.


