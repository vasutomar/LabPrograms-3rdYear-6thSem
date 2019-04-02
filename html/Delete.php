<!DOCTYPE html>
<html>
<body>
<?php

	// Values sent by the user
	$trainID = $_POST["id"]; 	

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

 	$sql = "Delete from TrainDetails where id = $trainID";

	if ($conn->query($sql) === TRUE) {
    	echo "Record deleted successfully";
	} else {
    	echo "Error: " . $sql . "<br>" . $conn->error;
	}

	echo '<div style = "text-align:center"><a href ="index.php">Home</a><br><br></div>';

	$conn->close();
?> 
</body>
</html>