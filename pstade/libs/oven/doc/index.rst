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
The next `Boost.Range`_ library is under construction.
Oven provides some ranges and `Range Adaptors`_ for those who cannot wait for the official.
All the types and functions are defined in ``namespace pstade::oven`` at ``<pstade/oven.hpp>``.



Requirements
------------
- `Boost C++ Libraries Version 1.33.1`__ or later (no compilation required)
- `P-Stade C++ Libraries Version 0.98.5`__ or later (no compilation required, give a higher priority than Boost headers)

__ Boost_
__ http://sourceforge.net/project/showfiles.php?group_id=141222&package_id=173059



Tested Under
------------
- Microsoft Visual C++ 2005 Express Edition
- Microsoft Visual C++ .NET Version 7.1
- GCC 3.4.4



Ranges
------


array_range
^^^^^^^^^^^
- Valid expression: ``array_range<T> rng(sz);``
- Returns: ``[&arr, &arr+sz)``, where ``arr`` is initialized by the expression ``boost::scoped_array<T> arr(new T[sz]);``.


counting_range
^^^^^^^^^^^^^^
- Valid expression: ``counting_range<I> rng(n, m);``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::counting_iterator``.


directory_range
^^^^^^^^^^^^^^^
- Valid expression: ``directory_range rng(path);``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::directory_iterator``.


empty_range
^^^^^^^^^^^
- Valid expression: ``empty_range<T> rng;``
- Returns: ``[static_cast<T *>(0), static_cast<T *>(0))``.


file_range
^^^^^^^^^^
- Valid expression: ``file_range<> rng;``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::file_iterator``.


istream_range
^^^^^^^^^^^^^
- Valid expression: ``istream_range<Value> rng(stream);``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``std::istream_iterator``.


single_range
^^^^^^^^^^^^
- Valid expression: ``single_range<T> rng(v);``
- Precondition: The type of ``v`` is ``T``.
- Returns: ``[&v, &v+1)``.



Range Adaptors
--------------
A Range Adaptor delivers an altered presentation of one or more underlying ranges.
Range Adaptors are lazy, meaning that their elements are only computed on demand.
The underlying ranges are not modified.


appended
^^^^^^^^
- Valid expression: ``rng|appended(v)``
- Precondition: ``v *`` is convertible to the ``iterator`` type of ``rng``.
- Returns: ``rng|jointed(make_single_range(v))``.


array_protected
^^^^^^^^^^^^^^^
- Valid expression: ``arr|array_protected``
- Precondition: ``arr`` is an array.
- Returns: ``[boost::begin(arr), boost::begin(arr)+sz)``, where ``sz`` is the size of ``arr``.


adjacent_filtered
^^^^^^^^^^^^^^^^^
- See: `Range Adaptors`_.


filtered
^^^^^^^^
- See: `Range Adaptors`_.


directed
^^^^^^^^
- Valid expression: ``rng|directed``
- Returns: ``make_counting_range(boost::begin(rng), boost::end(rng))``.


found
^^^^^
- Valid expression: ``rng|found(finder)``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::find_iterator``.


indirected
^^^^^^^^^^
- See: `Range Adaptors`_.


jointed
^^^^^^^
- Valid expression: ``rng1|jointed(rng2)``
- Precondition: The ``iterator`` type of ``rng2`` is convertible to ``rng1``\'s.
- Returns: A range that joints ``[boost::begin(rng1), boost::end(rng1))`` and ``[boost::begin(rng2), boost::end(rng2))``.


multi_passed
^^^^^^^^^^^^
- Valid expression: ``rng|multi_passed``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::multi_pass``.


null_terminated
^^^^^^^^^^^^^^^
- Valid expression: ``rngOrString|null_terminated``
- Precondition: ``rngOrString`` is a string literal; Otherwise for all the value ``v`` in the ``rngOrString``, the expression ``v == 0`` must be valid, and some ``v`` that the expression is ``true`` exists in the ``rngOrString``.
- Returns: ``[boost::begin(rng), y)``, where for all the value ``v`` in the range ``v != 0`` is ``true``, and ``*y == 0`` is ``true``.


permuted
^^^^^^^^
- Valid expression: ``rng|permuted(irng)``
- Precondition: ``rng`` is a `Random Access Range`_ and ``irng`` is a range of the indices.
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::permutation_iterator``.


pointed
^^^^^^^
- Valid expression: ``vec|pointed``
- Precondition: ``vec`` is the template instantiation of ``std::vector``.
- Returns: ``[&*boost::begin(vec), &*boost::begin(vec)+boost::size(vec))``.


positioned
^^^^^^^^^^
- Valid expression: ``rng|positioned``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::spirit::position_iterator``.


prepended
^^^^^^^^^
- Valid expression: ``rng|prepended(v)``
- Precondition: The ``iterator`` type of ``rng`` is convertible to ``v *``.
- Returns: ``make_single_range(v)|jointed(rng)``.


repeated
^^^^^^^^
- Valid expression: ``rng|repeated(i)``
- Returns: A range that repeats ``[boost::begin(rng), boost::end(rng))`` ``i`` times.


reversed
^^^^^^^^
- See: `Range Adaptors`_.


shared
^^^^^^
- Valid expression: ``new Range|shared``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::shared_container_iterator``.


sliced
^^^^^^
- See: `Range Adaptors`_.


sorted
^^^^^^
- Valid expression: ``rng|sorted`` or ``rng|sorted(pred)``
- Returns: A sorted view of ``rng``.


tokenized
^^^^^^^^^
- See: `Range Adaptors`_.


transformed
^^^^^^^^^^^
- See: `Range Adaptors`_.


uniqued
^^^^^^^
- See: `Range Adaptors`_.


unzipped
^^^^^^^^
- Valid expression: ``zipped_rng|unzipped<N>()``
- Returns: A unzipped range.


utf8_decoded
^^^^^^^^^^^^
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::u8_to_u32_iterator``.


zipped
^^^^^^^
- Valid expression: ``boost::tie(rng0, rng1, ..., rngN)|zipped``
- Returns: A range whose iterators behave as if they were the original iterators wrapped in ``boost::zip_iterator``.



Range Algorithms
----------------
Oven has all the range-based STL algorithms which are ported from `Boost.RangeEx`_.

- Valid expression: ``algo(rng, f);``
- Precondition: ``algo(boost::begin(rng), boost::end(rng), f);``, where ``algo`` is one of the STL algorithms.


Utilities
---------

sequence
^^^^^^^^
- Valid expression: ``seq = sequence(rng);``
- Precondition: ``seq`` is a `Sequence`_.
- Semantics: ``seq = boost::copy_range<Sequence>(rng);``, where ``Sequence`` is the type of ``seq``.

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
- Implemented `Range Algorithms`_.
- Added some `Ranges`_ and `Range Adaptors`_.

