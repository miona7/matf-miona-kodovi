import java.io.File
import java.util.Scanner
import scala.collection.mutable.ArrayBuffer

object Kupovina {
	def main(args: Array[String]): Unit = {

		val sc1 = new Scanner(new File("/home/miona/Downloads/kupovina.txt"))
		val niz = new ArrayBuffer[(Int, Int)]()

		while(sc1.hasNextLine) {
			niz.append((sc1.nextInt(), sc1.nextInt()))
		}
		sc1.close()
		val brDana = niz.length
		val rez = new Array[Float](brDana)

		val sc = new Scanner(System.in)
		val n = sc.nextInt()
		sc.close()


		val korak = Math.ceil(brDana.toDouble / n.toDouble).toInt
		val niti = new Array[Nit](n)
		for (i <- 0 until n) {
			niti(i) = new Nit(i * korak, Math.min((i + 1) * korak, brDana), niz, rez)
		}

		for(n <- niti) {
			n.start()
		}

		for(n <- niti) {
			n.join()
		}

		for(i <- rez.indices) {
			println(i + " " + rez(i))
		}
	}

	class Nit(poc : Int, kraj : Int, niz : ArrayBuffer[(Int, Int)], rez : Array[Float]) extends Thread {
		override def run(): Unit = {
			for(i <- poc until kraj) {
				rez(i) = niz(i)._2.toFloat / niz(i)._1.toFloat
			}
		}
	}
}
