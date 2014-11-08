<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
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
		<li><a href="index.php">Home</a></li>
      <li><a href="logout.php">Log out</a></li>
      <li><a href="curricula.php">Curricula</a></li>
      <li><a href="vakken.php">Alle vakken weergeven</a></li>
   </ul>

   <div id="content">
      <table width="300" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC">
			<tr>
		<form name="form1" method="post" action="checklogin.php">
		<td>
			<table width="100%" border="0" cellpadding="3" cellspacing="1" bgcolor="#FFFFFF">
				<tr>
					<td colspan="3"><strong>Login</strong></td>
				</tr>
				<tr>
					<td width="78">Gebruikersnaam</td>
					<td width="6">:</td>
					<td width="294"><input name="myusername" type="text" id="myusername"></td>
				</tr>
				<tr>
					<td>Wachtwoord</td>
					<td>:</td>
					<td><input name="password" type="text" id="mypassword"></td>
				</tr>
				<tr>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td><input type="submit" name="Submit" value="Inloggen"></td>
				</tr>
			</table>
		</td>
		</form>
			</tr>
		</table>

      <pre><?php echo $content; ?></pre>

   </div>
   <h2>&#169; 2014 Genius@Work <br> Powered by Group8</br></h2>
</div>

</body>
</html>
