import java.io.{File, PrintWriter}
import java.util.Scanner
import scala.Array.ofDim

object MnozenjeMatrica {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/matrica1.txt"))
		val n : Int = sc1.nextInt()
		val m1 : Int = sc1.nextInt()

		val sc2 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/matrica2.txt"))
		val m2 : Int = sc2.nextInt()
		val k : Int = sc2.nextInt()

		if(m1 != m2) {
			println("Greska, dimenzije matrica moraju da se poklapaju!")
			return
		}

		val matrica1 : Array[Array[Int]] = ofDim[Int](n, m1)
		for(i <- 0 until n) {
			for(j <- 0 until m1) {
				matrica1(i)(j) = sc1.nextInt()
			}
		}

		val matrica2 : Array[Array[Int]] = ofDim[Int](m1, k)
		for(i <- 0 until m2) {
			for(j <- 0 until k) {
				matrica2(i)(j) = sc2.nextInt()
			}
		}

		val pw : PrintWriter = new PrintWriter(new File("matrica3.txt"))
		val rezultat : Array[Array[Int]] = ofDim(n, k)

		// init()
		val mnozioci : Array[Mnozilac] = new Array[Mnozilac](n)
		for(i <- 0 until n) {
			mnozioci(i) = new Mnozilac(m1, k, matrica1(i), matrica2, rezultat(i))
		}

		// start()
		for(i <- 0 until n) {
			mnozioci(i).start()
		}

		// join()
		for(i <- 0 until n) {
			mnozioci(i).join()
		}

		// rez
		pw.append(s"$n $k \n")
		for(i <- 0 until n) {
			for(j <- 0 until k) {
				pw.append(s"${rezultat(i)(j)} ")
			}
			pw.append("\n")
		}

		pw.close()
	}

	class Mnozilac(m : Int, k : Int, vrsta1 : Array[Int], matrica2 : Array[Array[Int]], rezultat : Array[Int]) extends Thread {
		override def run(): Unit = {
			for(i <- 0 until k) {
				rezultat(i) = sp(i)
			}
		}

		def sp(j : Int): Int = {
			var rez : Int = 0
			for (i <- 0 until m) {
				rez += vrsta1(i) * matrica2(i)(j)
			}
			rez
		}
	}
}
