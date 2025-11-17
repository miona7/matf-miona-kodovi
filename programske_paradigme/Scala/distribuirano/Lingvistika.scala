import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap
import scala.collection.mutable.ArrayBuffer

object Lingvistika {
	def main(args: Array[String]): Unit = {
		val linije : ArrayBuffer[String] = new ArrayBuffer[String]()
		val sc1 : Scanner = new Scanner(new File("/home/miona/IdeaProjects/TMP/src/main/scala/manifest.data"))
		while(sc1.hasNextLine) {
			linije.append(sc1.nextLine())
		}
//		for (elem <- linije) {
//			println(elem)
//		}
		sc1.close()

		val sc : Scanner = new Scanner(System.in)
		val brNiti : Int = sc.nextInt()
		sc.close()

		val mapa : ConcurrentHashMap[Char, Int] = new ConcurrentHashMap[Char, Int]()
		val korak : Int = Math.ceil(linije.length / brNiti.toDouble).toInt
		val niz : Array[Brojac] = new Array[Brojac](brNiti)
		for(i <- 0 until brNiti) {
			niz(i) = new Brojac(i*korak, Math.min((i+1)*korak, linije.length), linije, mapa)
		}

		for (n <- niz) {
			n.start()
		}

		for (n <- niz) {
			n.join()
		}

		//rez
		println(mapa)
	}

	class Brojac(pocetak : Int, kraj : Int, linije : ArrayBuffer[String], mapa : ConcurrentHashMap[Char, Int]) extends Thread {
		override def run(): Unit = {
			for(i <- pocetak until kraj) {
				for(c <- linije(i)) {
					val c1 : Char = c.toLower
					if(c1 >= 'a' && c1 <= 'z') {
						mapa.synchronized {
							if(mapa.containsKey(c1)) {
								mapa.replace(c1, mapa.get(c1) + 1)
							} else {
								mapa.put(c1, 1)
							}
						}
					}
				}
			}
		}
	}
}
