<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.

ob_start(); //buffer the next output instead of printing directly
echo "Testing database with a generic query\n";
$GLOBALS["db"]->dump_query('SELECT id, name, class FROM users;');
$content = ob_get_clean(); //save the buffer to a variable
?>
<!DOCTYPE html>
<html>
<head>
   <link rel="stylesheet" href="genius.css">
   <title>Curriculum Viewer</title>
</head>

<body>

<div id="wrap">
   <h1>Curriculum Viewer</h1>

   <ul id="nav">
      <li><a href="#">Log in</a></li>
   </ul>

   <div id="content">
      <p>Test</p>
      <pre><?php echo $content; ?></pre>

   </div>
   <h2>&#169; 2014 Genius@Work <br> Powered by Group8</br></h2>
</div>

</body>
</html>
