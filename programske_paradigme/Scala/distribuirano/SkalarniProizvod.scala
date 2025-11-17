import org.apache.spark.{SparkConf, SparkContext}

object SkalarniProizvod {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf().setAppName("SkalarniProzivod").setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val p1 : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/vektor1.txt"
		val v1 = sk.textFile(p1).flatMap(x => x.split(", ")).map(x => x.toInt)

		val p2 : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/vektor2.txt"
		val v2 = sk.textFile(p2).flatMap(x => x.split(", ")).map(x => x.toInt)

		val sp = v1.zip(v2).map(x => x._1 * x._2).sum()
		println(sp)

		sk.stop()
	}
}
