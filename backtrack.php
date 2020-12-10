<?php

// Set Default Values
$rows = $_POST['rows'] ?? 10;
$cols = $_POST['cols'] ?? 10;
$seed = $_POST['seed'] ?? 0;

$startRow = $_POST['startRow'] ?? 0;
$startCol = $_POST['startCol'] ?? 0;

$wOne = $_POST['wOne'] ?? 1;
$wTwo = $_POST['wTwo'] ?? 1;
$wThree = $_POST['wThree'] ?? 1;
$wFour = $_POST['wFour'] ?? 1;

$escRows = escapeshellarg($rows);
$escCols = escapeshellarg($cols);
$escSeed = escapeshellarg($seed);

$escStartRow = escapeshellarg($startRow);
$escStartCol = escapeshellarg($startCol);

$escWOne = escapeshellarg($wOne);
$escWTwo = escapeshellarg($wTwo);
$escWThree = escapeshellarg($wThree);
$escWFour = escapeshellarg($wFour);


// seed, xLen, yLen, startRow, startCol, direction weights 1-4
exec("./MazeGen.out backtrack $escSeed $escCols $escRows $escStartCol $escStartRow $escWOne $escWTwo $escWThree $escWFour", $out, $return);

if ($return) {
    $response = "Generation failed. :(";
    foreach ($out as $val) {
        $debug =+ $val;
    }
}
else {
    // Pass maze data to image generation page and display returned image
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
                <div class="text-center">
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
                                    value="<?php echo $rows; ?>" />
                            </div>
                            <div class="form-group col-md-3">
                                Cols (5-25):
                                <input type="number" class="form-control" name="cols" id="cols" min="5" max="25"
                                    value="<?php echo $cols; ?>" />
                            </div>
                            <div class="form-group col-md-3">
                                Starting Row:
                                <input type="number" class="form-control"  name="startRow" id="startRow" min="0"
                                    max="" value="<?php echo $startRow; ?>" />
                            </div>
                            <div class="form-group col-md-3">
                                Starting Col:
                                <input type="number" class="form-control"  name="startCol" id="startCol" min="0"
                                    max="" value="<?php echo $startCol; ?>" />
                            </div>
                        </div>

                        <div class="form-row">
                        <div class="form-group col-md-6 mb-0">
                                Seed:
                                <input type="number" class="form-control"  name="seed" min="0"
                                        value="<?php echo $seed; ?>" />
                            </div>
                        </div>
                    </div>
                    <div class="card card-body shadow-lg mt-4">
                        <h3 class="font-weight-bold">Movement Direction Weights</h3>
                        <div class="form-row">
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Left (1-20):
                                <input type="number" class="form-control"  name="wOne" min="1" max="20"
                                    value="<?php echo $wOne; ?>" />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Right (1-20):
                                <input type="number" class="form-control"  name="wTwo" min="1" max="20"
                                    value="<?php echo $wTwo; ?>" />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Up (1-20):
                                <input type="number" class="form-control"  name="wThree" min="1" max="20"
                                    value="<?php echo $wThree; ?>" />
                            </div>
                            <div class="form-group col-md-3 mt-2 mb-0">
                                Down (1-20):
                                <input type="number" class="form-control"  name="wFour" min="1" max="20"
                                    value="<?php echo $wFour; ?>" />
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
        startRow.attr('max', 0);
        startCol.attr('max', 0);

        // If the values of Rows or Columns is changed,
        // update the max + val for the starting x + y.
        rows.on('input', function() {
            startRow.attr({
                max: rows.val() - 1,
                value: rows.val() - 1
            });
            startRow.val(rows.val() - 1);
        });
        cols.on('input', function() {
           startCol.attr({
                max: cols.val() - 1,
                value: cols.val() - 1
            });
            startCol.val(cols.val() - 1);
        });
    </script>
</body>
</html>
