<?php
include("../config.php"); //contains some useful global definitions
require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
session_start();
if($_SESSION['logged_in'] == true){
	header("Location: ./login_success.php");
} 
?>
<!DOCTYPE html>
<html>
<body>
<div id="wrap">
   <?php 
		include("../data/header.php"); // contains all information that would be shown as header. It contains also the head parameters
	?>

   <div id="content">
	<P align="center"><b>
		This is the website of the Curriculum Viewer, provided by Genius@Work! 
		<BR> To have access to all features of the website, you have to log in with your username and password.
		<BR><BR><BR><BR>
	</b></P>

      <table width="300" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#CCCCCC">
			<tr>
		<form name="form1" method="post" action="checklogin.php">
		<td>
			<table width="100%" border="0" cellpadding="3" cellspacing="1" bgcolor="#FFFFFF">
				<tr>
					<td colspan="3"><strong>Login</strong></td>
					<error>
					<?php
						if (isset($_GET['error_message']))
   						echo $_GET['error_message'];	
					?>
					</error>
				</tr>
				<tr>
					<td width="78">Username: </td>
					<td width="294"><input name="myusername" type="text" id="myusername"></td>
				</tr>
				<tr>
					<td>Password: </td>
					<td><input name="password" type="password" id="mypassword"></td>
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
   </div>
	<?php 
		include("../data/footer.php"); // contains all information that would be shown as header. It contains also the head parameters
	?>
</div>

</body>
</html>
