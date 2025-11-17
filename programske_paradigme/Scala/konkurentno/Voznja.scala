import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue

object Voznja {
	def main(args: Array[String]): Unit = {
		val sc = new Scanner(new File("/home/miona/Downloads/voznja.txt"))
		val klijenti = new ConcurrentLinkedQueue[(String, Double)]()
		while(sc.hasNextLine) {
			klijenti.add((sc.next(), sc.nextDouble()))
		}
		sc.close()

		val sc1 = new Scanner(System.in)
		val n = sc1.nextInt()
		sc1.close()

		val taksisti = new Array[Taksista](n)
		for(i <- 0 until n) {
			taksisti(i) = new Taksista(i, klijenti)
		}

		for(t <- taksisti) {
			t.start()
		}

		for(t <- taksisti) {
			t.join()
		}
	}

	class Taksista(i : Int, klijenti : ConcurrentLinkedQueue[(String, Double)]) extends Thread {
		override def run(): Unit = {
			while(true) {
				val k = klijenti.poll()
				if(k == null) {
					return
				}
				println(s"Taksista broj $i je preuzeo klijenta ${k._1}")
				Thread.sleep((k._2*1000).toInt)
				println(s"Taksista broj $i je prevezao klijenta ${k._1}")
			}
		}
	}
}
