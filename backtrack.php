<?php

// Set Default Values
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
exec("./MazeGen.out backtrack $escSeed $escCols $escRows $escStartX $escStartY $escWOne $escWTwo $escWThree $escWFour", $out, $return);

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

// Print entire output text
/*foreach ($out as $val) {
    echo "$val\r\n";
}*/
?>
<!doctype html>
<html lang="en">
<head>
    <title>Backtrack</title>
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
                <?php if(isset($image)) echo $image; ?>
                <?php if(isset($response))?>
                <!--<div class="alert alert-danger">
                    <b>An error occured:</b> <?php echo $response; ?><br/>
                    <?php print_r($debug); ?>
                </div>-->

                <form method="post" action="backtrack.php">
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
                            Seed (0 for random):
                            <input type="number" class="form-control"  name="seed" min="0"
                                    value="<?php echo $seed; ?>" />
                        </div>
                    </div>
                    <div class="form-row">
                        <div class="form-group col-md-3">
                            Starting X:
                            <input type="number" class="form-control"  name="startX" id="x" min="0"
                                   value="<?php echo $rows - 1; ?>" />
                        </div>
                        <div class="form-group col-md-3">
                            Starting Y:
                            <input type="number" class="form-control"  name="startY" id="y" min="0"
                                   value="<?php echo $cols - 1; ?>" />
                        </div>
                    </div>
                    <hr>

                    <h3 class="font-weight-bold">Movement Direction Weights</h3>
                    <div class="form-row">
                        <div class="form-group col-md-3">
                            Left (1-20):
                            <input type="number" class="form-control"  name="wOne" min="1" max="20"
                                   value="<?php echo $wOne; ?>" />
                        </div>
                        <div class="form-group col-md-3">
                            Right (1-20):
                            <input type="number" class="form-control"  name="wTwo" min="1" max="20"
                                   value="<?php echo $wTwo; ?>" />
                        </div>
                        <div class="form-group col-md-3">
                            Up (1-20):
                            <input type="number" class="form-control"  name="wThree" min="1" max="20"
                                   value="<?php echo $wThree; ?>" />
                        </div>
                        <div class="form-group col-md-3">
                            Down (1-20):
                            <input type="number" class="form-control"  name="wFour" min="1" max="20"
                                   value="<?php echo $wFour; ?>" />
                        </div>
                    </div>

                    <input class="btn btn-success" type="submit" value="Generate"/>
                </form>
            </div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script>
        rows = $('#rows');
        cols = $('#cols');
        x = $('#x');
        y = $('#y');

        rows.on('input', function() {
            x.attr({
                max: rows.val() - 1,
                value: rows.val() - 1
            });
            x.val(rows.val());
        });
        cols.on('input', function() {
            y.attr({
                max: cols.val() - 1,
                value: cols.val() - 1
            });
            y.val(cols.val());
        });
    </script>
</body>
</html>
