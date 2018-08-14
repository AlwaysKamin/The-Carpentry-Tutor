<?php

    $connection = mysqli_connect("localhost","id6750969_kaminfay","Fay89058","id6750969_thecarpentrytutor");

    if(mysqli_connect_errno()){
        echo "Something went very very very wrong..... ";
    }else{

        $blockID = $_GET['blockID'];
        //echo $blockID;
        $query = "SELECT length, width, height FROM blockDimensions WHERE blockID ='$blockID'"; // This will select all names and ID's from the blocks table

if($result = mysqli_query($connection, $query)){
    $resultArray = array(); // Initialize
        $tempArray = array(); // Initialize

        $dimensions = mysqli_query($connection, $query);
        $dimensionsArray = array(); // initializing an array

        while($row = $result->fetch_object()){
            $tempArray = $row;
            array_push($resultArray, $tempArray);
        }

        echo json_encode($resultArray);
    }
}
        

    mysqli_close($connection);
?>