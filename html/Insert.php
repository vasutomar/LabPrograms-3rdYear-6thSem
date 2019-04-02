<!DOCTYPE html>
<html>
<body>
<?php

	// Values sent by the user
	$trainID = $_POST["id"]; 	
 	$trainName = $_POST["name"];
 	$trainSource = $_POST["source"];
 	$trainDest = $_POST["destination"];
 	$trainArrival = $_POST["arrival"];
 	$trainDeparture = $_POST["departure"];

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

 	$sql2 = "INSERT INTO Timings (id, arrival, departure) VALUES ('$trainID', '$trainArrival', '$trainDeparture')";

 	$sql = "INSERT INTO TrainDetails (id, name, source, destination) VALUES ('$trainID', '$trainName', '$trainSource', '$trainDest')";

	if ($conn->query($sql) === TRUE && $conn->query($sql2)===TRUE) {
    	echo "New record created successfully";
	} else {
    	echo "Error: " . $sql . "<br>" . $conn->error;
	}

	echo '<div style = "text-align:center"><a href ="index.php">Home</a><br><br></div>';

	$conn->close();
?> 
</body>
</html>