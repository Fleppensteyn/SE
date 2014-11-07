<?php
//Folder with includes that don't need to be addressed directly
define("DATA_ROOT","/home/se/data/");
//The filename for the main SQLite database
define("DB_NAME","server.db");
//The root for the folder with the publicly accessible files.
define("WWW_ROOT","/home/se/www/");
//The salt for password hashing.
define("SALT","pls");

require_once(DATA_ROOT."constants.php");//load the constants.
?>