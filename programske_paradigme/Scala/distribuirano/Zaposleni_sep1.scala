import org.apache.spark.{SparkConf, SparkContext}

import scala.compat.Platform

object Zaposleni_sep1 {
	def main(args: Array[String]): Unit = {
		val k = new SparkConf().setAppName("bla").setMaster("local[4]")
		val sk = new SparkContext(k)

		val linije = sk.textFile("/home/miona/Downloads/zaposleni.txt")

		val zaposleni = linije
			.map(l => {
				val niz = l.split(" ")
				(niz(2), niz(7).toDouble)
			})
			// .foreach(x => println(x._1 + " " + x._2) )

		val zene = zaposleni
			.filter(z => z._1.equalsIgnoreCase("F"))
			.takeSample(false, 3, Platform.currentTime)
			.map(x => x._2)
			.sum

			// .foreach(x => println(x))
		println(s"Prosek zene = ${zene / 3.0}")

		val muskarci = zaposleni
			.filter(z => z._1.equalsIgnoreCase("M"))
			.takeSample(false, 3, Platform.currentTime)
			.map(x => x._2)
			// .foreach(x => println(x))

		println(s"Prosek muskarci = ${muskarci.sum / muskarci.size.toDouble}")

		sk.stop()
	}
}
