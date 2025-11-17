import io.netty.util.internal.ThreadLocalRandom

import java.io.File
import java.util.Scanner

object TuristickaAgencija {
	def main(args: Array[String]): Unit = {
		val sc : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/ucesnici.txt"))

		val dobitnici : Array[String] = new Array[String](5)

		val n : Int = sc.nextInt()
		val klijenti : Array[Klijent] = new Array[Klijent](n)
		for(i <- 0 until n) {
			klijenti(i) = new Klijent(sc.next(), sc.next(), sc.nextInt(), dobitnici)
		}

		for(i <- 0 until n) {
			klijenti(i).start()
		}

		println("Nagradna igra u toku...")
		Thread.sleep(5000)

		dobitnici.synchronized {
			val izvuceniIndeksi = ThreadLocalRandom.current().ints(0, n).distinct().limit(5).toArray

			for(j <- 0 until izvuceniIndeksi.length) {
				dobitnici(j) = klijenti(izvuceniIndeksi(j)).getIme
			}

			dobitnici.notifyAll()
		}

	}

	class Klijent(ime : String, prezime : String, cena : Int, dobitnici : Array[String]) extends Thread {
		def getIme : String = ime

		override def run(): Unit = {
			dobitnici.synchronized {
				dobitnici.wait()
			}

			for(d <- dobitnici) {
				if(d == ime) {
					println(s"Cestitamo ${ime} ${prezime} je dobio popust i cena karte je sada ${cena * 0.8}e")
					return
				}
			}

			println(s"Nazalost ${ime} ${prezime} niste dobili nagradu")
		}
	}
}
