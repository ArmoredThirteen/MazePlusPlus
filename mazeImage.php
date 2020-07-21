<?php
	header("Content-type: image/png");

	// Get header info
	$rows = (int)$_GET['rows'];
	$cols = (int)$_GET['cols'];
	$maze = $_GET['maze'];

	// Common pixel numbers
	$pixels = 12; // TODO: hardcoded...
	$pixelsTwice = $pixels * 2;

	// Help prevent attacks that manually request massive things
	$rows = min (25, $rows);
	$cols = min (25, $cols);
	$maze = mb_strimwidth($maze, 0, 2000);

	// Split maze data into 2d array
	$mazeAra = array_map(function($val) {return explode('-', $val); }, explode('|', $maze));

	// Diagnostic printoff
	/*for ($row = 0; $row < $rows; $row++){
		for ($col = 0; $col < $cols; $col++){
			$leftWall = $mazeAra[$row][$col][0];
			$topWall = $mazeAra[$row][$col][1];

			echo substr($mazeAra[$row][$col], 0, 1);
			echo substr($mazeAra[$row][$col], 1, 2);
			//echo $rightWall;
			echo " ";
		}
		echo "<br>";
	}
	echo "<br>";*/

	// Create image, set to black, and register colors
	$image = imagecreate(($cols * $pixelsTwice) + $pixels, ($rows * $pixelsTwice) + $pixels);
	$black = imagecolorallocate($image, 0, 0, 0);
	$white = imagecolorallocate($image, 255, 255, 255);

	for ($row = 0; $row < $rows; $row++){
		for ($col = 0; $col < $cols; $col++){
			// Lowest pixel coordinates of cell
			$rootX = $col * $pixelsTwice;
			$rootY = $row * $pixelsTwice;

			// Mid-point pixel coordinates of cell
			$midX = $rootX + $pixels;
			$midY = $rootY + $pixels;

			// Highest pixel coordinates of cell
			$endX = $rootX + $pixelsTwice;
			$endY = $rootY + $pixelsTwice;

			// Color known empty space
			imagefilledrectangle($image, $midX, $midY, $endX - 1, $endY - 1, $white);

			$leftWall = substr($mazeAra[$row][$col], 0, 1);
			$topWall = substr($mazeAra[$row][$col], 1, 2);

			// If left or top wall don't exist, color area to be white empty space
			if ($leftWall === '0'){
				imagefilledrectangle($image, $rootX, $midY, $midX - 1, $endY - 1, $white);
			}
			if ($topWall === '0'){
				imagefilledrectangle($image, $midX, $rootY, $endX - 1, $midY - 1, $white);
			}
		}
	}

	imagepng($image);
	imagedestroy($image);
?>