++++++++++++++++++++++
The Oven Range Library
++++++++++++++++++++++

.. include:: ../../doc/refs.rst

:Author: MB
:Contact: mb2act@yahoo.co.jp 
:License: Distributed under the `Boost Software License Version 1.0`_
:Version: 0.90.1



.. epigraph::

	"*Oh Paulie!*"
	
	-- Adrian



.. contents:: **Table of Contents**
.. section-numbering::



Introduction
------------
The upcoming `Boost.Range`_ library is under construction.
Oven provides some ranges and `Range Adaptors`_ for those who cannot wait for the official::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\introduction.ipp

All the types and functions are defined in ``namespace pstade::oven`` at ``<pstade/oven.hpp>``.


Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 0.99.7`__ or later (no compilation required, give a higher priority than Boost headers)

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
``<pstade/oven/algorithms.hpp>`` includes all the following functions.


STL
^^^
Oven has all the range-based STL algorithms which are ported from `Boost.RangeEx`_ with some compiler workarounds::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\algorithms.ipp


- Header: ``<pstade/oven/algorithm.hpp>``
- Valid expression: ``oven::algo(rng,a0,a1,...,aN);``
- Precondition: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);`` is a valid expression, where ``algo`` is one of the STL algorithms.
- Returns: ``std::algo(boost::begin(rng),boost::end(rng),a0,a1,...,aN);``


construct
^^^^^^^^^
``construct`` adds the automatic type deduction to `copy_range`_::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\construct.ipp

.. _copy_range: http://www.boost.org/libs/range/doc/utility_class.html#copy_range


- Header: ``<pstade/oven/construct.hpp>``
- Valid expression: ``seq = sequence(rng);``
- Precondition: ``seq = boost::copy_range<Seq>(rng);`` is a valid expression, and ``Seq`` is not a dependent name.
- Semantics: ``seq = boost::copy_range<Seq>(rng);``


copies
^^^^^^
``copies`` takes two ranges and checks the bounds under debug mode.
Prefer ``copies`` to ``copy`` everywhere possible::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\copies.ipp

- Header: ``<pstade/oven/copies.hpp>``
- Valid expression: ``oven::copies(rng1,rng2);``
- Precondition: ``boost::size(rng1) <= boost::size(rng2)`` is ``true``, and ``oven::copies(rng1,boost::begin(rng2));`` is a valid expression.


distance
^^^^^^^^
The upcoming `Boost.Range`_ will replace ``boost::size`` by ``boost::distance``.
``oven::distance`` that is the same as ``boost::distance`` makes your code portable.


- Header: ``<pstade/oven/distance.hpp>``
- Valid expression: ``oven::distance(rng);``
- Precondition: ``std::distance(boost::begin(rng),boost::end(rng));`` is a valid expression.
- Returns: ``std::distance(boost::begin(rng),boost::end(rng))``


equals
^^^^^^
``equals`` is the range-based ``std::equal`` that takes two ranges as the arguments.
Note that the size of two ranges is also checked out.

- Header: ``<pstade/oven/equals.hpp>``
- Valid expression: ``oven::equals(rng1,rng2);``
- Precondition: ``oven::equal(rng1,boost::begin(rng2));`` is a valid expression.
- Returns: ``true`` if and only if the ``oven::equal(rng1,boost::begin(rng2))`` and ``boost::size(rng1) == boost::size(rng2)`` returns ``true``.



Ranges
------
Oven provides some predefined range types.
``<pstade/oven/ranges.hpp>`` includes all the following ranges except for
`directory_range`_ and `tokenized`_.


array_range
^^^^^^^^^^^
``array_range`` is a model of `Random Access Range`_ which delivers
a range presentation of dynamically allocated arrays::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\array_range.ipp


- Header: ``<pstade/oven/array_range.hpp>``
- Valid expression: ``array_range<T> rng(sz);``
- Precondition: ``new T[sz];`` is a valid expression.


counting_range
^^^^^^^^^^^^^^
``counting_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `counting_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\counting_range.ipp

__ http://www.boost.org/libs/iterator/doc/counting_iterator.html


- Header: ``<pstade/oven/counting_range.hpp>``
- Valid expression: ``counting_range<I,T,D> rng(n,m);`` and ``oven::make_counting_range(n,m);``
- Precondition: ``boost::couting_iterator<I,T,D>(x);`` is a valid expression, where
  ``x`` is ``n`` or ``m``.


directory_range
^^^^^^^^^^^^^^^
``directory_range`` is a range whose iterators behave as if
they were the original iterators wrapped in `directory_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\directory_range.ipp

__ http://www.boost.org/libs/filesystem/doc/operations.htm#directory_iterator


- Header: ``<pstade/oven/directory_range.hpp>``
- Valid expression: ``directory_range rng(p);`` and ``wdirectory_range wrng(wp);``
- Precondition: The type of ``p`` is ``boost::filesystem::path`` and
  the type of ``wp`` is ``boost::filesystem::wpath``.


empty_range
^^^^^^^^^^^
``empty_range`` is a `Random Access Range`_ which is always empty::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\empty_range.ipp
	

- Header: ``<pstade/oven/empty_range.hpp>``
- Valid expression: ``empty_range<T> rng;``


file_range
^^^^^^^^^^
``file_range`` is a range whose iterators behave as if they were the original iterators wrapped in `file_iterator`__.
the member ``is_open()`` returns ``true`` if and only if the file opening is succeeded.
If ``is_open()`` is not ``true``, the range is empty::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\file_range.ipp

__ http://www.boost.org/libs/spirit/doc/file_iterator.html


- Header: ``<pstade/oven/file_range.hpp>``
- Valid expression: ``file_range<C> rng;`` and ``rng.is_open();``
- Precondition: ``boost::spirit::file_iterator<C>`` is a valid expression.


istream_range
^^^^^^^^^^^^^
``istream_range`` is a range whose iterators behave as if they were the original iterators wrapped in `istream_iterator`__::

	D:\p-stade.sourceforge.net\pstade\libs\oven\doc\inline\istream_range.ipp

__ http://www.sgi.com/tech/stl/istream_iterator.html



- Header: ``<pstade/oven/istream_range.hpp>``
- Valid expression: ``istream_range<V,C,T,D> rng(stm);`` and  ``oven::make_istream_range<V>(stm);``
- Precondition: ``std::istream_iterator<V,C,T,D>(stm)`` is a valid expression.


single_range
^^^^^^^^^^^^
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
``<pstade/oven/ranges.hpp>`` includes all the following Range Adaptors.


appended
^^^^^^^^
- Header: ``<pstade/oven/append_range.hpp>``
- Valid expression: ``rng|appended(v)``
- Precondition: ``v*`` is convertible to the ``iterator`` type of ``rng``.
- Returns: ``rng|jointed(oven::make_single_range(v))``.


array_protected
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/array_protect_range.hpp>``
- Valid expression: ``arr|array_protected``
- Precondition: ``arr`` is an array.
- Returns: ``[boost::begin(arr), boost::begin(arr)+sz)``, where ``sz`` is the size of ``arr``.


adjacent_filtered
^^^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/adjacent_filter_range.hpp>``
- See: `Range Library Proposal`_.


filtered
^^^^^^^^
- Header: ``<pstade/oven/filter_range.hpp>``
- See: `Range Library Proposal`_.


directed
^^^^^^^^
- Header: ``<pstade/oven/direct_range.hpp>``
- Valid expression: ``rng|directed``
- Returns: ``oven::make_counting_range(boost::begin(rng), boost::end(rng))``.


found
^^^^^
- Header: ``<pstade/oven/find_range.hpp>``
- Valid expression: ``rng|found(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::find_iterator``.


indirected
^^^^^^^^^^
- Header: ``<pstade/oven/indirect_range.hpp>``
- See: `Range Library Proposal`_.


jointed
^^^^^^^
- Header: ``<pstade/oven/joint_range.hpp>``
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``iterator`` type of ``rng2`` is convertible to ``rng1``\'s.
- Returns: A range that joints ``[boost::begin(rng1), boost::end(rng1))`` and ``[boost::begin(rng2), boost::end(rng2))``.


map_keys
^^^^^^^^
- Header: ``<pstade/oven/map_key_range.hpp>``
- See: `Range Library Proposal`_.


map_values
^^^^^^^^^^
- Header: ``<pstade/oven/map_value_range.hpp>``
- See: `Range Library Proposal`_.


multi_passed
^^^^^^^^^^^^
- Header: ``<pstade/oven/multi_pass_range.hpp>``
- Valid expression: ``rng|multi_passed``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::multi_pass``.


null_terminated
^^^^^^^^^^^^^^^
- Header: ``<pstade/oven/null_terminate_range.hpp>``
- Valid expression: ``rngOrString|null_terminated``
- Precondition: ``rngOrString`` is a string literal; Otherwise for all the value ``v`` in the ``rngOrString``, the expression ``v == 0`` must be valid, and some ``v`` that the expression is ``true`` exists in the ``rngOrString``.
- Returns: ``[boost::begin(rng), y)``, where for all the value ``v`` in the range ``v != 0`` is ``true``, and ``*y == 0`` is ``true``.


permuted
^^^^^^^^
- Header: ``<pstade/oven/permutation_range.hpp>``
- Valid expression: ``rng|permuted(irng)``
- Precondition: ``rng`` is a `Random Access Range`_ and ``irng`` is a range of the indices.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::permutation_iterator``.


pointed
^^^^^^^
- Header: ``<pstade/oven/pointer_range.hpp>``
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is the template instantiation of ``std::vector``.
- Returns: ``[&*boost::begin(vec), &*boost::begin(vec)+boost::size(vec))``.


positioned
^^^^^^^^^^
- Header: ``<pstade/oven/position_range.hpp>``
- Valid expression: ``rng|positioned``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::position_iterator``.


prepended
^^^^^^^^^
- Header: ``<pstade/oven/prepend_range.hpp>``
- Valid expression: ``rng|prepended(v)``
- Precondition: The ``iterator`` type of ``rng`` is convertible to ``v*``.
- Returns: ``oven::make_single_range(v)|jointed(rng)``.


repeated
^^^^^^^^
- Header: ``<pstade/oven/repeat_range.hpp>``
- Valid expression: ``rng|repeated(i)``
- Returns: A range that repeats ``[boost::begin(rng), boost::end(rng))`` ``i`` times.


reversed
^^^^^^^^
- Header: ``<pstade/oven/reverse_range.hpp>``
- See: `Range Library Proposal`_.


shared
^^^^^^
- Header: ``<pstade/oven/share_range.hpp>``
- Valid expression: ``new Range|shared``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::shared_container_iterator``.


sliced
^^^^^^
- Header: ``<pstade/oven/slice_range.hpp>``
- See: `Range Library Proposal`_.


sorted
^^^^^^
- Header: ``<pstade/oven/sort_range.hpp>``
- Valid expression: ``rng|sorted`` or ``rng|sorted(pred)``
- Returns: A sorted view of ``rng``.


tokenized
^^^^^^^^^
- Header: ``<pstade/oven/token_range.hpp>``
- See: `Range Library Proposal`_.


transformed
^^^^^^^^^^^
- Header: ``<pstade/oven/transorm_range.hpp>``
- See: `Range Library Proposal`_.


uniqued
^^^^^^^
- Header: ``<pstade/oven/unique_range.hpp>``
- See: `Range Library Proposal`_.


unzipped
^^^^^^^^
- Header: ``<pstade/oven/unzip_range.hpp>``
- Valid expression: ``zipped_rng|unzipped<N>()``
- Returns: A unzipped range.


utf8_decoded
^^^^^^^^^^^^
- Header: ``<pstade/oven/utf8_decode_range.hpp>``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.


zipped
^^^^^^^
- Header: ``<pstade/oven/zip_range.hpp>``
- Valid expression: ``boost::tie(rng0,rng1,...,rngN)|zipped``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::zip_iterator``.



References
----------
- `P-Stade`_
- `Boost C++ Libraries`_
- `Boost.Range`_
- `Boost.RangeEx`_
- `Range Library Proposal`_



Release Notes
-------------

Version 0.90.0
^^^^^^^^^^^^^^
- Initial version released.

Version 0.90.1
^^^^^^^^^^^^^^
- Updated this document.
- Implemented `Range Algorithms`_.
- Added some `Ranges`_ and `Range Adaptors`_.

