#!/usr/local/bin/slang

public void Main(int argc, string argv) modify {
	int result;

	int handle = mysql_init();

	writeln("mysql_real_connect()");
	mysql_real_connect(handle, "127.0.0.1", 3306, "root", "root", "ts_parking");

	mysql_close(handle);
	writeln("mysql_close()");

	writeln("done");
}
