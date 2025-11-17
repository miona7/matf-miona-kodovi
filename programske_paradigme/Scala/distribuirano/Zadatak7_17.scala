import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

import java.util.Scanner
import scala.compat.Platform
import scala.util.Random

object Zadatak7_17 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val sc : Scanner = new Scanner(System.in)
		val marka : String = sc.next()

		val putanja : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/uredjaji.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije
			.filter(_.contains(marka))
			.takeSample(false, 5, Platform.currentTime)

		podaci.foreach(x => println(x))

		sk.stop()
	}
}
