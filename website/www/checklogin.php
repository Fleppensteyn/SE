<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.

// username and password sent from form
$myusername=$_POST['myusername'];
$mypassword=$_POST['mypassword'];


  header("Content-type: text/plain");
  if (isset($_REQUEST["password"])) {
    $user = $_REQUEST["myusername"];
    $pw = $_REQUEST["password"];
    if (isset($_REQUEST["c"]))
        $phash = true;
    else
      $phash = false;
    $res = $GLOBALS["db"]->check_login($user, $pw, $phash);
    echo sprintf("%d|%s",$res[0],$res[1]);
  }
  else {
    echo "Deze gegevens kloppen niet! \n";
  }
  die();


?>