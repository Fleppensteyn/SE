<?php
if ($_SERVER["REQUEST_METHOD"]!='POST' || !isset($_REQUEST["a"]))
  die();

include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."database.php");

header("Content-type: text/plain");
if ($_POST["a"] == "login"){
  $db = new DatabaseAccess(DATA_ROOT.DB_NAME);
  $res = $db->check_login($_POST["u"], $_POST["p"], true);
  echo $res[0]."|".$res[1];
  die();
}
die();
?>