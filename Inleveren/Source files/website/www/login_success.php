<?php
	include("../config.php"); //contains some useful global definitions
	require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
	session_start();
	if($_SESSION['logged_in'] == false){
		header("Location: ./index.php");
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
				<br>
				<?php
					echo 'Log in succesful: ' .$_SESSION['name'];
				?>
				<br><br>
				Permission granted to all Curricula and the Course Library on this website.<BR>
				Please use the menu bar at the top of this webpage to browse through all available information.      
			</div>
			<?php 
				include("../data/footer.php"); // contains all information that would be shown as footer.
			?>
		</div>
	</body>
</html>
