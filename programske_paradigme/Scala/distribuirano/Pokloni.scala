import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

import scala.compat.Platform

object Pokloni {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Pokloni")
			.setMaster("local[4]")
		val sc : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/zaposleni.txt"
		val data : RDD[String] = sc.textFile(path)

		val res = data
			.filter(_.contains("IT_PROG"))
			.map(l => {
				val tmp = l.split(" ")
				(tmp(0), tmp(1), tmp(3).toLowerCase() + "@company.com")
			})
			.takeSample(false, 3, Platform.currentTime)
			.foreach(x => println(x))

		sc.stop()
	}
}

