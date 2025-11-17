import io.netty.util.internal.ThreadLocalRandom

import java.io.File
import java.util.Scanner
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

object Kladionica {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/utakmice.txt"))
		val utakmice : mutable.HashMap[String, (Float, Float, Float, Char)] = new mutable.HashMap[String, (Float, Float, Float, Char)]()
		while(sc1.hasNextLine) {
			utakmice.put(sc1.nextLine(), (sc1.nextFloat(), sc1.nextFloat(), sc1.nextFloat(), '-'))
			sc1.nextLine()
		}
		println(utakmice)

		val sc2 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/kladionicari.txt"))
		val kladionicari : ArrayBuffer[Kladionicar] = new ArrayBuffer[Kladionicar]()
		while(sc2.hasNextLine) {
			val ime : String = sc2.next()
			val novac : Int = sc2.nextInt()
			val tiket : mutable.HashMap[String, Char] = new mutable.HashMap[String, Char]()
			for (i <- 0 until 5) {
				sc2.nextLine()
				tiket.put(sc2.nextLine(), sc2.next()(0))
			}
			kladionicari.append(new Kladionicar(ime, novac, tiket, utakmice))
		}
		println(kladionicari)

		for(k <- kladionicari) {
			k.start()
		}

		println("Cekamo da se utakmice zavrse")
		Thread.sleep(5000)

		val rez : Array[Char] = Array('1', 'x', '2')
		for(u <- utakmice) {
			utakmice(u._1) = (u._2._1, u._2._2, u._2._3, rez(ThreadLocalRandom.current().nextInt(0, 3)))
		}

		utakmice.synchronized {
			utakmice.notifyAll()
		}

		for(k <- kladionicari) {
			k.join()
		}

		println(kladionicari)
	}

	class Kladionicar(ime : String, novac : Int, tiket : mutable.HashMap[String, Char], utakmice : mutable.HashMap[String, (Float, Float, Float, Char)]) extends Thread {
		var dobitak : Float = 0

		override def run(): Unit = {
			utakmice.synchronized {
				utakmice.wait()
			}

			var pogodjeno: Int = 0
			var kvota : Float = 0

			for(t <- tiket) {
				if(t._2 == utakmice(t._1)._4) {
					pogodjeno += 1
					if(utakmice(t._1)._4 == '1') {
						kvota += utakmice(t._1)._1
					} else if(utakmice(t._1)._4 == 'x') {
						kvota += utakmice(t._1)._2
					} else if(utakmice(t._1)._4 == '2') {
						kvota += utakmice(t._1)._3
					}
				}
				if(pogodjeno != 0) {
					dobitak = kvota * novac / pogodjeno
				}
			}
		}

		override def toString: String = s"Kladionicar ${ime} je stavio ${novac} na ${tiket} i dobio je ${dobitak}"
	}
}
