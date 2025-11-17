import java.util.Scanner

object ZbirVektora {
	def main(args: Array[String]): Unit = {
		val sc : Scanner = new Scanner(System.in)
		val n : Int = sc.nextInt()

		var v1 : Array[Int] = new Array[Int](n)
		for(i <- 0 until n) {
			v1(i) = sc.nextInt()
		}

		val v2 : Array[Int] = new Array[Int](n)
		for(i <- 0 until n) {
			v2(i) = sc.nextInt()
		}

		val brNiti : Int = sc.nextInt()
		val korak : Int = Math.ceil(n / brNiti.toFloat).toInt

		val brojaci : Array[Brojac] = new Array[Brojac](brNiti)
		for(i <- 0 until brNiti) {
			brojaci(i) = new Brojac(i*korak, Math.min((i+1)*korak, n), v1, v2)
		}

		for(b <- brojaci) {
			b.start()
		}

		for(b <- brojaci) {
			b.join()
		}

		v1.foreach(x => print(x + " "))
	}

	class Brojac(pocetak : Int, kraj : Int, v1 : Array[Int], v2 : Array[Int]) extends Thread {
		override def run(): Unit = {
			for(i <- pocetak until kraj) {
				v1(i) += v2(i)
			}
		}
	}
}
