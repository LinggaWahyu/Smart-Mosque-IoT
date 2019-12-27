-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Dec 27, 2019 at 12:04 AM
-- Server version: 10.3.16-MariaDB
-- PHP Version: 7.3.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `id11827270_jadwalsholatsmartmosque`
--

-- --------------------------------------------------------

--
-- Table structure for table `jadwal_sholat`
--

CREATE TABLE `jadwal_sholat` (
  `tanggal` date NOT NULL,
  `namaSholat` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `jamSholat` int(2) NOT NULL,
  `menitSholat` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `jadwal_sholat`
--

INSERT INTO `jadwal_sholat` (`tanggal`, `namaSholat`, `jamSholat`, `menitSholat`) VALUES
('2019-12-08', 'Shubuh', 3, 38),
('2019-12-08', 'Dhuhur', 11, 21),
('2019-12-08', 'Ashar', 14, 40),
('2019-12-08', 'Maghrib', 17, 44),
('2019-12-08', 'Isya', 18, 54),
('2019-12-09', 'Shubuh', 3, 38),
('2019-12-09', 'Dhuhur', 11, 21),
('2019-12-09', 'Ashar', 14, 40),
('2019-12-09', 'Maghrib', 17, 45),
('2019-12-09', 'Isya', 18, 55),
('2019-12-10', 'Shubuh', 3, 39),
('2019-12-10', 'Dhuhur', 11, 21),
('2019-12-10', 'Ashar', 14, 40),
('2019-12-10', 'Maghrib', 17, 45),
('2019-12-10', 'Isya', 18, 55),
('2019-12-11', 'Shubuh', 3, 39),
('2019-12-11', 'Dhuhur', 11, 22),
('2019-12-11', 'Ashar', 14, 40),
('2019-12-11', 'Maghrib', 17, 46),
('2019-12-11', 'Isya', 18, 56);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
