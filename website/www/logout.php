<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
session_start();
session_destroy();
header("Location: ./index.php");
?>