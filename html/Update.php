<!DOCTYPE html>
<html>
<body>
<?php

	// Values sent by the user
	$trainID = $_POST["id"]; 	
 	$trainName = $_POST["name"];
 	$trainSource = $_POST["source"];
 	$trainDest = $_POST["destination"];

	// Connection credentials
	$host = "localhost";
	$name = "php";
	$pass = "pass";
	$data = "Trains";

	// Establishing connection to mysql
 	$conn = new mysqli($host, $name, $pass, $data);
 	if($conn->connect_error) {
 		die("Connection failed.".$conn->connect_error);
 	}

 	$sql = "UPDATE TrainDetails 
 				SET 
 					name = '$trainName',
 					source = '$trainSource',
 					destination = '$trainDest'
 				WHERE 
 					id = '$trainID'";

	if ($conn->query($sql) === TRUE) {
    	echo "Record updated successfully";
	} else {
    	echo "Error: " . $sql . "<br>" . $conn->error;
	}

	echo '<div style = "text-align:center"><a href ="index.php">Home</a><br><br></div>';
	
	$conn->close();
?> 
</body>
</html>