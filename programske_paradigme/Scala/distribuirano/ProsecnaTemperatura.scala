import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object ProsecnaTemperatura {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("TemperatureBoston")
			.setMaster("local[4]")
		val sc : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/temperatureBoston.txt"
		val data : RDD[String] = sc.textFile(path)

		val res = data
			.map(l => {
				val tmp = l.split(" ")
				(tmp(3), tmp(4).toFloat)
			})
			.aggregateByKey((0.0, 0))((ak, vr) => (ak._1 + vr, ak._2 + 1) , (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2))
			.sortByKey()
			.collect()
			.foreach(x => println(x._1 + " " + (x._2._1 / x._2._2)))

		sc.stop()
	}
}
