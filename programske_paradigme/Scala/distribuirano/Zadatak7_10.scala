import org.apache.spark.{SparkConf, SparkContext}

import java.util.Scanner

object Zadatak7_10 {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val sc : Scanner = new Scanner(System.in)
		val n : Int = sc.nextInt()

		val niz : Array[Int] = (1 to n).toArray
		// niz.foreach(x => println(x))

		val nizRDD = sk.parallelize(niz)
		val faktorijeli = nizRDD.map(x => {
			var rez = 1
			for(i <- 1 to x) {
				rez = rez * i
			}
			rez
		}).collect()

		faktorijeli.foreach(x => println(x))
		
		sk.stop()
	}
}
