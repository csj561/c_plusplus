 MySQL dump 10.13  Distrib 5.1.73, for debian-linux-gnu (i486)
--
-- Host: localhost    Database: money
-- ------------------------------------------------------
-- Server version	5.1.73-1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `YuEBao`
--

DROP TABLE IF EXISTS `YuEBao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `YuEBao` (
  `date` date NOT NULL,
  `name` varchar(10) NOT NULL,
  `num` decimal(14,2) NOT NULL,
  `comment` text,
  `id` int(8) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=153 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `YuEBao`
--

LOCK TABLES `YuEBao` WRITE;
/*!40000 ALTER TABLE `YuEBao` DISABLE KEYS */;
INSERT INTO `YuEBao` VALUES ('2014-01-05','ÐìÑîµÏ','757.00','´æÈëÓà¶î±¦',36),('2014-02-08','ÐìÑîµÏ','500.00','´æÈëÓà¶î±¦',39),('2014-01-01','ÓàÈó»¨','5000.00','´æÈëÓà¶î±¦\r',3),('2014-04-06','Ðì¼Ñ','1500.00','´æÈëÓà¶î±¦\r',4),('2014-04-06','Ðì½¨','10700.00','´æÈëÓà¶î±¦\r',5),('2014-04-07','Ðì¼Ñ','-32.00','ÍøÉÏÂòÊé\r',6),('2014-04-27','Ðì¼Ñ','-39.00','ÂòÐ¬×Ó\r',7),('2014-04-28','Ðì½¨','4900.00','´æÈëÓà¶î±¦\r',8),('2014-04-29','ÑîÊç»¨','1000.00','´æÈëÓà¶î±¦\r',9),('2014-05-07','Ðì¼Ñ','1500.00','´æÈëÓà¶î±¦\r',10),('2014-05-07','Ðì¼Ñ','-25.00','¹þÂ×¾Å·Ö¿ã\r',11),('2014-05-07','Ðì¼Ñ','-15.80','·ÀÉ¹ÒÂ°ëÐä´òµ×ÉÀ\r',12),('2014-05-10','Ðì¼Ñ','-50.00','Ðì¼ÑÎªËýÂèÂèÂòÐ¬×Ó',13),('2014-05-09','ÐìÑîµÏ','2700.00','´æÈëÓà¶î±¦',47),('2013-08-25','ÐìÑîµÏ','200.00','´æÈëÓà¶î±¦',19),('2013-08-26','ÐìÑîµÏ','300.00','´æÈëÓà¶î±¦',20),('2013-08-31','ÐìÑîµÏ','2000.00','´æÈëÓà¶î±¦',21),('2013-09-01','ÐìÑîµÏ','500.00','´æÈëÓà¶î±¦',22),('2013-09-09','ÐìÑîµÏ','500.00','´æÈëÓà¶î±¦',23),('2013-09-11','ÐìÑîµÏ','500.00','´æÈëÓà¶î±¦',29),('2013-09-30','ÐìÑîµÏ','2000.00','´æÈëÓà¶î±¦',25),('2013-10-07','ÐìÑîµÏ','4000.00','´æÈëÓà¶î±¦',26),('2013-10-08','ÐìÑîµÏ','4000.00','´æÈëÓà¶î±¦',27),('2013-10-25','ÐìÑîµÏ','200.00','´æÈëÓà¶î±¦',28),('2013-11-11','ÐìÓÀ¿µ','2000.00','´æÈëÓà¶î±¦',30),('2013-11-12','ÐìÓÀ¿µ','1000.00','´æÈëÓà¶î±¦',31),('2013-11-30','ÐìÑîµÏ','1500.00','´æÈëÓà¶î±¦',32),('2013-11-16','Ðì½¨','5000.00','´æÈëÓà¶î±¦',33),('2013-12-11','ÐìÑîµÏ','800.00','´æÈëÓà¶î±¦',34),('2014-01-06','ÐìÓÀ¿µ','20000.00','´æÈëÓà¶î±¦',35),('2014-01-12','ÐìÑîµÏ','100.00','´æÈëÓà¶î±¦',37),('2014-01-14','Ðì½¨','7000.00','´æÈëÓà¶î±¦',38),('2014-03-02','ÐìÑîµÏ','3800.00','´æÈëÓà¶î±¦',40),('2014-03-05','ÐìÑîµÏ','3700.00','´æÈëÓà¶î±¦',41),('2014-03-15','ÐìÑîµÏ','15000.00','´æÈëÓà¶î±¦',48),('2014-03-23','ÐìÑîµÏ','4500.00','´æÈëÓà¶î±¦',43),('2014-04-08','ÐìÑîµÏ','800.00','´æÈëÓà¶î±¦',44),('2014-04-13','ÐìÑîµÏ','500.00','´æÈëÓà¶î±¦',45),('2014-04-27','ÐìÑîµÏ','100.00','´æÈëÓà¶î±¦',46),('2014-04-06','ÐìÑîµÏ','-700.00','ÉÙ´æÈë²î¶î',49),('2014-01-01','ÐìÑîµÏ','-5000.00','¸¶»ïÊ³·Ñ',50),('2014-02-08','ÐìÑîµÏ','-44.00','ÃÀÍÅµçÓ°',51),('2014-02-10','ÐìÑîµÏ','-47.00','»ð³µÆ±',52),('2014-02-13','ÐìÑîµÏ','-100.00','×ªµ½Óà¶î',53),('2014-02-19','ÐìÑîµÏ','-46.00','Ðì¼ÑÂòÐ¬×Ó',54),('2014-02-26','ÐìÑîµÏ','-20.00','ÁªÍ¨½É·Ñ',55),('2014-03-02','ÐìÑîµÏ','-50.00','µç»°·Ñ',56),('2014-03-02','ÐìÑîµÏ','-49.00','ÁªÍ¨»°·Ñ',57),('2014-05-02','ÐìÑîµÏ','-72.00','×ªÕËµ½½¨ÐÐ¿¨',58),('2014-03-17','ÐìÑîµÏ','-100.00','·¹¿¨',59),('2014-03-27','ÐìÑîµÏ','-79.00','Ð¬×Ó',60),('2014-03-29','ÐìÑîµÏ','-40.00','ÃÀÍÅµçÓ°Æ±',61),('2014-03-29','ÐìÑîµÏ','-20.00','ÁªÍ¨»°·Ñ',62),('2014-03-31','ÐìÑîµÏ','-100.00','·¹¿¨',63),('2014-04-02','ÐìÑîµÏ','-47.00','»ð³µÆ±',64),('2014-04-03','ÐìÑîµÏ','-30.00','µç»°·Ñ',65),('2014-05-19','Ðì¼Ñ','-28.80','ÂòÈ¹×Ó',66),('2014-01-01','ÐìÑîµÏ','-3826.03','²î¶î,Ò»´Î²¹Æë',67),('2014-05-23','ÐìÑîµÏ','-98.00','çÛÉôÂòº£·ÉË¿',69),('2014-05-24','Ðì¼Ñ','-68.00','ÂòÐ¬×Ó',70),('2014-05-25','Ðì½¨','5000.00','´æÈëÓà¶î±¦',71),('2014-05-26','Ðì½¨','300.00','´æÈëÓà¶î±¦',72),('2014-05-28','Ðì¼Ñ','-19.80','Ö¹º¹Â¶Á½Æ¿',73),('2014-06-05','ÐìÑîµÏ','-40.00','°ïçÛÉôÂò»¯×±Æ·140£¬ÒøÐÐ¿¨²»¹»£¬×ª³ö40',74),('2014-06-06','ÐìÑîµÏ','3700.00','×ªÈë¹¤×Ê',75),('2014-06-08','ÐìÑîµÏ','-200.00','Óà¶î±¦×ª³öµ½ÓÊÕþÒøÐÐ¿¨(ÍøÒø)',76),('2014-06-21','Ðì½¨','3800.00','¹¤×Ê×ªÈëÓà¶î±¦',77),('2014-06-21','ÑîÊç»¨','1000.00','6ÔÂ14ºÅ¸øµÄ£¬½ñÌì×ªÈë',78),('2014-06-21','ÐìÑîµÏ','200.00','×ªÈëÓà¶î±¦',79),('2014-06-22','Ðì½¨','1500.00','¹¤×Ê×ªÈë(21ºÅÓ¦¸ÃÒøÐÐÏÞ¶îÃ»ÓÐ×ªÍê)',80),('2014-06-22','ÐìÑîµÏ','-100.00','Óà¶î±¦×ª³öµ½ÓÊÕþÒøÐÐ(ÍøÒø)',81),('2014-06-27','ÐìÑîµÏ','-49.25','³äµç»°·Ñ¡£',82),('2014-06-27','Ðì¼Ñ','-30.00','³äµç»°·Ñ¡£',83),('2014-06-29','Ðì¼Ñ','-49.00','TÐô Ç³»ÒÉ«³ßÂë:¾ùÂë',84),('2014-06-29','Ðì¼Ñ','-26.80','2014ÐÂ¿îÏÄ×°º«°æÅ®Ê¿ÏÔÊÝÐ¡½Å¿ãÊúÌõÎÆµ¯Á¦Å·ÃÀ·çÐÝÏÐ¹þÂ×¿ãÅ®³±',85),('2014-06-29','Ðì¼Ñ','-39.50','Ô­ËÞ¿îºÚ°×¸´¹ÅËÉ¸âÐ¬Å·ÃÀÓ¢Â×·çÅ®Ð¬ ºñµ×Ð¬Ô²Í·Ïµ´øµ¥Ð¬ÆÂ¸úÐ¬',86),('2014-06-26','ÐìÑîµÏ','-158.00','ÍÅ¹º»ð¹ø',87),('2014-07-05','Ðì¼Ñ','457.00','¸øÏÖ½ð£¤1500£¬Ðì¼Ñ¸øçÛÉôÂòÊÖ»ú»¨·Ñ£¤1043£¬ËùÒÔ´æÈë£¤457',88),('2014-07-05','ÐìÑîµÏ','3043.00','´æÈë¹¤×Ê(Ò»´Î´æÈë£¤3500£¬ÆäÖÐÐì¼ÑÓÐ£¤457)',89),('2014-07-20','ÐìÑîµÏ','-100.00','×ª³öµ½½¨ÐÐ¿¨',90),('2014-07-27','Ðì½¨','5300.00','¹¤×Ê´æÈëÓà¶î±¦',91),('2014-07-27','ÐìÑîµÏ','-300.00','ÉÙ´æÈë300£¬×ªÖ®',92),('2014-07-27','Ðì¼Ñ','26.80','¹þÂÖ¿ãÍË¿î',93),('2014-07-27','ÐìÑîµÏ','-1000.00','½è¸øÕÅ³½£¤1000',94),('2014-08-06','Ðì¼Ñ','-450.00','ÍÅ¹º´óº£Íë*2°ËÈË²Í',95),('2014-08-07','Ðì¼Ñ','49.00','ÌÔ±¦ÒÂ·þÍË¿î',96),('2014-08-07','ÐìÑîµÏ','5000.00','´æÈë¹¤×Ê',97),('2014-08-08','ÐìÑîµÏ','2300.00','´æÈë¹¤×Ê',98),('2014-08-01','ÐìÑîµÏ','-500.00','Óà¶î±¦×ªÈëÓÊÕþÒøÐÐ¿¨',99),('2014-08-08','ÐìÑîµÏ','-25.80','²¹Æë²î¶î',100),('2014-08-08','Ðì¼Ñ','-56.00','É´È¹¶ÌÐä',101),('2014-08-09','ÐìÑîµÏ','-566.50','¸ø°Ö°ÖÂò»ð³µÆ±',102),('2014-08-10','ÐìÑîµÏ','-1500.00','çÛÉô´æÈë1500£¬×ª´æÖÁÎÒµÄ³É¶¼ÒøÐÐ¿¨',103),('2014-08-10','ÓàÈó»¨','1500.00','´æÈë¹¤×Ê¡£',104),('2014-08-15','Ðì¼Ñ','225.00','ÍÅ¹ºÍË¿î',105),('2014-08-15','Ðì¼Ñ','-49.65','¸øÐì¼Ñ³äµç»°·Ñ ºÅÂë£º15908253719',106),('2014-08-18','ÐìÑîµÏ','-547.50','¸ø°Ö°ÖÂòÈ¥ÎÚÂ³Ä¾ÆëµÄ³µÆ±',107),('2014-08-22','ÐìÑîµÏ','-49.25','¸øçÛçÛ³äµç»°·Ñ',108),('2014-08-24','ÐìÑîµÏ','-100.00','×ª³öµ½ÓÊÕþÒøÐÐ¿¨',109),('2014-08-25','Ðì¼Ñ','-35.90','Âò¿ã×Ó',110),('2014-08-25','Ðì¼Ñ','-39.00','Å£×Ð¿ã',111),('2014-08-29','ÐìÑîµÏ','-15.00','×ªµ½½¨ÉèÒøÐÐ¿¨ ¸øçÛÉôÂòÆ¤´ø',112),('2014-08-30','Ðì¼Ñ','-19.90','ÂòÐ¬×Ó',113),('2014-08-30','Ðì¼Ñ','-39.00','ÂòÐ¬×Ó',114),('2014-08-30','Ðì¼Ñ','-225.00','´óàËÍëÍÅ¹º',115),('2014-08-30','ÐìÑîµÏ','-44.90','ÂòÏ´·¢Ë®¸ø¿Û×Ó',116),('2014-08-28','ÐìÑîµÏ','-89.00','¸øÐì¼ÑÂò°Ù±¦Ïä',117),('2014-08-31','ÐìÑîµÏ','-96.00','¿´µçÓ°ÐÉÇòáÈÆð',118),('2014-08-31','ÐìÑîµÏ','-2000.00','×ªµ½ÓÊÕþÒøÐÐ¿¨',119),('2014-09-03','ÐìÑîµÏ','2000.00','ÓÊÕþÒøÐÐ¿¨×ªÈë',120),('2014-09-03','ÐìÑîµÏ','-500.00','×ª³öµ½ÓÊÕþÒøÐÐ¿¨',121),('2014-09-04','ÐìÑîµÏ','1000.00','ÕÅ³½»¹Ç®1000',122),('2014-09-05','ÐìÑîµÏ','4000.00','¹¤×Ê',123),('2014-09-05','ÐìÑîµÏ','-2000.00','ÂèÂè¸øÁË£¤2000 ×ªÖ®',124),('2014-09-05','ÑîÊç»¨','2000.00','´æÈë¹¤×Ê',125),('2014-09-09','ÐìÑîµÏ','1100.00','°Ö°Ö±¨ÏúµÄ»ð³µÆ±',126),('2014-09-09','Ðì½¨','5200.00','´æÈë¹¤×Ê',127),('2014-09-11','Ðì¼Ñ','-799.00','ÂòºìÃ×ÊÖ»úÒÆ¶¯4G°æ',128),('2014-09-16','Ðì¼Ñ','-17.90','¶ÌÈ¹',129),('2014-09-16','Ðì¼Ñ','-38.61','¼ÓºñÎÀÒÂ',130),('2014-09-20','Ðì½¨','5400.00','¹¤×Ê',131),('2014-09-23','ÐìÑîµÏ','-184.00','ÂòÒÂ·þ',132),('2014-09-24','Ðì¼Ñ','-59.00','Ñ¥×Ó',133),('2014-09-29','ÐìÑîµÏ','-5000.00','×ª³öµ½³É¶¼ÒøÐÐ',134),('2014-10-06','ÐìÑîµÏ','2000.00','³É¶¼ÒøÐÐ´æÈë',135),('2014-10-14','Ðì¼Ñ','-52.00','ÂòÒÂ·þ',136),('2014-10-10','ÐìÑîµÏ','4000.00','¹¤×Ê',137),('2014-10-20','ÐìÑîµÏ','-200.00','×ª³öµ½ÓÊÕþÒøÐÐ',138),('2014-10-22','Ðì¼Ñ','-27.00','È¹×Ó',139),('2014-10-25','Ðì½¨','4500.00','¹¤×Ê',140),('2014-10-25','ÐìÑîµÏ','-500.00','Ö»¸ø°Ö°Ö´æÁË4000(È¡ÁË4500)',141),('2014-10-28','ÐìÑîµÏ','-98.66','¸øçÛçÛ³å»°·Ñ',142),('2014-10-30','Ðì¼Ñ','-38.00','Ðì¼ÑÂòÒÂ·þ',143),('2014-11-06','ÐìÑîµÏ','4000.00','¹¤×Ê',144),('2014-11-02','ÐìÑîµÏ','-1000.00','×ª³öµ½ÒøÐÐ¿¨',145),('2014-11-15','ÐìÑîµÏ','-2400.00','×ª³öµ½ÓÊÕþÒøÐÐ',146),('2014-11-23','Ðì½¨','5200.00','¹¤×Ê',147),('2014-11-30','ÐìÑîµÏ','-280.00','ÂèÂèÂò»¯×±Æ·',148),('2014-12-05','ÐìÑîµÏ','4200.00','¹¤×Ê',149),('2014-12-09','ÐìÑîµÏ','-154.90','¸ø¿Û¿ÛÂò»¯×±Æ·',150),('2014-12-18','ÐìÑîµÏ','-200.00','×ª³öµ½ÓÊÕþÒøÐÐ¿¨',151),('2014-12-20','Ðì¼Ñ','-40.00','Âò¿ã²¹Íà',152);
/*!40000 ALTER TABLE `YuEBao` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-12-23 21:24:15
