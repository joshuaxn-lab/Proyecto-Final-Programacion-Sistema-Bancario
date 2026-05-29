-- MySQL dump 10.13  Distrib 8.0.45, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: banco
-- ------------------------------------------------------
-- Server version	9.6.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
SET @MYSQLDUMP_TEMP_LOG_BIN = @@SESSION.SQL_LOG_BIN;
SET @@SESSION.SQL_LOG_BIN= 0;

--
-- GTID state at the beginning of the backup 
--

SET @@GLOBAL.GTID_PURGED=/*!80000 '+'*/ 'a2efd5ac-12c9-11f1-b05d-402cf4eb8db8:1-109';

--
-- Table structure for table `clientes`
--

DROP TABLE IF EXISTS `clientes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clientes` (
  `id` int NOT NULL AUTO_INCREMENT,
  `nombre` varchar(100) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clientes`
--

LOCK TABLES `clientes` WRITE;
/*!40000 ALTER TABLE `clientes` DISABLE KEYS */;
INSERT INTO `clientes` VALUES (3,'Juan Perez','juan@email.com'),(4,'Maria Lopez','maria@email.com');
/*!40000 ALTER TABLE `clientes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cuentas`
--

DROP TABLE IF EXISTS `cuentas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cuentas` (
  `id` int NOT NULL AUTO_INCREMENT,
  `numero_cuenta` varchar(10) NOT NULL,
  `nombre_titular` varchar(200) DEFAULT NULL,
  `tipo` enum('ahorro','monetaria') NOT NULL,
  `saldo` decimal(10,2) NOT NULL DEFAULT '0.00',
  `correo_electronico` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `numero_cuenta` (`numero_cuenta`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cuentas`
--

LOCK TABLES `cuentas` WRITE;
/*!40000 ALTER TABLE `cuentas` DISABLE KEYS */;
INSERT INTO `cuentas` VALUES (1,'5582667349','Joshua Jonathan Lopez Solis','ahorro',200.00,NULL),(2,'0119775621','Jose','monetaria',1000.00,NULL),(3,'1941198151','Jose mus','monetaria',1600.00,NULL),(4,'4820535486','Joshua','ahorro',100.00,NULL),(5,'5620231683','Joshua Jonathan Lopez Solis','monetaria',12300.00,NULL);
/*!40000 ALTER TABLE `cuentas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transacciones`
--

DROP TABLE IF EXISTS `transacciones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transacciones` (
  `id` int NOT NULL AUTO_INCREMENT,
  `numero_cuenta` varchar(10) NOT NULL,
  `tipo` varchar(50) DEFAULT NULL,
  `monto` decimal(10,2) NOT NULL,
  `fecha` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transacciones`
--

LOCK TABLES `transacciones` WRITE;
/*!40000 ALTER TABLE `transacciones` DISABLE KEYS */;
INSERT INTO `transacciones` VALUES (1,'0119775621','deposito',200.00,'2026-05-26 10:30:00'),(2,'1941198151','deposito',300.00,'2026-05-29 09:32:26'),(3,'0119775621','deposito',300.00,'2026-05-29 09:57:43'),(4,'0119775621','transferencia_enviada',200.00,'2026-05-29 09:58:13'),(5,'1941198151','transferencia_recibida',200.00,'2026-05-29 09:58:13'),(6,'4820535486','deposito',1000.00,'2026-05-29 10:16:45'),(7,'4820535486','transferencia_enviada',1000.00,'2026-05-29 10:17:20'),(8,'1941198151','transferencia_recibida',1000.00,'2026-05-29 10:17:20'),(9,'5620231683','deposito',4000.00,'2026-05-29 10:46:08'),(10,'5620231683','retiro',300.00,'2026-05-29 10:46:21');
/*!40000 ALTER TABLE `transacciones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transferencias`
--

DROP TABLE IF EXISTS `transferencias`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transferencias` (
  `id` int NOT NULL AUTO_INCREMENT,
  `cuenta_origen` varchar(20) NOT NULL,
  `cuenta_destino` varchar(20) NOT NULL,
  `monto` decimal(12,2) NOT NULL,
  `estado` varchar(20) NOT NULL DEFAULT 'completada',
  `fecha` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transferencias`
--

LOCK TABLES `transferencias` WRITE;
/*!40000 ALTER TABLE `transferencias` DISABLE KEYS */;
INSERT INTO `transferencias` VALUES (2,'0119775621','1941198151',200.00,'completada','2026-05-29 09:58:13'),(3,'4820535486','1941198151',1000.00,'completada','2026-05-29 10:17:20'),(4,'5620231683','0119775621',400.00,'ok','2026-05-29 10:47:03');
/*!40000 ALTER TABLE `transferencias` ENABLE KEYS */;
UNLOCK TABLES;
SET @@SESSION.SQL_LOG_BIN = @MYSQLDUMP_TEMP_LOG_BIN;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2026-05-29 10:49:58
