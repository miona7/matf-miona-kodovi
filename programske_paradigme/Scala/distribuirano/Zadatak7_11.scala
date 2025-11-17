import org.apache.spark.{SparkConf, SparkContext}

import java.util.Scanner

object Zadatak7_11 {
	def main(args: Array[String]): Unit = {
		val k = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk = new SparkContext(k)

		val sc = new Scanner(System.in)
		val n = sc.nextInt()
		val niz = (1 to n).toArray

		val nizRDD = sk.parallelize(niz)
		val rez = nizRDD.map(x => 1.0/x.toFloat).reduce((a, b) => a + b)
		println(rez)

		sk.stop()
	}
}
