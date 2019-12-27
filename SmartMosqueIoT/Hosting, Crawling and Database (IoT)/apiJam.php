<?php
include 'koneksi.php';

$ch = curl_init();
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_URL, 'http://muslimsalat.com/malang.json?key=bd099c5825cbedb9aa934e255a81a5fc');
$result = curl_exec($ch);
curl_close($ch);

$obj = json_decode($result);
// var_dump($obj->items[0]);
$getHuruf = "";
foreach($obj->items[0] as $data => $value) {
    if($data != "date_for") {
        $getJam = $value;
        $getHuruf = $getHuruf . $getJam[0];
        // echo $getHuruf;
    }
}

$getJamShubuh = $getHuruf[0];
// echo $getJamShubuh;

$getJamDhuhur = $getHuruf[2] . $getHuruf[2];
// echo $getJamDhuhur;

$getJamAshar = (int)$getHuruf[3] + 13;
// echo $getJamAshar;

$getJamMaghrib = (int)$getHuruf[4] + 12;
// echo $getJamMaghrib;

$getJamIsya = (int)$getHuruf[5] + 12;
// echo $getJamIsya;

$getHuruf = "";
foreach($obj->items[0] as $data => $value) {
    if($data != "date_for") {
        $getJam = $value;
        $getHuruf = $getHuruf . $getJam[2];
        // echo $getHuruf;
    }
}

$getMenitShubuh = $getHuruf[0];
// echo $getMenitShubuh;

$getMenitDhuhur = "";
// echo $getMenitDhuhur;

$getMenitAshar = $getHuruf[3];
// echo $getMenitAshar;

$getMenitMaghrib = $getHuruf[4];
// echo $getMenitMaghrib;

$getMenitIsya = $getHuruf[5];
// echo $getMenitIsya;

$getHuruf = "";
foreach($obj->items[0] as $data => $value) {
    if($data != "date_for") {
        $getJam = $value;
        $getHuruf = $getHuruf . $getJam[3];
        // echo $getHuruf;
    }
}

$getMenitShubuh = $getMenitShubuh . $getHuruf[0];
// echo $getMenitShubuh;

$getMenitDhuhur = $getHuruf[2];
// echo $getMenitDhuhur;

$getMenitAshar = $getMenitAshar . $getHuruf[3];
// echo $getMenitAshar;

$getMenitMaghrib = $getMenitMaghrib . $getHuruf[4];
// echo $getMenitMaghrib;

$getMenitIsya = $getMenitIsya . $getHuruf[5];
// echo $getMenitIsya;

$getHuruf = "";
foreach($obj->items[0] as $data => $value) {
    if($data != "date_for") {
        $getJam = $value;
        $getHuruf = $getHuruf . $getJam[4];
        // echo $getHuruf;
    }
}

$getMenitDhuhur = $getMenitDhuhur . $getHuruf[2];
// echo $getMenitDhuhur;

	$sql = "SELECT * FROM `jadwal_sholat` WHERE MONTH(tanggal) = " . date("m") . " AND YEAR(tanggal) = " . date("Y") . " AND DAY(tanggal) = " . date("d");


	$hasil = mysqli_query($koneksi, $sql);

$result=array(); 
$row=mysqli_fetch_array($hasil);

if ($row == null) {
    echo "Kosong";
    $sql = "INSERT INTO jadwal_sholat VALUES (sysdate(),'Shubuh'," . $getJamShubuh . "," . $getMenitShubuh . ")";
    mysqli_query($koneksi, $sql);
    $sql = "INSERT INTO jadwal_sholat VALUES (sysdate(),'Dhuhur'," . $getJamDhuhur . "," . $getMenitDhuhur . ")";
    mysqli_query($koneksi, $sql);
    $sql = "INSERT INTO jadwal_sholat VALUES (sysdate(),'Ashar'," . $getJamAshar . "," . $getMenitAshar . ")";
    mysqli_query($koneksi, $sql);
    $sql = "INSERT INTO jadwal_sholat VALUES (sysdate(),'Maghrib'," . $getJamMaghrib . "," . $getMenitMaghrib . ")";
    mysqli_query($koneksi, $sql);
    $sql = "INSERT INTO jadwal_sholat VALUES (sysdate(),'Isya'," . $getJamIsya . "," . $getMenitIsya . ")";
    mysqli_query($koneksi, $sql);
} else {
    echo "Ada isinya";
}