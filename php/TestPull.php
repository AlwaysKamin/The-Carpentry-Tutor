<?php

$con=mysqli_connect("localhost","id6750969_kaminfay","Fay89058","id6750969_thecarpentrytutor");
 
// Check connection
if (mysqli_connect_errno())
{
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
 
// Select all of our stocks from table 'stock_tracker'
$blockIDName = "SELECT * FROM blocks";
$blockData = "SELECT * FROM blockDimensions";
 
// Confirm there are results
if ($result = mysqli_query($con, $blockIDName))
{
 // We have results, create an array to hold the results
        // and an array to hold the data
    $resultArray = array();
    $tempArray = array();
 
    // Loop through each result
    while($row = $result->fetch_object())
    {
        // Add each result into the results array
        $tempArray = $row;
        array_push($resultArray, $tempArray);
    }
 
    // Encode the array to JSON and output the results
    echo json_encode($resultArray);
}


mysqli_close($con);
?>