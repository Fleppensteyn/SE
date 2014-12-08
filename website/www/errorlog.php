<?php
header("Content-type: text/plain");
$err = file_get_contents("/nginx/logs/error.log");
if (isset($_REQUEST["full"])){
  echo $err;
} else{
  $erex = explode("\n", $err);
  $erc = count($erex);
  echo "--- Last 20 lines of the error log: ";
  for ($i=$erc-20; $i < $erc; $i++) {
    if ($i < 0) continue;
    echo preg_replace("/^(\d{4}.\d{2}.\d{2} \d{2}:\d{2}:\d{2})/", "---\n\\1", $erex[$i])."\n";
  }
}
?>
