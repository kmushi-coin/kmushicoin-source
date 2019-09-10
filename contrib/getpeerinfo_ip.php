<?php
$explorer = file_get_contents('http://explorer.tierravivaplanet.com/api/getpeerinfo');

$info = file_get_contents('http://explorer.tierravivaplanet.com/api/getinfo');

$connections = json_decode($info,TRUE)["connections"];

$array = json_decode($explorer,TRUE);

for ($x=0; $x<$connections; $x++) {

echo $array[$x]["addr"]."<br>";
}

?>
<br>
<br>
<br>
<br>
Configuracion de archivo .conf
<br>


<?php

for ($y=0; $y<$connections; $y++) {

echo "addnode=".$array[$y]["addr"]."<br>";
}

?>