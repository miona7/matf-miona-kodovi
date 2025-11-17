import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue
import java.util.concurrent.atomic.AtomicLong

object Krediti {
	def main(args: Array[String]): Unit = {
		val sc : Scanner = new Scanner(System.in)
		val kapital : AtomicLong = new AtomicLong(sc.nextLong())
		val pocetniKapital : Long = kapital.get()
		val kamata : Int = sc.nextInt()
		val brSluzbenica : Int = sc.nextInt()

		val sc1 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/red_klijenata.txt"))
		val klijenti : ConcurrentLinkedQueue[Klijent] = new ConcurrentLinkedQueue[Klijent]()
		while(sc1.hasNextLine) {
			klijenti.add(new Klijent(sc1.next(), sc1.nextInt()))
		}
		println(klijenti)

		val zaduzeni : ConcurrentLinkedQueue[Klijent] = new ConcurrentLinkedQueue[Klijent]()

		// init()
		val sluzbenice : Array[Sluzbenica] = new Array[Sluzbenica](brSluzbenica)
		for(i <- 0 until brSluzbenica) {
			sluzbenice(i) = new Sluzbenica(kapital, kamata, klijenti, zaduzeni)
		}

		// start()
		for(s <- sluzbenice) {
			s.start()
		}

		// join()
		for(s <- sluzbenice) {
			s.join()
		}

		println(zaduzeni)

		// rez
		var ukupnoZaduzenje : Float = 0
		val it = zaduzeni.iterator()
		while(it.hasNext) {
			ukupnoZaduzenje += it.next().getDug
		}
		println(s"Banka je zaradila ${ukupnoZaduzenje - pocetniKapital}")
	}

	class Klijent(ime : String, pozajmica : Int) {
		var dug : Float = 0

		def getIme : String = ime
		def getPozajmica : Int = pozajmica
		def getDug : Float = dug

		def setDug(d : Float) = {
			dug = d
		}

		override def toString: String = s"Klijent ${ime} sa pozajmicom ${pozajmica}e i dugom ${dug}e"
	}

	class Sluzbenica(kapital : AtomicLong, kamata : Int, klijenti : ConcurrentLinkedQueue[Klijent], zaduzeni : ConcurrentLinkedQueue[Klijent]) extends Thread {
		override def run(): Unit = {
			while(true) {
				val k : Klijent = klijenti.poll()
				if(k == null) {
					return
				}

				println(s"Klijent ${k.getIme} razgovara sa sluzbenicom")
				Thread.sleep(1000)

				kapital.synchronized {
					if(k.getPozajmica > kapital.get()) {
						println(s"Klijent ${k.getIme} ne moze dobiti kredit")
					} else {
						k.setDug(k.getPozajmica * ((100 + kamata.toFloat) / 100))
						val novKapital = kapital.get() - k.getPozajmica
						kapital.set(novKapital)
						println(s"Klijent ${k.getIme} je dobio pozajmicu u iznosu od ${k.getPozajmica}e i sada ima dug od ${k.getDug}e")
						zaduzeni.add(k)
					}
				}
			}
		}
	}
}
