#!/usr/bin/env slang

	public void Main(int argc, string argv) modify {
		int error;
		int result;

		int handle = mysql_init();
		writeln("mysq_init() = " + handle);

		handle = mysql_real_connect(handle, "127.0.0.1", 3306, "root", "root", "");
		writeln("mysql_real_connect() = " + handle);

		error = mysql_select_db(handle, "ts_parking");
		if ( error ) {
			writeln("error while selecting database: " + error);
			return;
		}

		string query = "SELECT * FROM parking_zones";

		error = mysql_query(handle, query);
		writeln("mysql_query(" + handle + ", \"" + query + "\") = " + error);
		if ( error ) {
			writeln("mysql_error(" + handle + ") = " + mysql_error(handle));
			return;
		}

		result = mysql_store_result(handle);
		writeln("mysql_store_result(" + handle + ") = " + result);

		int numRows = mysql_num_rows(result);
		writeln("mysql_num_rows(" + result + ") = " + numRows);

		int numFields = mysql_num_fields(result);
		writeln("mysql_num_fields(" + result + ") = " + numFields);

		bool printHeader = true;
		while ( mysql_fetch_row(result) ) {
			string fields;
			string values;

			for ( int fieldId = 0; fieldId < numFields; fieldId = fieldId + 1) {
				fields = fields + " | " +  mysql_get_field_name(result, fieldId);
				values = values + " | " +  mysql_get_field_value(result, fieldId);
			}

			if ( printHeader ) {
				printHeader = false;
				writeln(fields);
			}
			writeln(values);
		}

		mysql_close(handle);
		writeln("mysql_close(" + handle + ")");

		writeln("done");
	}
