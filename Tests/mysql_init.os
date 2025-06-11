#!/usr/bin/env slang

public void Main(int argc, string argv) modify {
	int handle = mysql_init();
	writeln("mysql_init() = " + handle);

	writeln("done.");
}
