import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_15 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla3")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val putanja : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/temperatureBoston.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije
			.map(l => {
				val niz = l.split(" ")
				(niz(3), (niz(2).toInt, niz(4).toFloat))
			})
			.reduceByKey((a, b) => if(a._2 > b._2) a else b)
			.sortByKey()
			.collect()
			.foreach(x => println(x._1 + " " + "(" + x._2._1 + ", " + x._2._2 + ")"))

		sk.stop()
	}
}
