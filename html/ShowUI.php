<!DOCTYPE html>
<html>
<style>
table {
  border-collapse: collapse;
  width: 100%;
}

th, td {
  text-align: left;
  padding: 8px;
}

tr:nth-child(even){background-color: #f2f2f2}

th {
  background-color: #4CAF50;
  color: white;
}
</style>
<body>


<?php
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

 	
	$sql = "SELECT * FROM TrainDetails";
	

	$result = $conn->query($sql);

	echo '<br><br><br> <h1> TRAINS </h1>';
	echo '<table>
	<tr>
	<th>ID</th>
	<th>Name</th>
	<th>Source</th>
	<th>Destination</th>
	</tr>';
	if(mysqli_num_rows($result) > 0) {
		while($row = mysqli_fetch_array($result)){
			echo '
			<tr>
			<td>'.$row['id'].'</td>
			<td>'.$row['name'].'</td>
			<td>'.$row['source'].'</td>
			<td>'.$row['destination'].'</td>
			</tr>';
			}
		}

	echo '</table><br>';
	echo '<br><br><br> <h1> TIMINGS </h1>';

	$sql2 = "SELECT * FROM Timings";
	$result2 = $conn->query($sql2);

	echo '<table>
	<tr>
	<th>ID</th>
	<th>Arrival</th>
	<th>Departure</th>
	</tr>';
	if(mysqli_num_rows($result2) > 0) {
		while($row = mysqli_fetch_array($result2)){
			echo '
			<tr>
			<td>'.$row['id'].'</td>
			<td>'.$row['arrival'].'</td>
			<td>'.$row['departure'].'</td>
			</tr>';
			}
		}
	echo '</table><br>';
	echo '<div style = "text-align:center"><a href ="index.php">Home</a><br><br></div>';

?> 
</body>
</html>