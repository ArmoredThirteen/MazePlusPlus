<?php

// Set Default Values
$rows = intval($_POST['rows'] ?? 10);
$cols = intval($_POST['cols'] ?? 10);
$seed = intval($_POST['seed'] ?? 0);

$startRow = intval($_POST['startRow'] ?? 1);
$startCol = intval($_POST['startCol'] ?? 1);

$wOne = intval($_POST['wOne'] ?? 1);
$wTwo = intval($_POST['wTwo'] ?? 1);
$wThree = intval($_POST['wThree'] ?? 1);
$wFour = intval($_POST['wFour'] ?? 1);


// seed, xLen, yLen, startRow, startCol, direction weights 1-4
exec(sprintf("./MazeGen.out backtrack $seed $cols $rows %d %d $wOne $wTwo $wThree $wFour", $startCol - 1, $startRow - 1), $out, $return);

if ($return) {
    $response = "Generation failed. :(";
    foreach ($out as $val) {
        $debug =+ $val;
    }
}
else {
    // Pass maze data to image generation page and display returned image
    $height = ($rows + 0.5) * 24;
    $image = "<img src='mazeImage.php?rows=$rows&cols=$cols&maze=$out[0]' alt='Generated Maze' />";
}
?>


<!doctype html>
<html lang="en">

<head>
    <title>Maze Plus Plus</title>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
</head>

<body>
    <div class="container mt-4">
        <div class="row justify-content-center">
            <div class="col-sm-12 col-md-9">
                <div class="text-center" style='height:<?php echo $height ?>px; display:block;'>
                    <?php if(isset($image)) echo $image; ?>
                </div>
                <?php if(isset($response)) { ?>
                <div class="alert alert-danger">
                    <b>An error occured:</b> <?php echo $response; ?><br/>
                    <?php print_r($debug); ?>
                </div>
                <?php } ?>

                <form method="post" action="backtrack.php">
                    <div class="card card-body shadow-lg mt-4">
                        <h3 class="font-weight-bold">Basic Settings</h3>
                        <div class="form-row">
                            <div class="form-group col-md-3">
                                Rows (5-25):
                                <input type="number" class="form-control" name="rows" id="rows" min="5" max="25"
                                    value="<?php echo $rows; ?>" required />
                            </div>
                            <div class="form-group col-md-3">
                                Cols (5-25):
                                <input type="number" class="form-control" name="cols" id="cols" min="5" max="25"
                                    value="<?php echo $cols; ?>" required />
                            </div>
                            <div class="form-group col-md-3">
                                Starting Row:
                                <input type="number" class="form-control"  name="startRow" id="startRow" min="1"
                                    max="" value="<?php echo $startRow; ?>" required />
                            </div>
                            <div class="form-group col-md-3">
                                Starting Col:
                                <input type="number" class="form-control"  name="startCol" id="startCol" min="1"
                                    max="" value="<?php echo $startCol; ?>" required />
                            </div>
                        </div>

                        <div class="form-row">
                        <div class="form-group col-md-6 mb-0">
                                Seed:
                                <input type="number" class="form-control"  name="seed" min="0"
                                        value="<?php echo $seed; ?>" required />
                            </div>
                        </div>
                    </div>
                    <div class="card card-body shadow-lg mt-4">
                        <h3 class="font-weight-bold">Movement Direction Weights</h3>
                        <div class="form-row">
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Left (1-20):
                                <input type="number" class="form-control"  name="wOne" min="1" max="20"
                                    value="<?php echo $wOne; ?>" required />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Right (1-20):
                                <input type="number" class="form-control"  name="wTwo" min="1" max="20"
                                    value="<?php echo $wTwo; ?>" required />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Up (1-20):
                                <input type="number" class="form-control"  name="wThree" min="1" max="20"
                                    value="<?php echo $wThree; ?>" required />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Down (1-20):
                                <input type="number" class="form-control"  name="wFour" min="1" max="20"
                                    value="<?php echo $wFour; ?>" required />
                            </div>
                        </div>
                    </div>
                    <p class="text-center mt-4">
                        <input class="btn btn-lg btn-success" type="submit" value="Generate Maze"/>

                    </p>
                </form>
            </div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script>
        rows = $('#rows');
        cols = $('#cols');
        startRow = $('#startRow');
        startCol = $('#startCol');

        // Let's set the max starting points right away.
        startRow.attr('max', rows.val());
        startCol.attr('max', cols.val());

        // If the values of Rows or Columns is changed,
        // update the max + val for the starting x + y.
        rows.on('input', function() {
            startRowVal = Math.min(startRow.val(), rows.val());
			startRow.attr({
                max: rows.val(),
                value: startRowVal
            });
            startRow.val(startRowVal);
        });
        cols.on('input', function() {
			startColVal = Math.min(startCol.val(), cols.val());
			startCol.attr({
                max: cols.val(),
                value: startColVal
            });
            startCol.val(startColVal);
        });
    </script>
</body>
</html>
