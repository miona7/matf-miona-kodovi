import org.apache.spark.{SparkConf, SparkContext}

object Milijarderi {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf()
			.setAppName("Milijarderi")
			.setMaster("local[4]")
		val sk : SparkContext = new SparkContext(c)

		val path = "/home/miona/IdeaProjects/TMP/src/main/scala/milijarderi.csv"
		val linije = sk.textFile(path)

		val podaci = linije
			.filter(l => {
				if(l.contains("\"")) {
					val niz = l.split("\"")
					// niz(0) - pre navodnika
					// niz(1) - unutar
					// niz(2) - posle
					var tmp = niz(0).split(",")
					val rang : Int = tmp(1).toInt
					val godina : Int = tmp(2).toInt

					tmp = niz(2).split(",")
					val pol = tmp(1)
					val lok = tmp(2)
					pol.equalsIgnoreCase("male") && rang <= 50 && godina >= 2000 && lok.equalsIgnoreCase("Europe")
				} else {
					val niz = l.split(",")
					niz(5).equalsIgnoreCase("male") && niz(1).toInt <= 50 && niz(2).toInt >= 2000 && niz(6).equalsIgnoreCase("Europe")
				}
			})
			.map(l => {
				if(l.contains("\"")) {
					val niz = l.split("\"")
					// niz(0) - pre navodnika
					// niz(1) - unutar
					// niz(2) - posle
					val tmp = niz(2).split(",")
					val godine : Int = tmp(0).toInt
					(godine, 1)
				} else {
					val niz = l.split(",")
					(niz(4).toInt, 1)
				}
			})
			.reduce((a, b) => (a._1 + b._1, a._2 + b._2))

		println(podaci._1 / podaci._2)

		sk.stop()
	}
}
