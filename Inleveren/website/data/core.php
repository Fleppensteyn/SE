<?php
session_start();
require_once(DATA_ROOT."database.php");
$GLOBALS["db"] = new DatabaseAccess(DATA_ROOT.DB_NAME, DATA_ROOT.DB_USERS);


/* This is something related to data storage between sessions, not useful for now.
if(isset($_SESSION["database"])){
  $GLOBALS["db"] = unserialize($_SESSION["database"]);
} else {
  try {
    $GLOBALS["db"] = new DatabaseAccess(DATA_ROOT.DB_NAME);
  } catch (Exception $e) {
    error_log($e->getMessage());
    echo "Database error";
    die();
  }
}
function save_db($db){
  $_SESSION["database"] = serialize($db);
}
register_shutdown_function('save_db',$GLOBALS["db"]);*/

?>