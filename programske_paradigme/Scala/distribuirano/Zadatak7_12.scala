import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_12 {
	def main(args: Array[String]): Unit = {
		val k = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk = new SparkContext(k)

		val v1 = sk.textFile("/home/miona/Downloads/cas10_11/Scala/datoteke/vektor1.txt")
			.flatMap(_.split(", "))

		val v2 = sk.textFile("/home/miona/Downloads/cas10_11/Scala/datoteke/vektor2.txt")
			.flatMap(_.split(", "))

		val zbir = v1.zip(v2).map(x => x._1.toInt + x._2.toInt).collect()

		zbir.foreach(x => print(x + " "))

		sk.stop()
	}
}
