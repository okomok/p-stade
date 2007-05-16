
// cupcake/basic.js required

var _fs = WScript.CreateObject("Scripting.FileSystemObject");

var cupcake_ForReading = 1, cupcake_ForWriting = 2, cupcake_ForAppending = 8;
var cupcake_TristateUseDefault = -2, cupcake_TristateTrue = -1, cupcake_TristateFalse = 0;
var cupcake_IsCreate = true;

function cupcake_traverse_file(folder, op)
{
	cupcake_for_each_file(folder, op);
	cupcake_for_each_subFolder(
		folder,
		function(subFolder) { cupcake_traverse_file(subFolder, op); }
	);
}

function cupcake_traverse_folder(folder, op)
{
	cupcake_for_each_subFolder(folder, op);
	cupcake_for_each_subFolder(
		folder,
		function(subFolder) { cupcake_traverse_folder(subFolder, op); }
	);
}

function cupcake_for_each_file(folder, op)
{
	cupcake_for_each_item(folder.files, op);
}

function cupcake_for_each_subFolder(folder, op)
{
	cupcake_for_each_item(folder.subFolders, op);
}

function cupcake_directory_path(path)
{
	return path.replace(/\\[^\\]+$/i, "");
}

function cupcake_file_name(path)
{
	return path.match(/[^\\]+$/i);
}

function cupcake_this_folder_path()
{
// Note. getFolder("."), shell.currentDirectory, incredible with Arguments
	var nameThis = WScript.ScriptFullName;
	return cupcake_directory_path(nameThis);
}

function cupcake_this_folder_file_path(filename)
{
	return _fs.BuildPath(cupcake_this_folder_path(), filename);
}

function cupcake_for_each_line_stream(ts, op)
{
	var i = 0;
	while (!ts.atEndOfStream)
	{
		var line = ts.readLine();
		if (line != "")
			op(line, i++);
	}
}

function cupcake_for_each_line_file(file, op)
{
	var ts = file.openAsTextStream(1);
	var i = 0;
	while (!ts.atEndOfStream)
	{
		var line = ts.readLine();
		if (line != "")
			op(line, i++);
	}
	ts.close();
}

function cupcake_unique_file_path(path, opBase)
{
	var newPath = path;
	var base = _fs.getBaseName(path);
	var ext = _fs.getExtensionName(path);
	var folder = _fs.getParentFolderName(path);
	var i = 0;
	while (_fs.fileExists(newPath))
	{
		var newBase = opBase(base, i);
		newPath = _fs.buildPath(folder, newBase + "." + ext);
		++i;
	}
	return newPath;
}

function cupcake_unique_file_copy(srcPath, dstPath, opBase)
{
	var newPath = cupcake_unique_file_path(dstPath, opBase);
	_fs.copyFile(srcPath, newPath);
}

function cupcake_download_file(url)
{
	var xml = WScript.CreateObject("Microsoft.XMLHTTP");
	xml.open("GET", url, false);
	xml.send();

	if (xml.status < 200 || xml.status >= 300)
	{
		WScript.echo(xml.statusText);
		return "";
	}
	
	return xml.responseText;
}

function cupcake_wrap_path(path)
{
	return " \"" + path + "\" ";
}
