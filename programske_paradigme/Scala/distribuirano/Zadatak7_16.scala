import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object Zadatak7_16 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Bla3")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val putanja : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/mavenLog.txt"
		val linije : RDD[String] = sk.textFile(putanja)

		val podaci = linije
			.filter(l => { l.contains("Downloaded:") && l.contains("apache") })
			.map(l => {
				val niz = l.split("\\(")
				niz(1).stripSuffix(")")
			})
			.saveAsTextFile("ApacheDownloaded")

		sk.stop()
	}
}
