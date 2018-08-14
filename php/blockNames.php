<?php

    $connection = mysqli_connect("localhost","id6750969_kaminfay","Fay89058","id6750969_thecarpentrytutor");

    if(mysqli_connect_errno()){
        echo "Something went very very very wrong..... ";
    }else{
        $query = "SELECT * FROM blocks"; // This will select all names and ID's from the blocks table

        $nameAndID = mysqli_query($connection, $query);
        $nameAndIDArray = array(); // initializing an array

        while($row = $nameAndID->fetch_object()){
            array_push($nameAndIDArray, $row);
        }

            echo json_encode($nameAndIDArray);
        }

    mysqli_close($connection);
?>