<?php
if ($_SERVER["REQUEST_METHOD"]!='POST' || !isset($_REQUEST["a"]))
  die();

include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."database.php");

header("Content-type: text/plain");
if ($_POST["a"] == "login"){
  $db = new DatabaseAccess(DATA_ROOT.DB_NAME, DATA_ROOT.DB_USERS);
  $res = $db->check_login($_POST["u"], $_POST["p"], true);
  echo $res[0]."|".$res[1];
  die();
} elseif ($_POST["a"] == "export"){
  $db = new DatabaseAccess(DATA_ROOT.DB_NAME, DATA_ROOT.DB_USERS);
  if (!isset($_POST["l"])) die();
  $msg = "";
  $logindata = explode("|",$_POST["l"]);
  $res = $db->check_login($logindata[0], $logindata[1], true);
  if ($res[0] != 2){
    $msg = "0|Not authorized";
  } elseif (isset($_FILES["db"])){
    $file = $_FILES["db"];
    if ($file["error"] == 0 &&
        $file["size"] > 1024 && $file["name"] == "client.db"){
      if (move_uploaded_file($file["tmp_name"], DATA_ROOT."client.db"))
        $msg = "1|Database uploaded successfully";
      else
        $msg = "0|Error moving database file";
    } else
        $msg = "0|Database file doesn't meet basic criteria";
  } else $msg = "0|No file uploaded";
  echo $msg;
}
die();
?>