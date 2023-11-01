-- MySQL dump 10.13  Distrib 8.0.35, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: chatdb
-- ------------------------------------------------------
-- Server version	8.0.35-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `messages`
--

DROP TABLE IF EXISTS `messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `messages` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `from_user_id` int NOT NULL,
  `to_user_id` int NOT NULL,
  `message` text,
  `date` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `messages`
--

LOCK TABLES `messages` WRITE;
/*!40000 ALTER TABLE `messages` DISABLE KEYS */;
INSERT INTO `messages` VALUES (1,4,0,'hello all','2023-10-30 14:14:38'),(2,4,2,'hello ivan','2023-10-30 14:15:02'),(3,2,0,'Hello all mmmm','2023-10-30 14:16:13'),(4,2,3,'hello petr','2023-10-30 14:16:37'),(5,2,3,'привет петр','2023-10-31 12:11:39'),(6,8,0,'hello all','2023-10-31 12:20:32'),(7,2,8,'hi misha','2023-11-01 10:10:21'),(8,16,0,'в ыфафвыэаждэвыажд фывэаждвыэждп эждпэврждж прэждаоэжд   раэодэждпв оэждэожд ап','2023-11-01 11:34:31');
/*!40000 ALTER TABLE `messages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(50) NOT NULL,
  `hash_password` varchar(60) NOT NULL,
  `email` varchar(50) NOT NULL,
  `salt` varchar(50) NOT NULL,
  `date_registration` datetime DEFAULT CURRENT_TIMESTAMP,
  `ban_user` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (0,'Всем','0','0','0','2023-10-30 14:13:23',1),(2,'ivan','19626275211600017711418389904640617325014053911804','1','HIL0hDXONo898gozIyQNY37sOaQO9hAT','2023-10-30 14:13:56',0),(3,'petr','36347898141916380224323502967327880127122089180670','2','jqSBAJ1ZdOp5YJD4V1Vmq9ADKPp3fjzN','2023-10-30 14:14:07',0),(4,'serg','119281044037549224222914487122246667115887341635','3','kbNNlFB2oHos1AJngDWL8CI2PE7csT76','2023-10-30 14:14:22',0),(7,'Миша','203101323918219146241921129166117424420777456785','dsk;fldkf;','T9gmu4QVZydtJ19iRVw4oqrYbhQ6ypWw','2023-10-31 12:12:36',0),(8,'misha','35226835794244438384315452791030045007703725527806','sdfgdfgfg','WQOOS2Jyvoov94nnPX2wNc7b87Zve2VA','2023-10-31 12:17:29',0),(13,'укуцк цуйк','27398069421027395026205617573131211367924122940944','1','v3LyCf6EZRPm2W4DtWMTXza5KNC6Cv8K','2023-11-01 11:11:42',0),(16,'влджфдывлпэываждплаэывждплаывжплывалдпыэждавлп','4007724316938443245275679550731044803402620261881','1','qbhdl8ww5vCuR2UhgZ9rt7IJzeTUIl4f','2023-11-01 11:34:14',0);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-01 12:02:20
