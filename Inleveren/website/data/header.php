<?php
	include("../config.php"); //contains some useful global definitions
	require(DATA_ROOT."core.php");//Include everywhere for session related stuff
	session_start();
?>	

<!-- for the dropdown menu -->
<script language="JavaScript">
	sfHover = function() {
		var sfEls = document.getElementById("nav").getElementsByTagName("LI");
		for (var i=0; i<sfEls.length; i++) {
			sfEls[i].onmouseover=function() {
				this.className+=" ie_does_hover";
			}
			sfEls[i].onmouseout=function() {
				this.className=this.className.replace(new RegExp(" ie_does_hover\\b"), "");
			}
		}
	}
	if (window.attachEvent) window.attachEvent("onload", sfHover);
</script> 

<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" href="genius.css">
		<title>Curriculum Viewer</title>
		<link rel="shortcut icon" href="./Icon.ico">
		<meta charset="UTF-8">
	</head>

	<body>
		<h1>Curriculum Viewer</h1>
		
		<!-- menu -->
		<?php 
			$query= "SELECT name FROM curriculum ORDER BY name;";
			$res= $GLOBALS["db"]->do_query($query);
			$counted = count($res, 0);
			
			echo '<ul id="nav">';
			echo '<li><a href="index.php">Home</a></li>'; //set index.php
			if(isset($_SESSION['logged_in']) || $_SESSION['logged_in'] == true){ // if logged in-> logout button must be shown
				echo '<li><a href="logout.php">Log out</a></li>';
			}
			echo '<li><a href="curricula.php?c=0">Curricula</a>'; // set curricula.php
			echo '<ul style="border: 1px solid #ccc; border-bottom: 0px;">';
			if(isset($_SESSION['logged_in']) || $_SESSION['logged_in'] == true){
				for ($i = 0; $i < $counted; $i++){ // if logged in -> curricula.php- curriculum must be shown, else not
					echo '<li><a href="curricula.php?c='.$i.'">'.$res[$i]["name"].'</a></li><div id="clear"></div>';
				}
			}
			echo '</ul></li>';
			echo '<li><a href="courses.php">Course library</a></li>';
			echo '</ul> ';
		?>
	</body>
</html>
