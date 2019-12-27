<?php
include "koneksi.php";

	$sql = "SELECT jamSholat FROM `jadwal_sholat` WHERE MONTH(tanggal) = " . date("m") . " AND YEAR(tanggal) = " . date("Y") . " AND DAY(tanggal) = " . date("d") . " AND namaSholat = 'Shubuh'";


	$hasil = mysqli_query($koneksi, $sql);

$result=array(); 
$row=mysqli_fetch_array($hasil);
array_push($result,array(
"value"=>$row['jamSholat']
));

//show format json
echo $result[0]['value'];
mysqli_close($koneksi);
?>