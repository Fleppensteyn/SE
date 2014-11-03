<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.

header("Content-type: text/plain");
echo "Testing database with a generic query\n";
$GLOBALS["db"]->dump_query('SELECT id, name, class FROM users;');
?>
