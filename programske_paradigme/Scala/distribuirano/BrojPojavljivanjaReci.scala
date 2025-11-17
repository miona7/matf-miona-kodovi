import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object BrojPojavljivanjaReci {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf().setAppName("BrojPojavljivanjaReci").setMaster("local[4]")
		val sc : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/knjiga.txt"
		val data : RDD[String] = sc.textFile(path)

		val rez = data
			.flatMap(_.split(" "))
			.map(rec => (rec, 1))
			.reduceByKey(_ + _)
			.sortByKey()
			.saveAsTextFile("res.txt")

		sc.stop()
	}
}
