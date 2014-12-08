<?php
	include("../config.php"); //contains some useful global definitions
	require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
	session_start();

	if(!isset($_SESSION['logged_in']) || $_SESSION['logged_in'] == false){
		 header('Location: ./index.php?error_message=Please log in to access this page.');
		 exit();
	} 
?>

<!DOCTYPE html>
<html>
	<body>
		<div id="wrap">
			<?php 
				include("../data/header.php"); // contains all information that would be shown as header. It contains also the head parameters
			?>
				
			<!-- content -->
			<div id="content">
			
				<!-- refresh by given value in form -->
				<script>
					function change(){
						document.getElementById("myform").submit();
					}
				</script>
				<?php
						// dropdownlist for sorting by course_type
					$query= 'SELECT DISTINCT name FROM course_types ORDER BY name;';
					$res= $GLOBALS["db"]->do_query($query);
					$counted = count($res, 0);
					echo "<div id='sortbox'>Filter by course type: <br>" . '<form id="myform" method="post">';
					echo "<select name= 'type' onchange='change()'>";
					echo "<option value='show'>Show everything</option>";
					for ($i = 0; $i < $counted; $i++){
						if (isset($_POST["type"]) && $_POST["type"] == $res[$i]["name"]){
							echo '<option value="'.$res[$i]["name"].'"selected = "selected">'.$res[$i]["name"].'</option>';
						}
						else
							echo '<option value="'.$res[$i]["name"].'">'.$res[$i]["name"].'</option>';
					}
					echo '</select></div>';
					
					// dropdownlist for sorting by affiliation
					$query= 'SELECT DISTINCT name FROM affiliations ORDER BY name;';
					$res= $GLOBALS["db"]->do_query($query);
					$counted = count($res, 0);
					echo "<div id='sortbox'>Filter by affiliation/line: <br>" . '<form id="myform" method="post">';
					echo "<select name= 'aff' onchange='change()'>";
					echo "<option value='show'>Show everything</option>";
					for ($i = 0; $i < $counted; $i++){
						if (isset($_POST["aff"]) && $_POST["aff"] == $res[$i]["name"]){
							echo '<option value="'.$res[$i]["name"].'"selected = "selected">'.$res[$i]["name"].'</option>';
						}
						else
							echo '<option value="'.$res[$i]["name"].'">'.$res[$i]["name"].'</option>';
					}
					echo '</select></div>';
					
					// dropdownlist for sorting by ects
					$query= 'SELECT DISTINCT ects FROM courses ORDER BY ects;';
					$res= $GLOBALS["db"]->do_query($query);
					$counted = count($res, 0);
					echo "<div id='sortbox'>Filter by ects: <br>" . '<form id="myform" method="post">';
					echo "<select name= 'ects' onchange='change()'>";
					echo "<option value='show'>Show everything</option>";

					for ($i = 0; $i < $counted; $i++){
						if (isset($_POST["ects"]) && $_POST["ects"] == $res[$i]["ects"]){
							echo '<option value="'.$res[$i]["ects"].'"selected = "selected">'.$res[$i]["ects"].'</option>';
						}
						else
							echo '<option value="'.$res[$i]["ects"].'">'.$res[$i]["ects"].'</option>';
					}
					echo '</select></div>';
					

					// sorting options. When sorted by line/ects/type or whatever, the query will be changed.
					// so, when line is set, sort by line, etc
					// if show all, $_POST["ects"] == "show", else $_POST["ects"] <> "show"
					
					if (isset($_POST["ects"]) && isset($_POST["type"]) && isset($_POST["aff"])){
						if ($_POST["ects"] == "show" && $_POST["type"] == "show" && $_POST["aff"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id) ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["type"] == "show" && $_POST["aff"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND C.ects =='".$_POST['ects']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["ects"] == "show" && $_POST["aff"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND CT.name =='".$_POST['type']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["type"] == "show" && $_POST["ects"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND A.name =='".$_POST['aff']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["type"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND C.ects =='".$_POST['ects']."' AND A.name=='".$_POST['aff']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["ects"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND CT.name =='".$_POST['type']."' AND A.name =='".$_POST['aff']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else if ($_POST["aff"] == "show"){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND C.ects =='".$_POST['ects']."' AND CT.name =='".$_POST['type']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
						else {
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND C.ects == '".$_POST["ects"]."' AND CT.name=='".$_POST['type']."' AND A.name =='".$_POST['aff']."') ORDER BY C.typeid, C.affilid, C.number;";
						}
					}
					else 
						$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id) ORDER BY C.typeid, C.affilid, C.number;";
					
					$res= $GLOBALS["db"]->do_query($query);
					$counted = count($res, 0);	
					echo '<br><br><br><br><div id="clear"></div>';
					for ($i = 0; $i < $counted; $i++){
						$colourinner = "#" . $res[$i]["colour"];
						$colourouter = "#" . $res[$i]["ccolour"];
						echo '<div id="vakcontainer" style ="background:' .$colourouter. ';"><div id="leftcontainer">'. $res[$i]["line"]. "-". $res[$i]["number"] .
							'<div id="innercontainer" style="background:' .$colourinner.';">'. $res[$i]["ects"]. '</div></div><div id="rightcontainer">'. $res[$i]["name"]. '</div></div>';
					}
				?>
			</div>
			<?php 
				include("../data/footer.php"); // contains all information that would be shown as footer.
			?>
		</div>
	</body>
</html>
