import java.util.Scanner

object Zadatak6_13 {
	def main(args: Array[String]): Unit = {
		val sc = new Scanner(System.in)

		val n = sc.nextInt()
		val v = new Array[Int](n)
		for(i <- 0 until n) {
			v(i) = sc.nextInt()
		}

		val s = sc.nextInt()

		val brNiti = sc.nextInt()
		val mnozioci = new Array[Mnozilac](brNiti)
		val korak = Math.ceil(n.toFloat / brNiti.toFloat).toInt
		// println(korak)

		for(i <- 0 until brNiti) {
			mnozioci(i) = new Mnozilac(i*korak, Math.min((i+1)*korak, n), s, v)
		}

		for(i <- 0 until brNiti) {
			mnozioci(i).start()
		}

		for(i <- 0 until brNiti) {
			mnozioci(i).join()
		}

		v.foreach(x => print(x + " "))

		sc.close()
	}
	class Mnozilac(poc : Int, kraj : Int, skalar : Int, vektor : Array[Int]) extends Thread {
		override def run(): Unit = {
			for(i <- poc until kraj) {
				vektor(i) = vektor(i) * skalar
			}
		}
	}
}
