<?php
	$rows = $_POST['rows'] ?? 10;
	$cols = $_POST['cols'] ?? 10;
	$seed = $_POST['seed'] ?? 0;

	$startX = $_POST['startX'] ?? 0;
	$startY = $_POST['startY'] ?? 0;

	$wOne = $_POST['wOne'] ?? 1;
	$wTwo = $_POST['wTwo'] ?? 1;
	$wThree = $_POST['wThree'] ?? 1;
	$wFour = $_POST['wFour'] ?? 1;

	$escRows = escapeshellarg($rows);
	$escCols = escapeshellarg($cols);
	$escSeed = escapeshellarg($seed);

	$escStartX = escapeshellarg($startX);
	$escStartY = escapeshellarg($startY);

	$escWOne = escapeshellarg($wOne);
	$escWTwo = escapeshellarg($wTwo);
	$escWThree = escapeshellarg($wThree);
	$escWFour = escapeshellarg($wFour);


	// seed, xLen, yLen, startX, startY, direction weights 1-4
	exec("./MazeGen.out backtrack $escSeed $escCols $escRows", $out, $return);
	//exec("./MazeGen.out backtrack $escSeed $escCols $escRows $escStartX $escStartY $escWOne $escWTwo $escWThree $escWFour", $out, $return);

	if ($return) {
		echo "Generation failed :'(<br>";
		foreach ($out as $val) {
			echo "$val<br>";
		}
	}
	else {
		// Pass maze data to image generation page and display returned image
		echo "<img src='mazeImage.php?rows=$rows&cols=$cols&maze=$out[0]' alt='Generated Maze' />";
	}

	// Print entire output text
	/*foreach ($out as $val) {
		echo "$val\r\n";
	}*/
?>

<br>
<hr>

<form method="post" action="backtrack.php">
	<p>Rows (5-25): <input type="number" name="rows"
					min="5" max="25"
					value="<?php echo $_POST['rows'] ?? 10; ?>" /></p>
	<p>Cols (5-25): <input type="number" name="cols"
					min="5" max="25"
					value="<?php echo $_POST['cols'] ?? 10; ?>" /></p>
	<p>Seed (0 for random): <input type="number" name="seed"
					min="0"
					value="<?php echo $_POST['seed'] ?? 0; ?>" /></p>
	<p><input type="submit" value="Generate"/></p>
</form>
