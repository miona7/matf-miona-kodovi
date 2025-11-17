import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Automobili {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Automobili")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/IdeaProjects/TMP/src/main/scala/cars.csv"
		val linije : RDD[String] = sk.textFile(path)

		val podaci = linije.filter(l => {
			val niz = l.split(",")
			val brzine = niz(2).split(" ")
			niz(0) == "AWD" && niz(7).toInt > 2010 && niz(8).toInt > 300 && niz(4).equalsIgnoreCase("Gasoline") && niz(2).contains("Automatic") && brzine(0).toInt >= 5
		})
			.map(l => {
				val niz = l.split(",")
				(niz(3).toFloat, 1)
			})
			.reduce((a, b) => (a._1 + b._1, a._2 + b._2))

		//val rez = podaci.sum().toFloat / podaci.count()
		println(podaci._1 / podaci._2)
		//.collect().foreach(x => println(x))

		sk.stop()
	}
}
