<?php

$connection = mysqli_connect("localhost","id6750969_kaminfay","Fay89058","id6750969_thecarpentrytutor");

if(mysqli_connect_errno()){
    echo "Something went very very very wrong..... ";
}else{

    $blockName = '"' . $_GET['blockName'] . '"';
    $blockLength = $_GET['blockLength'];
    $blockWidth = $_GET['blockWidth'];
    $blockHeight = $_GET['blockHeight'];


    echo $blockName;
    echo "---";
    echo $blockLength;
    echo "---";
    echo $blockWidth;
    echo "---";
    echo $blockHeight;
    echo "---";

    $query = "SELECT blockID FROM blocks WHERE blockName = $blockName;"; // This will select all names and ID's from the blocks table

    echo $query;
    
    $blocks = mysqli_query($connection, $query);
    //$blocksArray = array(); // initializing an array
    
        $row = mysqli_fetch_array($blocks);
        

        $blockID = (int) $row[0];
        
        if($blockID){
            echo $blockID;
            echo "<br>";
            echo "That block already exists";
        }else{
            echo "<br> $blockID";
            echo "There is no block by that name time to insert it:";

            $insertBlockQuery = "INSERT INTO blocks (blockName) VALUES ($blockName)";
            mysqli_query($connection, $insertBlockQuery);    


            $query = "SELECT blockID FROM blocks WHERE blockName = $blockName;"; // This will select all names and ID's from the blocks table
            echo $query;
            $blocks = mysqli_query($connection, $query);
            $row = mysqli_fetch_array($blocks);
            $blockID = $row[0];

            $insertDataQuery = "INSERT INTO blockDimensions (blockID, length, width, height) VALUES
            ($blockID, $blockLength, $blockWidth, $blockHeight)";
            mysqli_query($connection, $insertDataQuery);

            }
    }



mysqli_close($connection);

?>
