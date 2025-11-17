import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

object UspesnaPreuzimanja {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf().setAppName("UspesnaPreuzimanja").setMaster("local[4]")
		val sc : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/mavenLog.txt"
		val data : RDD[String] = sc.textFile(path)

		val res = data.filter(x => x.startsWith("Downloading: ") || x.startsWith("Downloaded: "))
			.map(x => {
				val niz = x.split(" ")
				(niz(1),  niz(0))
			})
			.groupByKey()
			// .collect()
			//.foreach(x => println(x))

		val downloading : Long = res.count()
		val downloaded : Long = res.filter(x => {
			var ind : Boolean = false
			for(y <- x._2) {
				if(y == "Downloaded:") {
					ind = true
				}
			}
			ind
		})
			.count()

		println(downloaded*100.0/downloading)

		sc.stop()
	}
}
