import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

import java.io.{File, PrintWriter}

object UredjajiTransakcije {
	def main(args: Array[String]): Unit = {
		val c : SparkConf = new SparkConf().setAppName("UredjajiTransakcije").setMaster("local[4]")
		val sc : SparkContext = new SparkContext(c)

		val path : String = "/home/miona/Downloads/cas10_11/Scala/datoteke/uredjaji.txt"
		val data : RDD[String] = sc.textFile(path)

		val res = data.map(linija => {
				val niz = linija.split(" ")
				(niz(0), niz.drop(1).mkString(" "))
			})
			.groupByKey()
			.collect()
			.foreach(x => {
				val pw : PrintWriter = new PrintWriter(new File(x._1.toLowerCase() + ".txt"))
				pw.write("-----" + x._1 + "-----\n")
				x._2.foreach(dec => pw.append(dec + "\n"))
				pw.close()
			})

		sc.stop()
	}
}
