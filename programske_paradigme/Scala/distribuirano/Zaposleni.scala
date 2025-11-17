import org.apache.spark.{SparkConf, SparkContext}

object Zaposleni {
	def main(args: Array[String]): Unit = {
		val k = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk = new SparkContext(k)

		val linije = sk.textFile("/home/miona/Downloads/zaposleni.txt")
			//.foreach(x => println(x))

		val rez = linije.map(l => {
			val niz = l.split(" ")
			(niz(6), niz(7).toDouble)
		})
			.groupByKey()
			.map(x => {
				val plate = x._2
				val prosek = plate.sum / plate.size.toDouble
				(x._1, prosek)
			})
			.foreach(x => println(x._1 + " " + x._2))

		sk.stop()
	}
}
