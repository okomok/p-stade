
var cupcake_reo_whole = /(.*)/;

function cupcake_sort(array)
{
	array.sort();
}

function cupcake_for_each_elem(array, op)
{
	for (var i = 0; i < array.length; ++i)
	{
		op(array[i]);
	}
}

function cupcake_for_each_item(collection, op)
{
	var iter = new Enumerator(collection);
	for (; !iter.atEnd(); iter.moveNext())
	{
		op(iter.item());
	}
}

function cupcake_for_each_arg(_, op)
{
	var args = WScript.Arguments;
	for (var i = 0; i < args.length; ++i)
	{
		op(args(i)); // not [] but (), sucker
	}
}

// easy permutation
function cupcake_for_each_each(opForEach1, dst1, opForEach2, dst2, op)
{
	opForEach1(dst1,
		function(elem1)
		{
			opForEach2(dst2, function(elem2) { op(elem1, elem2); });
		}
	);
}


