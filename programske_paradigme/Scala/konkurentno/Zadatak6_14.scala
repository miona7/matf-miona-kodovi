import java.util.Scanner
import scala.Array.ofDim

object Zadatak6_14 {
	def main(args: Array[String]): Unit = {
		val sc = new Scanner(System.in)

		val n = sc.nextInt()
		val v = new Array[Int](n)

		for(i <- 0 until n) {
			v(i) = sc.nextInt()
		}

		val m = sc.nextInt()
		val mat = ofDim[Int](m, n)
		for(i <- 0 until m) {
			for(j <- 0 until n) {
				mat(i)(j) = sc.nextInt()
			}
		}

		val rez = ofDim[Int](m, n)

		val brNiti = sc.nextInt()
		val korak = Math.ceil(m.toDouble / brNiti.toDouble).toInt
		val mnozioci = new Array[Mnozilac](brNiti)
		for(i <- 0 until brNiti) {
			mnozioci(i) = new Mnozilac(i*korak, Math.min((i+1)*korak, m), v, mat, rez)
		}

		for(m <- mnozioci) {
			m.start()
		}

		for(m <- mnozioci) {
			m.join()
		}

		for(i <- 0 until m) {
			for(j <- 0 until n) {
				print(rez(i)(j) + " ")
			}
			println()
		}

		sc.close()
	}

	class Mnozilac(poc : Int, kraj : Int, vektor : Array[Int], mat : Array[Array[Int]], rez : Array[Array[Int]]) extends Thread {
		override def run(): Unit = {
			for(i <- poc until kraj) {
				for(j <- vektor.indices) {
					rez(i)(j) = vektor(j) * mat(i)(j)
				}
			}
		}
	}
}
