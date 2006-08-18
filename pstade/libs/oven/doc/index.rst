++++++++++++++++++++++
The Oven Range Library
++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.8



.. epigraph::

	"*Oh Paulie!*"
	
	-- Adrian



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
Oven provides an experimental Range Adaptor implementation of `Range Library Proposal`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\introduction.ipp

All the types and functions are defined in ``namespace pstade::oven`` at ``<pstade/oven.hpp>``.


Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 1.00.5`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Range Algorithms
----------------
Oven provides some range-based algorithms.
``<pstade/oven/functions.hpp>`` includes all the following functions unless otherwise specified.


STL Algorithms
^^^^^^^^^^^^^^
Oven has all the range-based STL algorithms which are ported from `Boost.RangeEx`_ with some compiler workarounds::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\stl_algorithms.ipp


- Header: ``<pstade/oven/algorithm.hpp>``
- Valid expression: ``oven::algo(rng,a0,a1,...,aN);``
- Precondition: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);`` is a valid expression, where ``algo`` is one of the STL algorithms.
- Returns: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);``


``adaptor_to``
^^^^^^^^^^^^^^
``adaptor_to`` gets the ``base_type`` iterator of iterator adaptors::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\adaptor_to.ipp


- Header: ``<pstade/oven/adaptor_to_base.hpp>``
- Valid expression: ``base = oven::adaptor_to<BaseIter>(it);`` or ``BaseIter base = it|to_base;``
- Precondition: The type of ``base`` is ``BaseIter``, and ``it`` is an iterator adaptor.

``to_base`` adds the automatic type deduction to ``adaptor_to``.


``copied``
^^^^^^^^^^
``copied`` adds the automatic type deduction to `copy_range`_ which
calls the range constructor of the STL Sequences::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copied.ipp

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

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\distance.ipp


- Header: ``<pstade/oven/distance.hpp>``
- Valid expression: ``oven::distance(rng);``
- Precondition: ``std::distance(boost::begin(rng),boost::end(rng));`` is a valid expression.
- Returns: ``std::distance(boost::begin(rng),boost::end(rng))``


``equals``
^^^^^^^^^^
``equals`` is the range-based ``std::equal`` that takes two ranges as the arguments.
Note that the size of two ranges is also checked out::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\equals.ipp


- Header: ``<pstade/oven/equals.hpp>``
- Valid expression: ``oven::equals(rng1,rng2);``
- Precondition: ``oven::equal(rng1,boost::begin(rng2));`` is a valid expression.
- Returns: ``true`` if and only if the ``oven::equal(rng1,boost::begin(rng2))`` and ``boost::size(rng1) == boost::size(rng2)`` returns ``true``.



Ranges
------
Oven provides some predefined range types.
``<pstade/oven/ranges.hpp>`` includes every range header unless otherwise specified.


``array_range``
^^^^^^^^^^^^^^^
``array_range`` is a model of `Random Access Range`_ which delivers
a range presentation of dynamically allocated arrays::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\array_range.ipp


- Header: ``<pstade/oven/array_range.hpp>``
- Valid expression: ``array_range<T> rng(sz);``
- Precondition: ``new T[sz];`` is a valid expression.


``counting_range``
^^^^^^^^^^^^^^^^^^
``counting_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `counting_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\counting_range.ipp

__ http://www.boost.org/libs/iterator/doc/counting_iterator.html


- Header: ``<pstade/oven/counting_range.hpp>``
- Valid expression: ``counting_range<I,T,D> rng(n,m);`` and ``oven::make_counting_range(n,m);``
- Precondition: ``boost::couting_iterator<I,T,D>(x);`` is a valid expression, where
  ``x`` is ``n`` or ``m``.


``directory_range``
^^^^^^^^^^^^^^^^^^^
``directory_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `directory_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directory_range.ipp

__ http://www.boost.org/libs/filesystem/doc/operations.htm#directory_iterator


- Header: ``<pstade/oven/directory_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``directory_range rng(p);`` and ``wdirectory_range wrng(wp);``
- Precondition: The type of ``p`` is ``boost::filesystem::path`` and
  the type of ``wp`` is ``boost::filesystem::wpath``.


``empty_range``
^^^^^^^^^^^^^^^
``empty_range`` is a `Random Access Range`_ which is always empty::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\empty_range.ipp
	

- Header: ``<pstade/oven/empty_range.hpp>``
- Valid expression: ``empty_range<T> rng;``


``file_range``
^^^^^^^^^^^^^^
``file_range`` is a range whose iterators behave as if they were the original iterators wrapped in `file_iterator`__.
The member ``is_open()`` returns ``true`` if and only if the file opening is succeeded.
If ``is_open()`` is not ``true``, the range is empty::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\file_range.ipp

__ http://www.boost.org/libs/spirit/doc/file_iterator.html


- Header: ``<pstade/oven/file_range.hpp>``
- Valid expression: ``file_range<C> rng;`` and ``rng.is_open();``
- Precondition: ``boost::spirit::file_iterator<C>`` is a valid expression.


``istream_range``
^^^^^^^^^^^^^^^^^
``istream_range`` is a range whose iterators behave as if they were the original iterators wrapped in `istream_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\istream_range.ipp

__ http://www.sgi.com/tech/stl/istream_iterator.html



- Header: ``<pstade/oven/istream_range.hpp>``
- Valid expression: ``istream_range<V,C,T,D> rng(stm);`` and  ``oven::make_istream_range<V>(stm);``
- Precondition: ``std::istream_iterator<V,C,T,D>(stm)`` is a valid expression.


``single_range``
^^^^^^^^^^^^^^^^
``single_range`` is a `Random Access Range`_ which delivers a range presentation of one object::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\single_range.ipp


- Header: ``<pstade/oven/single_range.hpp>``
- Valid expression: ``single_range<T> rng(v);`` and ``oven::make_single_range(v)``
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
- ``rfun``: any `Functor`_ which can be used with ``boost::result_of``


``adjacent_filtered``
^^^^^^^^^^^^^^^^^^^^^
``adjacent_filtered`` returns a range whose adjacent pairs are filtered by using a `Predicate`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\adjacent_filtered.ipp


- Header: ``<pstade/oven/adjacent_filter_range.hpp>``
- See: `Range Library Proposal`_.


``always``
^^^^^^^^^^^^^
``always`` returns a range which does not change as its adapting range vary::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\always.ipp


- Header: ``<pstade/oven/always_range.hpp>``
- Valid expression: ``unusedRng|always(rng)``
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``appended``
^^^^^^^^^^^^
``appended`` returns a range which is appended with its argument::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\appended.ipp


- Header: ``<pstade/oven/append_range.hpp>``
- Valid expression: ``rng|appended(v)``
- Precondition: ``v*`` is convertible to the ``iterator`` type of ``rng``.
- Returns: ``rng|jointed(oven::make_single_range(v))``.


``applied``
^^^^^^^^^^^
``applied`` returns a range which is adapting by using functors.
``applied`` is intended to be used with Boost.Phoenix version2.

- Header: ``<pstade/oven/apply_range.hpp>``
- Valid expression: ``rng|applied(f1,f2)``
- Precondition: ``f1(rng)`` and ``f2(rng)`` return iterators that are convertible to ``rng``\'s.
- Returns: ``[f1(rng),f2(rng))``.


``array_protected``
^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/array_protect_range.hpp>``
- Valid expression: ``arr|array_protected``
- Precondition: ``arr`` is an array.
- Returns: ``[boost::begin(arr),boost::begin(arr)+sz)``, where ``sz`` is the size of ``arr``.


``broken_into``
^^^^^^^^^^^^^^^
``broken_into`` is the adaptor version of ``boost::tokenizer``::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\broken_into.ipp


- Header: ``<pstade/oven/break_into_range.hpp>``
- Valid expression: ``rng|broken_into<t>(f)``, where ``f`` is a ``TokenizerFunction``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::token_iterator``.


``checked``
^^^^^^^^^^^
``checked`` adds the bounds checking ability to its adapting range::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\checked.ipp


- Header: ``<pstade/oven/check_range.hpp>``
- Valid expression: ``rng|checked``
- Effect: Throws ``check_error`` derived from ``std::range_error`` if iterators go out of ``rng``.
- Returns: ``[boost::begin(rng),boost::end(rng))``


``cleared``
^^^^^^^^^^^
``cleared`` returns a range which is always empty::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\cleared.ipp


- Header: ``<pstade/oven/clear_range.hpp>``
- Valid expression: ``rng|cleared``
- Returns: ``[boost::end(rng),boost::end(rng))``.


``constants``
^^^^^^^^^^^^^
``constants`` returns a range whose iterators dereference cannot be modified::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\constants.ipp


- Header: ``<pstade/oven/constant_range.hpp>``
- Valid expression: ``rng|constants``
- Returns: ``[boost::end(rng),boost::end(rng))`` whose iterators are constant.


``const_lvalues``
^^^^^^^^^^^^^^^^^
``const_lvalues`` makes iterators of `Forward Range`_ conform to Forward Iterator, which
makes STL that doesn't know traversal concepts choose effective algorithms.


- Header: ``<pstade/oven/const_lvalue_range.hpp>``
- Valid expression: ``rng|const_lvalues``
- Returns: ``[boost::begin(rng),boost::end(rng))`` whose iterators are constant.


``copied_to``
^^^^^^^^^^^^^
``copied_to`` makes a side-effect that copies its adapting range to its argument::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copied_to.ipp


- Header: ``<pstade/oven/copy_range.hpp>``
- Valid expression: ``rng|copied_to(it)``
- Precondition: ``oven::copy(rng,it)`` is a valid expression.
- Effect: ``oven::copy(rng,it)``
- Returns: ``[boost::begin(rng),boost::end(rng))`` if ``rng`` is a `Forward Range`_; otherwise, ``void``.


``directed``
^^^^^^^^^^^^
``directed`` returns a range whose values are iterators of its adapting range::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directed.ipp


- Header: ``<pstade/oven/direct_range.hpp>``
- Valid expression: ``rng|directed``
- Returns: ``oven::make_counting_range(boost::begin(rng),boost::end(rng))``.


``dropped``
^^^^^^^^^^^
``dropped`` returns the suffix of its adapting range after the first ``n`` elements::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped.ipp


- Header: ``<pstade/oven/drop_range.hpp>``
- Valid expression: ``rng|dropped(n)``
- Precondition: ``0 <= n && n <= oven::distance(rng)``
- Returns: ``[f,boost::end(rng))``, where ``f = boost::begin(rng); std::advance(f,n);``.


``dropped_while``
^^^^^^^^^^^^^^^^^
``dropped_while`` returns the remaining suffix of its adapting range of elements that satisfy `Predicate`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\dropped_while.ipp


- Header: ``<pstade/oven/drop_while_range.hpp>``
- Valid expression: ``rng|dropped_while(pred)``
- Returns: ``[f,boost::end(rng))``, where ``f = oven::find_if(f,not_(pred));``


``filtered``
^^^^^^^^^^^^
``filtered`` returns a range which is filtered by using a `Predicate`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\filtered.ipp

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
``identities`` returns a range which is identical to its adapting range::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\identities.ipp


- Header: ``<pstade/oven/identity_range.hpp>``
- Valid expression: ``rng|identities``
- Returns: ``[boost::begin(rng),boost::end(rng))``.


``indirected``
^^^^^^^^^^^^^^
``indirected`` adapts its adapting range by applying an extra dereference inside of ``operator*()``::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\indirected.ipp


- Header: ``<pstade/oven/indirect_range.hpp>``
- See: `Range Library Proposal`_.


``jointed``
^^^^^^^^^^^
``jointed`` returns a range which is jointed with its argument::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\jointed.ipp


- Header: ``<pstade/oven/joint_range.hpp>``
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``iterator`` ``reference`` type of ``rng2`` is convertible to ``rng1``\'s.
- Returns: A range that joints ``[boost::begin(rng1),boost::end(rng1))`` and ``[boost::begin(rng2),boost::end(rng2))``.


``map_keys``
^^^^^^^^^^^^
``map_keys`` returns a range whose values are the keys of its adapting associative container::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_keys.ipp


- Header: ``<pstade/oven/map_key_range.hpp>``
- See: `Range Library Proposal`_.


``map_values``
^^^^^^^^^^^^^^
``map_values`` returns a range whose values are the mapped values of its adapting associative container::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\map_values.ipp


- Header: ``<pstade/oven/map_value_range.hpp>``
- See: `Range Library Proposal`_.


``matched``
^^^^^^^^^^^
- Header: ``<pstade/oven/match_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|matched(re)`` or ``biRng|matched(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::regex_iterator``.


``memoized``
^^^^^^^^^^^^
``memoized`` returns a range whose values are cached for speed, preparing repeated dereferences.
Note that ``memoized`` can return a `Forward Range`_ even if its adapting range is a `Single Pass Range`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\memoized.ipp


- Header: ``<pstade/oven/memoize_range.hpp>``
- Valid expression: ``rng|memoized``
- Precondition: ``rng`` is referentially transparent.
- Returns: A `Forward Range`_ whose values are memoized.


``null_terminated``
^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/null_terminate_range.hpp>``
- Valid expression: ``fwdRngOrString|null_terminated``
- Precondition: ``rngOrString`` is a string literal; otherwise, for all the value ``v`` in the ``fwdRngOrString``, the expression ``v == 0`` must be valid, and some ``v`` that the expression is ``true`` exists in the ``fwdRngOrString``.
- Returns: ``[boost::begin(fwdRngOrString),y)``, where for all the value ``v`` in the range ``v != 0`` is ``true``, and ``*y == 0`` is ``true``.


``out_placed``
^^^^^^^^^^^^^^
``out_placed`` converts its adapting range to a `Random Access Range`_ by using temporary iterator container::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\out_placed.ipp


- Header: ``<pstade/oven/out_place_range.hpp>``
- Valid expression: ``fwdRng|out_placed``
- Returns: A `Random Access Range`_ representing ``[boost::begin(fwdRng),boost::end(fwdRng))``.


``permuted``
^^^^^^^^^^^^
- Header: ``<pstade/oven/permute_range.hpp>``
- Valid expression: ``rndRng|permuted(rng)``
- Precondition: ``rng`` is a range of the indices of ``rndRng``.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::permutation_iterator``.


``pointed``
^^^^^^^^^^^
``pointed`` provides an interface to have a conversation with legacy APIs::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\pointed.ipp


- Header: ``<pstade/oven/point_range.hpp>``
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is a template instantiation of ``std::vector``.
- Returns:  ``[&*boost::begin(vec),&*boost::begin(vec)+oven::distance(vec))`` if ``vec`` is not empty; otherwise, ``[0,0)``.


``positioned``
^^^^^^^^^^^^^^
- Header: ``<pstade/oven/position_range.hpp>``
- Valid expression: ``rng|positioned``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::position_iterator``.


``prepended``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/prepend_range.hpp>``
- Valid expression: ``rng|prepended(v)``
- Precondition: The ``iterator`` type of ``rng`` is convertible to ``v*``.
- Returns: ``oven::make_single_range(v)|jointed(rng)``.


``regularized``
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/regularize_range.hpp>``
- Valid expression: ``rng|regularized``
- Returns: ``[boost::begin(rng),boost::end(rng))``, which is a conforming range, even if iterators of ``rng`` are not assignable.


``repeated``
^^^^^^^^^^^^
- Header: ``<pstade/oven/repeat_range.hpp>``
- Valid expression: ``rng|repeated(n)``
- Returns: A range that repeats ``[boost::begin(rng),boost::end(rng))`` ``n`` times.


``reversed``
^^^^^^^^^^^^
- Header: ``<pstade/oven/reverse_range.hpp>``
- See: `Range Library Proposal`_.


``scanned``
^^^^^^^^^^^
``scanned`` is similar to ``oven::accumulate``, but returns a range of successive reduced values from its adapting range::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\scanned.ipp


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


``shifted``
^^^^^^^^^^^
- Header: ``<pstade/oven/shift_range.hpp>``
- Valid expression: ``fwdRng|shifted(d)``
- Returns: ``fwdRng|sliced(d,d)``.


``sliced``
^^^^^^^^^^
- Header: ``<pstade/oven/slice_range.hpp>``
- See: `Range Library Proposal`_.


``sorted``
^^^^^^^^^^
``sorted`` provides the out-place sorting. Note that ``sorted`` doesn't modify its adapting range.

- Header: ``<pstade/oven/sort_range.hpp>``
- Valid expression: ``fwdRng|sorted`` or ``fwdRng|sorted(pred)``
- Returns: A sorted view of ``fwdRng``.


``stridden``
^^^^^^^^^^^^
``stridden`` provides the column view of its adapting range::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\stridden.ipp

- Header: ``<pstade/oven/stride_range.hpp>``
- Valid expression: ``fwdRng|stridden(l,o)``
- Precondition: ``d % l == 0 || d % l == l`` and ``o < l``, where ``d = oven::distance(fwdRng);``


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
``taken``, applied to its adapting range, returns the prefix of the range of length ``n``::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken.ipp


- Header: ``<pstade/oven/take_range.hpp>``
- Valid expression: ``fwdRng|taken(n)``
- Precondition: ``0 <= n && n <= oven::distance(rng)``
- Returns: ``[boost::begin(fwdRng),l)``, where ``l = boost::begin(fwdRng); std::advance(l,n);``.


``taken_while``
^^^^^^^^^^^^^^^
``taken_while``, applied to a `Predicate`_ and its adapting range, returns the longest
prefix (possibly empty) of the range of elements that satisfy `Predicate`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\taken_while.ipp


- Header: ``<pstade/oven/take_while_range.hpp>``
- Valid expression: ``fwdRng|taken_while(pred)``
- Returns: ``[boost::begin(fwdRng),oven::find_if(fwdRng,not_(pred)))``


``tokenized``
^^^^^^^^^^^^^
- Header: ``<pstade/oven/token_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- See: `Range Library Proposal`_.


``transformed``
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/transorm_range.hpp>``
- Valid expression: ``rng|transformed(rfun)``
- See: `Range Library Proposal`_.


``uniqued``
^^^^^^^^^^^
- Header: ``<pstade/oven/unique_range.hpp>``
- See: `Range Library Proposal`_.


``unzipped``
^^^^^^^^^^^^
Pending...

- Header: ``<pstade/oven/unzip_range.hpp>``
- Valid expression: ``zipped_rng|unzipped_at<N>`` or ``zipped_range|unzipped``
- Precondition: ``N`` is a integral constant specifying the index.
- Returns: A range which is unzipped the `zipped`_ range.


``utf8_decoded``
^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/utf8_decode_range.hpp>``
- Valid expression: ``biRng|utf8_decoded<>()``
- Returns: A `Bidirectional Range`_ whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.


``xpressive_matched``
^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_match_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_matched(re)`` or ``biRng|xpressive_matched(re,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_iterator``.


``xpressive_tokenized``
^^^^^^^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/xpressive_token_range.hpp>``; not included by ``<pstade/oven/ranges.hpp>``
- Valid expression: ``biRng|xpressive_tokenized(re)`` or ``biRng|xpressive_tokenized(re,subMatches,flag)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::xpressive::regex_token_iterator``.


``zipped``
^^^^^^^^^^
``zipped`` takes two range and returns a range of corresponding tuples.
If one input range is short, excess elements of the longer range are discarded.

- Header: ``<pstade/oven/zip_range.hpp>``
- Valid expression: ``rng0|zipped(rng1)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::zip_iterator``.


``zipped_with``
^^^^^^^^^^^^^^^
``zipped_with`` generalises ``zipped`` by zipping with the functor,
given as the first argument, instead of a tupling::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\zipped_with.ipp


- Header: ``<pstade/oven/zip_with_range.hpp>``
- Valid expression: ``rng0|zipped_with(rng1, rfun)``
- Returns: A range whose values are zipped by using ``rfun``.



Acknowledgments
---------------
- `P-Stade`_
- `Boost C++ Libraries`_
- `Boost.Range`_
- `Boost.RangeEx`_
- `Range Library Proposal`_



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Released initial version.

Version 0.90.1
^^^^^^^^^^^^^^
- Updated this document.
- Implemented `Range Algorithms`_.
- Added some `Ranges`_ and `Range Adaptors`_.

Version 0.90.2
^^^^^^^^^^^^^^
- Added some `Range Adaptors`_.
- Changed the header of `permuted`_.
- Changed the header of `pointed`_.
- Changed a valid expression of `zipped`_.
- Changed `checked`_ to throw exception.
- Renamed ``found`` to `string_found`_.

Version 0.90.3 - 0.90.6
^^^^^^^^^^^^^^^^^^^^^^^
- Changed the header of `Range Algorithms`_.
- Added ``base_iterator``.
- Added some `Range Adaptors`_.
- Renamed ``accumulated`` to `scanned`_.
- Added workaround for `Standard Library Defect #198`__.
- Changed `constants`_ semantics, and added `always`_ instead.
- Changed `utf8_decoded`_ valid expression.
- `shared`_ accepts ``auto_ptr``.

__ http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198

Version 0.90.7
^^^^^^^^^^^^^^
- Added `matched`_, `xpressive_matched`_ and `xpressive_tokenized`_.

Version 0.90.8
^^^^^^^^^^^^^^
- Renamed ``base_iterator`` to ``to_base``.
- Renamed ``copied`` adaptor to ``copied_to``.
