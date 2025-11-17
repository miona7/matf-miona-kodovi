import io.netty.util.internal.ThreadLocalRandom

import java.io.File
import java.util.Scanner
import java.util.concurrent.{ConcurrentHashMap, ConcurrentLinkedDeque}

object Berba {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(new File("/home/miona/Downloads/cas8_9/Scala/datoteke/drvoredi.txt"))
		val drvoredi : ConcurrentLinkedDeque[(String, Int)] = new ConcurrentLinkedDeque[(String, Int)]()
		while(sc1.hasNextLine) {
			drvoredi.push(sc1.next(), sc1.nextInt())
		}
		println(drvoredi)

		val sc2 : Scanner = new Scanner(System.in)
		val brStudenata : Int = sc2.nextInt()

		val skladiste : ConcurrentHashMap[String, Int] = new ConcurrentHashMap[String, Int](4, 4, brStudenata)
		skladiste.put("kruske", 0)
		skladiste.put("sljive", 0)
		skladiste.put("kajsije", 0)
		skladiste.put("tresnje", 0)

		val studenti : Array[Student] = new Array[Student](brStudenata)
		for(i <- 0 until brStudenata) {
			studenti(i) = new Student(drvoredi, skladiste)
		}

		for(s <- studenti) {
			s.start()
		}

		for(s <- studenti) {
			s.join()
		}

		println(skladiste)
	}

	class Student(drvoredi : ConcurrentLinkedDeque[(String, Int)], skladiste : ConcurrentHashMap[String, Int]) extends Thread {
		override def run(): Unit = {
			while(true) {
				val d = drvoredi.poll()
				if(d == null) {
					return
				}

				Thread.sleep(ThreadLocalRandom.current().nextInt(0, 1)*1000)

				var ukupnoKg: Int = 0
				for(_ <- 0 until d._2) {
					ukupnoKg += ThreadLocalRandom.current().nextInt(30, 50)
				}

				skladiste.synchronized {
					skladiste.replace(d._1, skladiste.get(d._1) + ukupnoKg)
				}
			}
		}
	}
}
