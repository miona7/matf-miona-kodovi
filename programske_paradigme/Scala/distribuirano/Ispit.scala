import io.netty.util.internal.ThreadLocalRandom

import java.io.File
import java.util.Scanner
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.ConcurrentLinkedQueue

object Ispit {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(System.in)
		val brMehanicara : Int = sc1.nextInt()

		val sc2 : Scanner = new Scanner(new File("/home/miona/IdeaProjects/TMP/src/main/scala/automobili.txt"))
		val redAutomobila : ConcurrentLinkedQueue[(String, String)] = new ConcurrentLinkedQueue[(String, String)]()
		while(sc2.hasNextLine) {
			redAutomobila.add(sc2.next(), sc2.next())
		}
		// println(redAutomobila)

		val servisirani : ConcurrentLinkedQueue[(String, String)] = new ConcurrentLinkedQueue[(String, String)]()
		val redovno : AtomicInteger = new AtomicInteger(0)
		val popravka : AtomicInteger = new AtomicInteger(0)
		val vreme : AtomicInteger = new AtomicInteger(0)

		// init()
		val mehanicari : Array[Mehanicar] = new Array[Mehanicar](brMehanicara)
		for(i <- 0 until brMehanicara) {
			mehanicari(i) = new Mehanicar(redAutomobila, servisirani, redovno, popravka, vreme)
		}

		// start()
		for(m <- mehanicari) {
			m.start()
		}

		// join()
		for(m <- mehanicari) {
			m.join()
		}

		// rez
		println(s"Redovno odrzavanje: ${redovno.get()} vozila")
		println(s"Popravka: ${popravka.get()} vozila")
		println(s"Prosecno vreme servisiranja: ${vreme.get().toFloat / servisirani.size()} sekunde")

		// println(redAutomobila)
		// println(servisirani)
	}

	class Mehanicar(redAutomobila : ConcurrentLinkedQueue[(String, String)], servisirani : ConcurrentLinkedQueue[(String, String)],
					redovno : AtomicInteger, popravka : AtomicInteger, vreme : AtomicInteger) extends Thread {
		override def run(): Unit = {
			while(true) {
				val a = redAutomobila.poll()
				if(a == null) {
					return
				} else {
					if(a._2 == "redovno") {
						val vr = ThreadLocalRandom.current().nextInt(2, 6)
						Thread.sleep(vr*1000)
						servisirani.add(a)

						redovno.synchronized {
							val v = redovno.get() + 1
							redovno.set(v)
						}

						vreme.synchronized {
							val v = vreme.get() + vr
							vreme.set(v)
						}
					} else if(a._2 == "popravka") {
						val vr = ThreadLocalRandom.current().nextInt(5, 11)
						Thread.sleep(vr*1000)
						servisirani.add(a)

						popravka.synchronized {
							val v = popravka.get() + 1
							popravka.set(v)
						}

						vreme.synchronized {
							val v = vreme.get() + vr
							vreme.set(v)
						}
					}
				}
			}
		}
	}
}
