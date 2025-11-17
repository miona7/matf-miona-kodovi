import org.apache.spark.{SparkConf, SparkContext}

object TempBoston {
	def main(args: Array[String]): Unit = {
		val k = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk = new SparkContext(k)

		val linije = sk.textFile("/home/miona/Downloads/cas10_11/Scala/datoteke/temperatureBoston.txt")

		val rez = linije
			.map(l => {
				val niz = l.split(" ")
				(niz(2), niz(4).toDouble)
			})
			.groupByKey()
			.map(x => (x._1, (x._2.min, x._2.max )))
			.collect()
			.sortWith((a, b) => a._1.toInt <= b._1.toInt)
			.foreach(x => println(x._1 + " " + x._2))

		sk.stop()
	}
}
