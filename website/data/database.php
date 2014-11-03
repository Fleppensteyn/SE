<?php
require_once("../config.php");

//Handles all database contact
class DatabaseAccess
{
  private $db; //database connection
  private $filename;//filename for the database

  //Get an instance with access to the database
  //$file is the filename for the SQLite database
  public function __construct($file){
    $this->filename = $file;
    $this->db = NULL;
    if (!file_exists($file)){
      throw new Exception("Database error: '$file' could not be found");
    } else {
      $this->connect();
    }
  }

  public function __destruct(){
    $this->close();
  }

  /* This is only useful if you serialize this object in the session data
  public function __wakeup(){
    $this->db = NULL;
    $this->connect();
  }*/

  //Connect to the database
  private function connect(){
    if ($this->db == NULL)
      $this->db = new SQLite3($this->filename);
  }

  //Close the database connection
  private function close(){
    if ($this->db!=NULL)
      $this->db->close();
  }

  //Creates an array of associative arrays for a given resultset
  //$res is the result set
  //Returns the array of associative arrays
  private function result_to_assoc($res){
    $r = array();
    while ($r[] = $res->fetchArray(SQLITE3_ASSOC));
    unset($r[count($r)-1]);
    return $r;
  }

  //Executes a query and returns an array containing the full results
  //$query - is the query to execute
  //$verb  - determines if some output is printed [false]
  //Returns the result of a query in an array of associative arrays
  private function result_array($query, $verb = false){
    if($verb) echo "Executing: $query\n";
    $res = $this->db->query($query);
    $r = $this->result_to_assoc($res);
    $res->finalize();
    return $r;
  }

  //Execute a query and dump the result set to stdout
  //$query - the query to execute
  public function dump_query($query){
    var_dump($this->result_array($query,true));
  }
  
  //Generate the hash for the provided values
  //$user     - the username of the user
  //$pw       - the password
  //$prehashed- The desktop client sends a hash instead of the actual password,
  //            so if this is set to false it will not do the hashing that was
  //            done on the client application again. [false]
  //Returns the hash for the given details
  private function pwhash($user,$pw, $prehashed = false){
    $user = strtolower($user);
    if(!$prehashed) $pw = sha1($pw);
    return sha1(SALT.md5(sha1($user).SALT.sha1($pw)).SALT);
  }

  //Check the provided login data and return the user level and a message
  //$user     - the username
  //$pass     - the password
  //$prehashed- The desktop client already hashes the password once, so if you
  //            set this to true it won't hash it again.
  //Returns -1 if the provided credentials do not match anything in the database
  //         0 if the user has been banned
  //         1 if the user is a normal user
  //         2 if the user is an admin
  public function check_login($user, $pass, $prehashed = false){
    if (strlen($user) < 4){
      echo "Error: Username too short";
      return -1;
    }
    if (strlen($pass) < 1){
      echo "Error: No password entered";
      return -1;
    }
    if(!preg_match("/^[\w\-\.]+$/",$user)){
      echo "Error: Username contains illegal character(s)";
      return -1;
    }
    if($prehashed && !preg_match("/^[\da-f]{40}$/",$pass)){
      echo "Error: Invalid password hash";
      return -1;
    } elseif (!$prehashed && !preg_match("/^[\w\-\.]+$/", $pass)) {
      echo "Error: Password contains illegal character(s)";
      return -1;
    }
    $hashed = $this->pwhash($user, $pass, $prehashed);
    $res = $this->result_array(sprintf("SELECT pass, class FROM users WHERE name='%s';",strtolower($user)));
    if (count($res)==0){
      echo "Error: Unknown username '$user'";
      return -1;
    }
    $res = $res[0];
    if ($res['pass'] == $hashed){
      echo "Login correct";
      return $res["class"];
    }else {
      echo "Error: Invalid password";
      return -1;
    }
  }
}
?>
