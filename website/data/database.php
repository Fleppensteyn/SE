<?php
require_once("../config.php");

//Handles all database contact
class DatabaseAccess
{
  private $db; //database connection
  private $filename;//filename for the database

  //Get an instance with access to the database
  //$file is the filename for the SQLite database
  public function __construct($file, $userfile){
    $this->filename = $file;
    $this->userfile = $userfile;
    $this->db = NULL;
    $this->userdb = NULL;
    if (!file_exists($file)){
      throw new Exception("Database error: '$file' could not be found");
    } elseif (!file_exists($userfile)) {
      throw new Exception("Database error: '$userfile' could not be found");
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
    if ($this->userdb == NULL)
      $this->userdb = new SQLite3($this->userfile);
  }

  //Close the database connection
  private function close(){
    if ($this->db != NULL)
      $this->db->close();
    if ($this->userdb != NULL)
      $this->userdb->close();
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
  private function result_array($query, $verb = false, $db = NULL){
   if($verb) echo "Executing: $query\n";
    if ($db == NULL) $db = $this->db;
    $res = $db->query($query);
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
  //Returns an array containing an integer and a message with more info.
  //        -1 if there is no matching user [LOGIN_ERROR]
  //         0 if the user has been banned  [LOGIN_BANNED]
  //         1 if the user is a normal user [LOGIN_USER]
  //         2 if the user is an admin      [LOGIN_ADMIN]
  public function check_login($user, $pass, $prehashed = false){
    if (strlen($user) < 4)
      return array(LOGIN_ERROR,"Username too short");
    elseif (strlen($pass) < 1)
      return array(LOGIN_ERROR,"No password entered");
    elseif (!preg_match("/^[\w\-\.@]+$/",$user))
      return array(LOGIN_ERROR,"Username contains illegal character(s)");
    elseif ($prehashed && !preg_match("/^[\da-f]{40}$/",$pass))
      return array(LOGIN_ERROR,"Invalid password hash");
    elseif (!$prehashed && !preg_match("/^[\w\-\.@!]+$/", $pass))
      return array(LOGIN_ERROR,"Password contains illegal character(s)");

    $hashed = $this->pwhash($user, $pass, $prehashed);
    $res = $this->result_array(sprintf("SELECT pass, class FROM users WHERE name='%s';", 
                               strtolower($user)), false, $this->userdb);
    if (count($res)==0)
      return array(-1,"Unknown username '$user'");

    $res = $res[0];
    if ($res['pass'] == $hashed)
      return array($res["class"], "Login correct");
    else
      return array(LOGIN_ERROR,"Invalid password");
  }

  public function generate_curricula()
  {
  // TODO: Genereer data
    echo "0";
    $res = $this->result_array("SELECT pass, class FROM users", true);
    echo "0";
    echo $res[0]['class'];
    echo "0";
  }

  public function do_query($query){
    $res = $this->result_array($query, false);
    return $res;
  }
}
?>
