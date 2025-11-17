import org.apache.spark.{SparkConf, SparkContext}
import org.apache.spark.rdd.RDD

object LogPoruke {

	def main(args: Array[String]): Unit = {
		val conf : SparkConf = new SparkConf()
			.setAppName("LogPoruke")
			.setMaster("local[4]")
		val context : SparkContext = new SparkContext(conf)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/log.txt"
		val data: RDD[String] = context.textFile(path)

		val res = data
			.filter(l => (l.startsWith("[warn] ") || l.startsWith("[info] ") || l.startsWith("[error] ")) && l.contains("java"))
			.map(l => (l.split(" ")(0), l))
			.groupByKey()
			.map(l => (l._1, l._2.size))
			.collect()

		context.stop()

		res.foreach(x => println(x))
	}
}
