<html>
<body>
<?php
$dbhost = "localhost";
 $dbuser = "root";
 $dbpass = "123456";
 $db = "exams";
 $conn = new mysqli($dbhost, $dbuser, $dbpass,$db) or die("Connect failed: %s\n". $conn -> error);
 $sql = 'SELECT Name, Surname, Group_id FROM students';
 $result_mode = 0;
   $retval = mysqli_query( $conn, $sql, $result_mode );
   if(! $retval ) {
      die('Could not get data: ' . mysqli_error());
   }
    $conn -> close();
 ?>
</body>
</html>