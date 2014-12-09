<?php
	//Folder with includes that don't need to be addressed directly
	define("DATA_ROOT","/home/se/data/");
	//The filename for the SQLite databases
	define("DB_NAME","client.db");//all data for the application
	define("DB_USERS","server.db");//login details
	//The root for the folder with the publicly accessible files.
	define("WWW_ROOT","/home/se/www/");
	//The salt for password hashing.
	define("SALT","pls");

	require_once(DATA_ROOT."constants.php");//load the constants.
?>