import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_14 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla2")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val putanja : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/log.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije.filter(_.contains("[error]"))

		//podaci.foreach(x => println(x))

		println(podaci.count())

		sk.stop()
	}
}
