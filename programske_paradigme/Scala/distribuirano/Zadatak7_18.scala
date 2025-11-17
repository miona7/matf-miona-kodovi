import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_18 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val putanja = "/home/miona/Downloads/cas10_11/Scala/datoteke/zaposleni.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije
			.filter(_.contains("IT_PROG"))
			.map(l => {
				val niz = l.split("IT_PROG ")
				(niz(1).replace(",", ".").toFloat, 1)
			})
			.reduce((a, b) => (a._1 + b._1, a._2 + b._2))

		println(podaci._1 / podaci._2)

		sk.stop()
	}
}
