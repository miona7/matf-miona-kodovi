import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

import java.util.Scanner

object ParniKvadrati {
	def main(args: Array[String]): Unit = {
		val conf : SparkConf = new SparkConf().setAppName("ParniKvadrati").setMaster("local[4]")
		val context : SparkContext = new SparkContext(conf)

		val sc : Scanner = new Scanner(System.in)
		val n : Int = sc.nextInt()

		val niz = (2 to n by 2).toArray
		val nizRDD : RDD[Int] = context.parallelize(niz)

		val nizKvadrata = nizRDD.map(x => x*x).collect()

		context.stop()
		nizKvadrata.foreach(x => println(x))
	}
}
