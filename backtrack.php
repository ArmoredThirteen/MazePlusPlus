<?php
	$rows = $_POST['rows'] ?? 10;
	$cols = $_POST['cols'] ?? 10;
	$seed = $_POST['seed'] ?? 0;

	$escapeRows = escapeshellarg($rows);
	$escapeCols = escapeshellarg($cols);
	$escapeSeed = escapeshellarg($seed);

	// seed, xLen, yLen
	exec("./a.out backtrack $escapeSeed $escapeCols $escapeRows", $out, $return);

	if ($return) {
		echo "Generation failed :'(";
	}
	else {
		// Pass maze data to image generation page and display returned image
		echo "<img src='mazeImage.php?rows=$rows&cols=$cols&maze=$out[0]' alt='Generated Maze' />";

		// Print entire output text
		/*foreach ($out as $val) {
			echo "$val\r\n";
		}*/
	}
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
