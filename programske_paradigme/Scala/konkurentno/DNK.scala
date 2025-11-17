import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap
import scala.collection.mutable.ArrayBuffer

object DNK {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(System.in)
		//println("Broj procesora na racunaru je " + Runtime.getRuntime.availableProcessors())
		val brNiti : Int = sc1.nextInt()

		val sc2 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/bio_podaci.txt"))
		val sekvence : ArrayBuffer[String] = new ArrayBuffer[String]()
		while(sc2.hasNextLine) {
			sekvence.append(sc2.nextLine())
		}

		val brSekvenci : Int = sekvence.length
		val rez : ConcurrentHashMap[Char, Int] = new ConcurrentHashMap[Char, Int](4, 4, brNiti)
		rez.put('a', 0)
		rez.put('c', 0)
		rez.put('g', 0)
		rez.put('t', 0)

		// init()
		val brojaci : Array[Brojac] = new Array[Brojac](brNiti)
		val korak : Int = Math.ceil(brSekvenci/brNiti.toDouble).toInt
		for(i <- 0 until brNiti) {
			brojaci(i) = new Brojac(i*korak, Math.min((i+1)*korak, brSekvenci), sekvence, rez)
		}

		// start()
		for(b <- brojaci) {
			b.start()
		}

		// join()
		for(b <- brojaci) {
			b.join()
		}

		println("Rezultati su sledeci: ")
		println("a: " + rez.get('a'))
		println("c: " + rez.get('c'))
		println("g: " + rez.get('g'))
		println("t: " + rez.get('t'))
	}

	class Brojac(pocetak : Int, kraj : Int, sekvence : ArrayBuffer[String], rez : ConcurrentHashMap[Char, Int]) extends Thread {
		override def run(): Unit = {
			for(i <- pocetak until kraj) {
				val a : Int = sekvence(i).count(_ == 'a')
				val c : Int = sekvence(i).count(_ == 'c')
				val g : Int = sekvence(i).count(_ == 'g')
				val t : Int = sekvence(i).count(_ == 't')

				rez.synchronized {
					rez.replace('a', rez.get('a') + a)
					rez.replace('c', rez.get('c') + c)
					rez.replace('g', rez.get('g') + g)
					rez.replace('t', rez.get('t') + t)
				}
			}
		}
	}
}
