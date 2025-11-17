import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object MuzickiIzvodjaci {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Muzickiizvodjaci")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/IdeaProjects/TMP/src/main/scala/izvodjaci.csv"
		val linije : RDD[String] = sk.textFile(path)

		linije
			.map(_.split(","))
			.filter(x => x(4) == "Rock" && x(5).toInt <= 100)
			.map(x => (x(3).toInt, x(2).toInt))
			.groupByKey()
			.sortByKey()
			.map(el => {
				val niz = el._2
				(el._1, niz.sum.toFloat / niz.size)
			})
			.collect()
			.foreach(x => printf("(%d, %.2f)\n", x._1, x._2))

		sk.stop()
	}
}
