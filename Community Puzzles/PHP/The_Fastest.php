<?php

/*~~~~~~~~~~~~~~~~~~*
*                  *
*  $DollarAkshay$  *
*                  *
*~~~~~~~~~~~~~~~~~~*/

//https://www.codingame.com/ide/puzzle/the-fastest

$n = fgets(STDIN);
$timings = array();

for ($i = 0; $i < $n; $i++){
    $timings[] = fgets(STDIN);
}

echo min($timings);

?>