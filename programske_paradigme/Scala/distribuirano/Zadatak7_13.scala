import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_13 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla1")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val putanja : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/knjiga.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije
			.flatMap(_.toCharArray)
			.filter(_.isDigit)
			.map(c => (c.toString, 1))
			.reduceByKey(_ + _)
			.sortByKey()

		podaci
			.collect()
			.foreach(x => println(x._1 + " " + x._2))

		sk.stop()
	}
}
