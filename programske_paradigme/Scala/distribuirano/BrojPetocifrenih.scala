import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object BrojPetocifrenih {
	def main(args: Array[String]): Unit = {
		val conf : SparkConf = new SparkConf().setAppName("BrojPetocifrenih").setMaster("local[4]")
		val context : SparkContext = new SparkContext(conf)

		val path : String = "/home/miona/Downloads/cas8_9/Scala/datoteke/brojevi1.txt"
		val data : RDD[String] = context.textFile(path)

		val brojPetocifrenih  = data.filter(_.length == 5).count()

		context.stop()
		println(brojPetocifrenih)
	}
}
