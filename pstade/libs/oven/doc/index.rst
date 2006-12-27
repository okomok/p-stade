++++++++++++++++++++++
The Oven Range Library
++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: Shunsuke Sogame
:Contact: pstade.mb@gmail.com
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.92.2



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



Range Algorithms
----------------
Oven provides some range-based algorithms.
``<pstade/oven/functions.hpp>`` includes all the following functions unless otherwise specified.


STL Algorithms
^^^^^^^^^^^^^^
Oven has all the range-based STL algorithms which are ported from `Boost.RangeEx`_ with some compiler workarounds::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\stl_algorithms.ipp


- Header: ``<pstade/oven/algorithm.hpp>``
- Valid expression: ``oven::algo(rng,a0,a1,...,aN);``
- Precondition: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);`` is a valid expression, where ``algo`` is one of the STL algorithms.
- Returns: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);``


``adaptor_to/to_base``
^^^^^^^^^^^^^^^^^^^^^^
``adaptor_to`` gets the ``base_type`` iterator of iterator adaptors::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\adaptor_to_base.ipp


- Header: ``<pstade/oven/adaptor_to_base.hpp>``
- Valid expression: ``base = oven::adaptor_to<BaseIter>(it);`` or ``BaseIter base = it|to_base;``
- Precondition: The type of ``base`` is ``BaseIter``, and ``it`` is an iterator adaptor.

``to_base`` adds the automatic type deduction to ``adaptor_to``.


``begins/ends``
^^^^^^^^^^^^^^^
``begins/ends`` is a pipable version of ``boost::begin/end``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\begins_ends.ipp


- Header: ``<pstade/oven/begin_end.hpp>``
- Valid expression: ``rng|begins`` and ``rng|ends``.
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
- Valid expression: ``oven::distance(rng);``
- Precondition: ``std::distance(boost::begin(rng),boost::end(rng));`` is a valid expression.
- Returns: ``std::distance(boost::begin(rng),boost::end(rng))``


``equals``
^^^^^^^^^^
``equals`` is the range-based ``std::equal`` that takes two ranges as the arguments.
Note that the size of two ranges is also checked out::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\equals.ipp


- Header: ``<pstade/oven/equals.hpp>``
- Valid expression: ``oven::equals(rng1,rng2);``
- Precondition: ``oven::equal(rng1,boost::begin(rng2));`` is a valid expression.
- Returns: ``true`` if and only if the ``oven::equal(rng1,boost::begin(rng2))`` and ``boost::size(rng1) == boost::size(rng2)`` returns ``true``.



Ranges
------
Oven provides some predefined range types.
``<pstade/oven/ranges.hpp>`` includes every range header unless otherwise specified.


``any_range``
^^^^^^^^^^^^^
``any_range`` is a range whose iterators behave as if they were the original iterators wrapped in
`any_iterator`__::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\any_range.ipp


__ http://thbecker.net/free_software_utilities/type_erasure_for_cpp_iterators/start_page.html

- Header: ``<pstade/oven/any_range.hpp>``
- Valid expression: ``any_range<Value,TraversalTag> any_(rng);`` and ``any_range<Value,TraversalTag> any_ = rng;``
  , where the iterators of ``any_`` are ``Interoperatable`` if and only if ``rng``\s are the same type.


``array_protect_range``
^^^^^^^^^^^^^^^^^^^^^^^
The current Boost.Range regards char array as literal, which
``array_protect_range`` works around.

- Header: ``<pstade/oven/array_protect_range.hpp>``
- Valid expression: ``array_protect_range<T> rng(arr)`` and ``arr|array_protected``
- Precondition: ``arr`` is an array whose ``value_type`` is ``T`` and whose size is ``sz``.
- Returns: ``[boost::begin(arr),boost::begin(arr)+sz)``, where ``sz`` is the size of ``arr``.


``array_range``
^^^^^^^^^^^^^^^
``array_range`` is a model of `Random Access Range`_ which delivers
a range presentation of dynamically allocated arrays::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\array_range.ipp


- Header: ``<pstade/oven/array_range.hpp>``
- Valid expression: ``array_range<T> rng(sz);``
- Precondition: ``new T[sz];`` is a valid expression.


``c_str_range``
^^^^^^^^^^^^^^^
``c_str_range`` makes a `Random Access Range`_ from null-terminated c-style string::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\c_str_range.ipp


- Header: ``<pstade/oven/c_str_range.hpp>``
- Valid expression: ``c_str_range<Char> rng(psz)`` and ``psz|as_c_str``, where ``psz`` is convertible to a pointer to a null-terminated array.


``count_range``
^^^^^^^^^^^^^^^^^^
``count_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `counting_iterator`__.
Note that this range introduces the replacement of ``for`` loop::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\count_range.ipp

__ http://www.boost.org/libs/iterator/doc/counting_iterator.html


- Header: ``<pstade/oven/count_range.hpp>``
- Valid expression1: ``count_range<I,T,D> rng(n,m);``, ``oven::make_count_range(n,m);`` and ``pstade::pack(n,m)|counted``.
- Valid expression2: ``oven::count_from(n)`` and ``oven::count_to(m)``
- Precondition: ``boost::couting_iterator<I,T,D>(x);`` is a valid expression, where
  ``x`` is ``n`` or ``m``.


``directory_range``
^^^^^^^^^^^^^^^^^^^
``directory_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `directory_iterator`__::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directory_range.ipp

__ http://www.boost.org/libs/filesystem/doc/operations.htm#directory_iterator


- Header: ``<pstade/oven/directory_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``directory_range rng(p);`` and ``wdirectory_range wrng(wp);``
- Precondition: The type of ``p`` is ``boost::filesystem::path`` and
  the type of ``wp`` is ``boost::filesystem::wpath``.


``empty_range``
^^^^^^^^^^^^^^^
``empty_range`` is a `Random Access Range`_ which is always empty::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\empty_range.ipp
	

- Header: ``<pstade/oven/empty_range.hpp>``
- Valid expression: ``empty_range<T> rng;``


``file_range``
^^^^^^^^^^^^^^
``file_range`` is a range whose iterators behave as if they were the original iterators wrapped in `file_iterator`__.
The member ``is_open()`` returns ``true`` if and only if the file opening is succeeded.
If ``is_open()`` is not ``true``, the range is empty::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\file_range.ipp

__ http://www.boost.org/libs/spirit/doc/file_iterator.html


- Header: ``<pstade/oven/file_range.hpp>``
- Valid expression: ``file_range<C> rng;`` and ``rng.is_open();``
- Precondition: ``boost::spirit::file_iterator<C>`` is a valid expression.


``generate_range``
^^^^^^^^^^^^^^^^^^
``generate_range`` is a `Single Pass Range`_ whose iterators behave as if
they were the original iterators wrapped in `generator_iterator`__::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\generate_range.ipp

__ http://www.boost.org/libs/utility/generator_iterator.htm


- Header: ``<pstade/oven/generate_range.hpp>``
- Valid expression1: ``generate_range<Rfun> rng(rfun);`` and ``oven::make_generate_range(rfun)``
- Valid expression2: ``oven::generation(rfun)``
- Precondition:``rfun`` call returns initialized ``boost::optional`` if range is not end; Otherwise, returns uninitialized one.
- Returns: A `Single Pass Range`_ whose values are the results of invoking ``rfun``, where ``rfun`` is a reference in the case of valid expression2.


``index_range``
^^^^^^^^^^^^^^^
Pending...

A legacy API may provide a way to access objects by using an index.
``index_range`` can be a building block for something like a ``ToolBarButtonRange``.

- Header: ``<pstade/oven/index_range.hpp>``
- Valid expression: ``index_range<Incrementable,Rfun>``, where ``Rfun`` is a type of ``rfun``.


``istream_range``
^^^^^^^^^^^^^^^^^
``istream_range`` is a range whose iterators behave as if they were the original iterators wrapped in `istream_iterator`__::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\istream_range.ipp

__ http://www.sgi.com/tech/stl/istream_iterator.html


``istreambuf_range``
^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/istreambuf_range.hpp>``
- Valid expression: ``istreambuf_range<C,T> rng(stm);`` and  ``oven::make_istreambuf_range(stm);``
- Precondition: ``std::istreambuf_iterator<C,T>(stm)`` is a valid expression.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``istreambuf_iterator``


``iterate_range``
^^^^^^^^^^^^^^^^^
``iterate_range`` creates an infinite range where the first item is calculated by applying
the function on the first argument, the second item by applying the function on the previous result and so on::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\iterate_range.ipp
	

- Header: ``<pstade/oven/iterate_range.hpp>``
- Valid expression: ``iterate_range<X,Fun> rng(x,fun);`` and  ``oven::iteration(x,fun);``
- Returns: An infinite `Single Pass Range`_ of repeated applications of ``fun`` to ``x``.


``literal_range``
^^^^^^^^^^^^^^^^^
``literal_range`` makes a `Random Access Range`_ from character array.
``literal_range`` doesn't support any pointer type but array type. So it is safe and fast. Compare it with ``c_str_range``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\literal_range.ipp


- Header: ``<pstade/oven/literal_range.hpp>``
- Valid expression: ``literal_range<Char> rng(arr)`` and ``arr|as_literal``, where ``arr`` is a ``char`` or ``wchar_t`` array type;


``repeat_range``
^^^^^^^^^^^^^^^^
``repeat_range`` creates a `Random Access Range`_ where all values are the first argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\repeat_range.ipp

- Header: ``<pstade/oven/repeat_range.hpp>``
- Valid expression: ``repeat_range<T,C> rng(v,c);``, ``oven::make_repeat_range(v,c)`` and ``v|repeated(c)``.
- Precondition: The type of ``v`` is ``T``.


``single_range``
^^^^^^^^^^^^^^^^
``single_range`` is a `Random Access Range`_ which delivers a range presentation of one object::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\single_range.ipp


- Header: ``<pstade/oven/single_range.hpp>``
- Valid expression: ``single_range<T> rng(v);``, ``oven::make_single_range(v)`` and ``v|as_single``.
- Precondition: The type of ``v`` is ``T``.



Range Adaptors
--------------
A Range Adaptor delivers an altered presentation of one or more underlying ranges.
Range Adaptors are lazy, meaning that their elements are only computed on demand.
The underlying ranges are not modified.
Additional information is available at `Range Library Proposal`_.
``<pstade/oven/ranges.hpp>`` includes all the following Range Adaptors unless otherwise specified.


Specification
^^^^^^^^^^^^^
- ``rng``: any range
- ``fwdRng``: any `Forward Range`_
- ``biRng``: any `Bidirectional Range`_
- ``rndRng``: any `Random Access Range`_
- ``pred``: any `Predicate`_
- ``rfun``: any `Functor`_ which can be used with ``boost::result_of``.

The function type is not supported as ``rfun``.
Instead, add ``&`` to make it a function **pointer**.


``adjacent_filtered``
^^^^^^^^^^^^^^^^^^^^^
``adjacent_filtered`` returns a range where adjacent pairs of base range are filtered by using a `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\adjacent_filtered.ipp


- Header: ``<pstade/oven/adjacent_filter_range.hpp>``
- See: `Range Library Proposal`_.


``adjacent_transformed``
^^^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/adjacent_transform_range.hpp>``
- Valid expression: ``fwdRng|adjacent_transformed(rfun)``
- Returns: A range where adjacent pairs of ``fwdRng`` are transformed by using ``rfun``.


``advanced``
^^^^^^^^^^^^
- Header: ``<pstade/oven/advance_range.hpp>``
- Valid expression: ``fwdRng|advanced(d1,d2)``
- Precondition: ``fwdRng`` must be a `Bidirectional Range`_ if either ``d1`` or ``d2`` is negative.
- Returns: ``[boost::next(boost::begin(fwdRng),d1),boost::next(boost::end(fwdRng),d2))``.


``always``
^^^^^^^^^^^^^
``always`` returns a range which does not change as its base range vary::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\always.ipp


- Header: ``<pstade/oven/always_range.hpp>``
- Valid expression: ``unusedRng|always(rng)``
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``appended``
^^^^^^^^^^^^
``appended`` returns a range which is appended with its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\appended.ipp


- Header: ``<pstade/oven/append_range.hpp>``
- Valid expression: ``rng|appended(v)``
- Returns: ``rng|jointed(oven::make_single_range(v))``.


``applied``
^^^^^^^^^^^
``applied`` puts an algorithm into a range, intended to be used with Boost.Phoenix version2::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\applied.ipp


- Header: ``<pstade/oven/apply_range.hpp>``
- Valid expression: ``rng|applied(f1,f2)``
- Precondition: ``f1(rng)`` and ``f2(rng)`` return iterators that are convertible to ``rng``\'s.
- Returns: ``[f1(rng),f2(rng))``.

``rng1`` is the same as ``phoenix::arg1``.


``broken_into``
^^^^^^^^^^^^^^^
``broken_into`` is the adaptor version of ``boost::tokenizer``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\broken_into.ipp


- Header: ``<pstade/oven/break_into_range.hpp>``
- Valid expression: ``rng|broken_into<t>(f)``, where ``f`` is a ``TokenizerFunction``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::token_iterator``.


``checked``
^^^^^^^^^^^
``checked`` adds the bounds checking ability to its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\checked.ipp


- Header: ``<pstade/oven/check_range.hpp>``
- Valid expression: ``rng|checked``
- Effect: Throws ``check_error`` derived from ``std::range_error`` if iterators go out of ``rng``.
- Returns: ``[boost::begin(rng),boost::end(rng))``


``cleared``
^^^^^^^^^^^
``cleared`` returns a range which is always empty::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\cleared.ipp


- Header: ``<pstade/oven/clear_range.hpp>``
- Valid expression: ``rng|cleared``
- Returns: ``[boost::end(rng),boost::end(rng))``.



``concatenated``
^^^^^^^^^^^^^^^^
``concatenated`` accepts a range whose ``value_type`` is a range and concatenates them::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\concatenated.ipp

- Header: ``<pstade/oven/concatenate_range.hpp>``
- Valid expression: ``rngs|concatenated``
- Specification: ``SegmentIterator`` is an iterator of ``rngs``, and ``LocalIterator`` is an iterator of the range which the dereference of ``SegmentIterator`` returns.
- Precondition: The ``LocalIterator`` must be valid after copying of ``SegmentIterator``.



``constants``
^^^^^^^^^^^^^
In spite of STL designers effort, the ``const_iterator`` is not so useful as expected.
An adapted range loses the difference between the mutable and constant.
That's why ``constants`` returns a range whose iterators dereference cannot be modified::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\constants.ipp


- Header: ``<pstade/oven/constant_range.hpp>``
- Valid expression: ``rng|constants``
- Returns: ``[boost::end(rng),boost::end(rng))`` whose iterators are constant.


``const_lvalues``
^^^^^^^^^^^^^^^^^
``const_lvalues`` turns the associated ``reference`` type of the base range into reference type,
which makes iterators of `Forward Range`_ conform to Forward Iterator.
Thus, STL that doesn't know traversal concepts can choose effective algorithms.


- Header: ``<pstade/oven/const_lvalue_range.hpp>``
- Valid expression: ``rng|const_lvalues``
- Returns: ``[boost::begin(rng),boost::end(rng))`` whose iterators are constant.


``copied_out``
^^^^^^^^^^^^^^
``copied_out`` makes a side-effect that copies its base range to its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copied_out.ipp


- Header: ``<pstade/oven/copy_range.hpp>``
- Valid expression: ``rng|copied_out(it)``
- Precondition: ``oven::copy(rng,it)`` is a valid expression.
- Effect: ``oven::copy(rng,it)``
- Returns: ``rng``.


``cycled``
^^^^^^^^^^^^
``cycled`` creates a circular range from its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\cycled.ipp


- Header: ``<pstade/oven/cycle_range.hpp>``
- Valid expression: ``rng|cycled(n)``
- Returns: A constant range that repeats ``[boost::begin(rng),boost::end(rng))`` ``n`` times.


``directed``
^^^^^^^^^^^^
``directed`` returns a range whose values are iterators of its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directed.ipp


- Header: ``<pstade/oven/direct_range.hpp>``
- Valid expression: ``rng|directed``
- Returns: ``oven::make_count_range(boost::begin(rng),boost::end(rng))``.


``dropped``
^^^^^^^^^^^
``dropped`` returns the suffix of its base range after the first ``n`` elements::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped.ipp


- Header: ``<pstade/oven/drop_range.hpp>``
- Valid expression: ``rng|dropped(n)``
- Precondition: ``0 <= n && n <= oven::distance(rng)``
- Returns: ``[f,boost::end(rng))``, where ``f = boost::begin(rng); std::advance(f,n);``.


``dropped_while``
^^^^^^^^^^^^^^^^^
``dropped_while`` returns the remaining suffix of its base range of elements that satisfy `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped_while.ipp


- Header: ``<pstade/oven/drop_while_range.hpp>``
- Valid expression: ``rng|dropped_while(pred)``
- Returns: ``[f,boost::end(rng))``, where ``f = oven::find_if(f,not_(pred));``


``filtered``
^^^^^^^^^^^^
``filtered`` returns a range which is filtered by using a `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\filtered.ipp

Note that a non-assignable lambda functor makes ``filtered`` non-conforming, so
it needs `regularized`_ that makes it assignable and then conforming.


- Header: ``<pstade/oven/filter_range.hpp>``
- See: `Range Library Proposal`_.


``firsts``
^^^^^^^^^^
- Header: ``<pstade/oven/first_range.hpp>``
- Valid expression: ``rng|firsts``
- Returns: ``rng|map_keys``.


``got_at``
^^^^^^^^^^
Pending...

- Header: ``<pstade/oven/get_at_range.hpp>``
- Valid expression: ``rng|got_at<N>()`` or ``rng|got_at_c<N>()``, where ``value_type`` of ``rng`` is a Fusion Sequence.


``identities``
^^^^^^^^^^^^^^
``identities`` returns a range which is identical to its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\identities.ipp


- Header: ``<pstade/oven/identity_range.hpp>``
- Valid expression: ``rng|identities`` and ``rng|identities(trv)``, where ``trv`` is a traversal tag object.
- Precondition: ``rng``\'s traversal tag is convertible to ``trv``.
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``indirected``
^^^^^^^^^^^^^^
``indirected`` adapts its base range by applying an extra dereference inside of ``operator*()``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\indirected.ipp


- Header: ``<pstade/oven/indirect_range.hpp>``
- See: `Range Library Proposal`_.


``jointed``
^^^^^^^^^^^
``jointed`` returns a range which is jointed with its argument::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\jointed.ipp


- Header: ``<pstade/oven/joint_range.hpp>``
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``reference`` type of ``rng2`` is convertible to ``rng1``\'s without creating rvalue.
- Returns: A range that joints ``[boost::begin(rng1),boost::end(rng1))`` and ``[boost::begin(rng2),boost::end(rng2))``.


``map_keys``
^^^^^^^^^^^^
``map_keys`` returns a range whose values are the keys of its base associative container::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_keys.ipp


- Header: ``<pstade/oven/map_key_range.hpp>``
- See: `Range Library Proposal`_.


``map_values``
^^^^^^^^^^^^^^
``map_values`` returns a range whose values are the mapped values of its base associative container::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_values.ipp


- Header: ``<pstade/oven/map_value_range.hpp>``
- See: `Range Library Proposal`_.


``matches``
^^^^^^^^^^^
- Header: ``<pstade/oven/match_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|matches(re)`` or ``biRng|matches(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::regex_iterator``.


``memoized``
^^^^^^^^^^^^
``memoized`` returns a range whose values are cached for speed, preparing repeated dereferences.
Note that ``memoized`` can return a `Forward Range`_ even if its base range is a `Single Pass Range`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\memoized.ipp


- Header: ``<pstade/oven/memoize_range.hpp>``
- Valid expression: ``rng|memoized``
- Precondition: ``rng`` is referentially transparent.
- Returns: A `Forward Range`_ whose values are memoized.


``merged``
^^^^^^^^^^
``merged`` combines two sorted ranges into a single sorted range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\merged.ipp


- Header: ``<pstade/oven/merge_range.hpp>``
- Valid expression: ``rng1|merged(rng2)`` and ``rng1|merged(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant `Forward Range`_ which behaves as if they were made by ``std::merge``.


``null_terminated``
^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/null_terminate_range.hpp>``
- Valid expression: ``fwdRng|null_terminated``
- Precondition: ``fwdRng`` has a value which is convertible to ``0``.
- Returns: ``fwdRng|taken_while(_1 != 0)``.


``permuted``
^^^^^^^^^^^^
- Header: ``<pstade/oven/permute_range.hpp>``
- Valid expression: ``rndRng|permuted(rng)``
- Precondition: ``rng`` is a range of the indices of ``rndRng``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::permutation_iterator``.


``pointed``
^^^^^^^^^^^
``pointed`` provides an interface to have a conversation with legacy APIs::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\pointed.ipp


- Header: ``<pstade/oven/point_range.hpp>``
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is a template instantiation of ``std::vector``.
- Returns:  ``[&*boost::begin(vec),&*boost::begin(vec)+oven::distance(vec))`` if ``vec`` is not empty; otherwise, ``[0,0)``.


``popped``
^^^^^^^^^^
- Header: ``<pstade/oven/pop_range.hpp>``
- Valid expression: ``fwdRng|popped``
- Returns: A range which behaves as if it were ``[boost::begin(fwdRng),boost::next(boost::begin(fwdRng),oven::distance(fwdRng)-1))``


``prepended``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/prepend_range.hpp>``
- Valid expression: ``rng|prepended(v)``
- Returns: ``oven::make_single_range(v)|jointed(rng)``.


``regularized``
^^^^^^^^^^^^^^^
Boost.Lambda functors are neither DefaultConstructible nor CopyAssignable.
An iterator holding such a functor cannot conform to even InputIterator.
``regularized`` converts such a broken iterator to conforming one.


- Header: ``<pstade/oven/regularize_range.hpp>``
- Valid expression: ``rng|regularized``
- Returns: ``[boost::begin(rng),boost::end(rng))``, which is a conforming range, even if iterators of ``rng`` are not assignable.


``rotated``
^^^^^^^^^^^
- Header: ``<pstade/oven/rotate_range.hpp>``
- Valid expression: ``fwdRng|rotated(fun)``
- Returns: ``[fun(fwdRng),boost::end(fwdRng))|jointed([boost::begin(fwdRng),fun(fwdRng)))``


``reversed``
^^^^^^^^^^^^
- Header: ``<pstade/oven/reverse_range.hpp>``
- See: `Range Library Proposal`_.


``set_cap``
^^^^^^^^^^^
- Header: ``<pstade/oven/set_intersection_range.hpp>``
- Valid expression: ``rng1|set_cap(rng2)`` and ``rng1|set_cap(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant `Forward Range`_ which behaves as if they were made by ``std::set_intersection``.


``set_cup``
^^^^^^^^^^^
- Header: ``<pstade/oven/set_union_range.hpp>``
- Valid expression: ``rng1|set_cup(rng2)`` and ``rng1|set_cup(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant `Forward Range`_ which behaves as if they were made by ``std::set_union``.


``set_delta``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/set_symmetric_difference_range.hpp>``
- Valid expression: ``rng1|set_delta(rng2)`` and ``rng1|set_delta(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant `Forward Range`_ which behaves as if they were made by ``std::set_symmetric_difference``.


``set_minus``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/set_difference_range.hpp>``
- Valid expression: ``rng1|set_minus(rng2)`` and ``rng1|set_minus(rng2,pred)``
- Precondition: ``rng1`` and ``rng2`` are sorted.
- Returns: A constant `Forward Range`_ which behaves as if they were made by ``std::set_difference``.


``scanned``
^^^^^^^^^^^
``scanned`` is similar to ``oven::accumulate``, but returns a range of successive reduced values from its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\scanned.ipp


- Header: ``<pstade/oven/scan_range.hpp>``
- Valid expression: ``rng|scanned(init,fun)``
- Precondition: ``fun(s,r)`` is a valid expression, where the type of ``s`` is the same as ``init`` and ``r`` is the iterator dereference of ``rng``.


``seconds``
^^^^^^^^^^^
- Header: ``<pstade/oven/second_range.hpp>``
- Valid expression: ``rng|seconds``
- Returns: ``rng|map_values``.


``shared``
^^^^^^^^^^
- Header: ``<pstade/oven/share_range.hpp>``
- Valid expression: ``new Range|shared``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::shared_container_iterator``.


``sliced``
^^^^^^^^^^
``sliced`` provides the column view of its base range::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\sliced.ipp

- Header: ``<pstade/oven/slice_range.hpp>``
- Valid expression: ``rndRng|sliced(start,stride)``
- Precondition: ``d == 0 || d % stride == 0`` and ``0 <= start && start < stride``, where ``d = oven::distance(rndRng);``

Note that this effect is different from `Range Library Proposal`_\'s, which is the role of `advanced`_.


``string_found``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/string_find_range.hpp>``
- Valid expression: ``rng|string_found(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::algorithm::find_iterator``.


``string_split``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/string_split_range.hpp>``
- Valid expression: ``rng|string_split(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::algorithm::split_iterator``.


``taken``
^^^^^^^^^
``taken``, applied to its base range, returns the prefix of the range of length ``n``::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken.ipp


- Header: ``<pstade/oven/take_range.hpp>``
- Valid expression: ``rng|taken(n)``
- Precondition: ``0 <= n && n <= oven::distance(rng)``
- Returns: A range which behaves as if it were ``[boost::begin(rng),l)``, where ``l = boost::begin(rng); std::advance(l,n);``.


``taken_while``
^^^^^^^^^^^^^^^
``taken_while``, applied to a `Predicate`_ and its base range, returns the longest
prefix (possibly empty) of the range of elements that satisfy `Predicate`_::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken_while.ipp


- Header: ``<pstade/oven/take_while_range.hpp>``
- Valid expression: ``rng|taken_while(pred)``
- Returns: A range which behaves as if it were ``[boost::begin(rng),oven::find_if(rng,not_(pred)))``


``tokenized``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/token_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- See: `Range Library Proposal`_.


``transformed``
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/transorm_range.hpp>``
- Valid expression: ``rng|transformed(rfun)``
- See: `Range Library Proposal`_.


``through_window``
^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/window_range.hpp>``
- Valid expression: ``fwdRng|through_window(n,m)``
- Returns: ``[boost::next(boost::begin(rng),n),boost::next(boost::begin(rng),m))``.


``uniqued``
^^^^^^^^^^^
- Header: ``<pstade/oven/unique_range.hpp>``
- See: `Range Library Proposal`_.


``unzipped``
^^^^^^^^^^^^
Pending...

- Header: ``<pstade/oven/unzip_range.hpp>``
- Valid expression: ``zipped_rng|unzipped_at<N>()`` or ``zipped_range|unzipped``
- Precondition: ``N`` is a integral constant specifying the index.
- Returns: A range which is unzipped the `zipped`_ range.


``utf8_decoded``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/utf8_decode_range.hpp>``
- Valid expression: ``biRng|utf8_decoded`` or ``biRng|utf8_decoded(u32)``
- Returns: A `Bidirectional Range`_ whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.


``with_position``
^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/position_range.hpp>``
- Valid expression: ``rng|with_position``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::position_iterator``.


``xpressive_matches``
^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_match_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_matches(re)`` or ``biRng|xpressive_matches(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_iterator``.


``xpressive_tokenized``
^^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_token_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_tokenized(re)`` or ``biRng|xpressive_tokenized(re,subMatches,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_token_iterator``.


``zipped``
^^^^^^^^^^
``zipped`` takes a tuple of ranges and returns a range of corresponding tuples.
If one input range is short, excess elements of the longer range are discarded.

- Header: ``<pstade/oven/zip_range.hpp>``
- Valid expression: ``pstade::pack(rng1,rng2,..rngN)|zipped``, where ``N <= 5``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::zip_iterator``.

If the base ranges are neither const-reference nor rvalue, you can use ``boost::tie`` instead of ``pstade::pack``.


``zipped_with``
^^^^^^^^^^^^^^^
``zipped_with`` generalises ``zipped`` by zipping with the functor,
given as the first argument, instead of a tupling::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\zipped_with.ipp


- Header: ``<pstade/oven/zip_with_range.hpp>``
- Valid expression: ``pstade::pack(rng1,rng2,..rngN)|zipped_with(rfun)``, where ``N <= 5``.
- Precondition: The arity of ``rfun`` is ``N``.
- Returns: A range whose values are zipped by using ``rfun``.



Output Iterator Adaptors
------------------------

``to_counter``
^^^^^^^^^^^^^^
``to_counter`` takes an initial count and increments it every output.
`adaptor_to/to_base`_ can extract the result of the counting::

	E:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\to_counter.ipp


- Header: ``<pstade/oven/to_counter.hpp>``
- Valid expression: ``to_counter(i)``, where ``i`` is an ``Incrementable``.
- Returns: An ``OutputIterator`` which counts the output.


``to_function``
^^^^^^^^^^^^^^^
``to_function`` returns an ``OutputIterator`` which is a port of `boost::function_output_iterator`__
with some workarounds.

__ http://www.boost.org/libs/iterator/doc/function_output_iterator.html

- Header: ``<pstade/oven/function_output_iterator.hpp>``
- Valid expression: ``to_function(fun)`` and ``to_regularized_function(lambda)``
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
Also, ``Range`` has the second template parameter for ``boost::enable_if``.
``boost::size`` is automatically extended by Oven.


- Header: ``<pstade/oven/extension.hpp>``
- Valid expression1: ``PSTADE_OVEN_EXTENSION_TYPE(X)``
- Valid expression2: ``PSTADE_OVEN_EXTENSION_TEMPLATE(X,N)``, where ``N`` is the number of template arguments. Only valid if all template arguments are typenames.
- Valid expression3: ``PSTADE_OVEN_EXTENSION_TEMPLATE(X,S)``, where ``S`` is a sequence of template arguments. Must be used when integral or template template parameters are present.
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
- `RangeLib - The Boost Iterable Range Library`__
- `VTL (View Template Library)`__

__ http://www.flll.jku.at/staff/private/roland/view/
__ http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2068.html
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
- Added `literal_range`_ and `c_str_range`_.
- `null_terminated`_ no longer supports c-string.
- Added ``as_single`` to `single_range`_'\s valid expressions.
- Added `begins/ends`_.
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

Version 0.92.0
^^^^^^^^^^^^^^
- Renamed ``counting_range`` to ``count_range``, and added a valid expression.

Version 0.92.1
^^^^^^^^^^^^^^
- Removed the valid expression ``advanced(d)``.

Version 0.92.2
^^^^^^^^^^^^^^
- Renamed ``tie`` to ``pack``.
- Added ``boost::result_of`` support to range-based algorithms.


