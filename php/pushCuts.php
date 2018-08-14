<?php

$connection = mysqli_connect("localhost","id6750969_kaminfay","Fay89058","id6750969_thecarpentrytutor");

if(mysqli_connect_errno()){
    echo "Something went very very very wrong..... ";
}else{

    $blockName = '"' . $_GET['blockName'] . '"';
    $blockFace = $_GET['blockFace'];
    $cutX = $_GET['cutX'];
    $cutY = $_GET['cutY'];


    

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

            $blocks = mysqli_query($connection, $query);
            $row = mysqli_fetch_array($blocks);
            $blockID = $row[0];

            $insertDataQuery = "INSERT INTO blockCuts (blockID, faceType, cutX, cutY) VALUES
            ($blockID, $blockFace, $cutX, $cutY)";
            mysqli_query($connection, $insertDataQuery);

        }else{
            echo "<br> $blockID";
            echo "There is no block by that name time to insert it:";

        }
            
    }



mysqli_close($connection);

?>
