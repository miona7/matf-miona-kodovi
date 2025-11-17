import java.io.{File, PrintWriter}
import java.util.Scanner
import scala.Array.ofDim

object Zadatak6_15 {
	def main(args: Array[String]): Unit = {
		val sc = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/matrica1.txt"))

		val n = sc.nextInt()
		val m = sc.nextInt()
		val mat = ofDim[Int](n, m)
		for(i <- 0 until n) {
			for(j <- 0 until m) {
				mat(i)(j) = sc.nextInt()
			}
		}

		val rez = ofDim[Int](m, n)

		val niti = new Array[Nit](n)
		for(i <- 0 until n) {
			niti(i) = new Nit(mat(i), i, rez, m)
		}

		for(n <- niti) {
			n.start()
		}

		for(n <- niti) {
			n.join()
		}

		val pw = new PrintWriter(new File("transponovana_matrica.txt"))
		pw.append(s"$m $n\n")
		for(i <- 0 until m) {
			for(j <- 0 until n) {
				pw.append(s"${rez(i)(j)} ")
			}
			pw.append("\n")
		}
		pw.close()

		sc.close()
	}

	class Nit(vrsta : Array[Int], i : Int, rez : Array[Array[Int]], m : Int) extends Thread {
		override def run(): Unit = {
			for(j <- 0 until m) {
				rez(j)(i) = vrsta(j)
			}
		}
	}
}
