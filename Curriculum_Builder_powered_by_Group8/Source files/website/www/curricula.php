<?php
	include("../config.php"); //contains some useful global definitions
	require(DATA_ROOT."core.php");//Include everywhere for session related stuff.
	session_start();

	if(!isset($_SESSION['logged_in']) || $_SESSION['logged_in'] == false){
		 header('Location: ./index.php?error_message=Please log in to access this page.');
		 exit();
	} 
	
	function splits ($i, $j, $ret){
		$query= 'SELECT S.left, S.right FROM lines L, columns C, years Y, curriculum CU, splits S WHERE CU.id == Y.cid AND Y.ind =="'.$i.'" AND Y.id == C.yid AND C.ind =="'.$j.'" AND C.lid == L.id AND CU.name=="'.$ret.'" AND L.type == 2 AND L.fid == S.id;';
		$rest= $GLOBALS["db"]->do_query($query);
		$cou= count($rest, 0);
		// lefter split
		for ($k = 0; $k < $cou; $k++){
			$query= 'SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM lines L, courses C, affiliations A, course_types CT WHERE C.affilid == A.id AND C.typeid == CT.id AND L.id == "'.$rest[$k]["left"].'" AND L.fid == C.id ';
			$resultt=$GLOBALS["db"]->do_query($query);
			echo '<div id="split" style="float: left"> split left';
			$countt = count($resultt, 0);	
			for ($l = 0; $l < $countt; $l++){
				$colourinner = "#" . $resultt[$l]["colour"];
				$colourouter = "#" . $resultt[$l]["ccolour"];
			echo '<div id="center"><div id="vakcontainer" style ="background:' .$colourouter. '; "><div id="leftcontainer">'. $resultt[$l]["line"]. "-". $resultt[$l]["number"] .'<div id="innercontainer" style="background:' .$colourinner.';">'. $resultt[$l]["ects"]. '</div></div><div id="rightcontainer">'. $resultt[$l]["name"]. '</div></div></div><div id="clear"></div>';
			}
			echo '</div>';
		}
		
		// righter split
		for ($k = 0; $k < $cou; $k++){
			$query= 'SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM lines L, courses C, affiliations A, course_types CT WHERE C.affilid == A.id AND C.typeid == CT.id AND L.id == "'.$rest[$k]["right"].'" AND L.fid == C.id ';
			$resultt=$GLOBALS["db"]->do_query($query);
			echo '<div id="split" style="float: right"> split right';
			$countt = count($resultt, 0);	
			for ($l = 0; $l < $countt; $l++){
				$colourinner = "#" . $resultt[$l]["colour"];
				$colourouter = "#" . $resultt[$l]["ccolour"];
			echo '<div id="center"><div id="vakcontainer" style ="background:' .$colourouter. '; "><div id="leftcontainer">'. $resultt[$l]["line"]. "-". $resultt[$l]["number"] .'<div id="innercontainer" style="background:' .$colourinner.';">'. $resultt[$l]["ects"]. '</div></div><div id="rightcontainer">'. $resultt[$l]["name"]. '</div></div></div><div id="clear"></div>';
			}
			echo '</div>';
		}
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
			<!-- refresh by given value in form -->
			<script>
				function change(){
					document.getElementById("myform").submit();
				}
			</script>
			<?php
				// selects which curriculum must be shown
				$query= 'SELECT name FROM curriculum ORDER BY name;';
				$res= $GLOBALS["db"]->do_query($query);
				$ret= $res[$_GET["c"]]["name"];
				
				// show curriculum which is selected
				$query= 'SELECT C.name, C.semesters, Y.name AS yname FROM curriculum C, years Y WHERE C.id == Y.cid AND C.name =="'.$ret.'"';
				$res= $GLOBALS["db"]->do_query($query);
				$counted = count($res, 0);
				
				// open curriculum div, place curriculum title, place year title,
				echo '<div id="curriculum"><div id="currtitle">'.$res[0]["name"].'</div>';
				for ($i = 1; $i <= $counted; $i++){
					echo '<div id="clear"></div><div id="yeartitle">'.$res[$i-1]["yname"].'</div><div id="curryear">';
					$sem = $res[0]["semesters"];
					$sem = ('100'/$sem)-'1';
					
					// place semester title, and place courses in semester
					for ($j = 1; $j <= $res[$i-1]["semesters"]; $j++){
						echo '<div id="semester" style="width:'.$sem.'%;"> semester '.$j.'<div id="clear"></div>';
						$query= 'SELECT L.fid FROM lines L, columns C, years Y, curriculum CU WHERE CU.id == Y.cid AND Y.ind =="'.$i.'" AND Y.id == C.yid AND C.ind =="'.$j.'" AND C.lid == L.id AND CU.name=="'.$ret.'" AND L.type == 1 ORDER BY L.id;';
						$result = $GLOBALS["db"]->do_query($query);
						$tel = count($result, 0);
						for ($k = 0; $k < $tel; $k++){
							$query= "SELECT C.name, C.line, C.number, C.ects, A.colour, CT.colour AS ccolour FROM courses C, affiliations A, course_types CT WHERE (C.affilid == A.id AND C.typeid == CT.id AND C.id='".$result[$k]['fid']."') ORDER BY C.typeid, C.affilid, C.number;";
							$resultt= $GLOBALS["db"]->do_query($query);
							$countt = count($resultt, 0);	
							for ($l = 0; $l < $countt; $l++){
								$colourinner = "#" . $resultt[$l]["colour"];
								$colourouter = "#" . $resultt[$l]["ccolour"];
							echo '<div id="center"><div id="vakcontainer" style ="background:' .$colourouter. '; "><div id="leftcontainer">'. $resultt[$l]["line"]. "-". $resultt[$l]["number"] .'<div id="innercontainer" style="background:' .$colourinner.';">'. $resultt[$l]["ects"]. '</div></div><div id="rightcontainer">'. $resultt[$l]["name"]. '</div></div></div><div id="clear"></div>';
							}
							
						}
						
						// splits
						splits ($i, $j, $ret); //function defined in top of this file

						echo '</div>';
					}
					echo '</div><div id="clear"></div>';
				}
				echo '</div></div>';
				include("../data/footer.php"); // contains all information that would be shown as footer. 
			?>
		</div>
	</body>
</html>

