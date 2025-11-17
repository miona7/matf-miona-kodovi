import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.atomic.AtomicInteger
import scala.collection.mutable.ArrayBuffer

object Korisnici {
	def main(args: Array[String]): Unit = {
		val sc = new Scanner(new File("/home/miona/Downloads/korisnici.txt"))
		val korisnici = new ArrayBuffer[(String, Int)]()
		while(sc.hasNextLine) {
			korisnici.append((sc.next(), sc.nextInt()))
		}
		sc.close()
		val brKorisnika = korisnici.length
		// println(brKorisnika)

		val sc1 = new Scanner(System.in)
		val n = sc1.nextInt()
		sc1.close()

		val niti = new Array[Nit](n)
		val korak = Math.ceil(brKorisnika.toDouble / n.toDouble).toInt
//		val rez = new ConcurrentHashMap[String, (Int, Long)](2, 2, n)
//		rez.put("User", (0, 0))
//		rez.put("Admin", (0, 0))

		val brUser = new AtomicInteger(0)
		val brAdmin = new AtomicInteger(0)
		val vreme = new AtomicInteger(0)

		for(i <- 0 until n) {
			niti(i) = new Nit(i*korak, Math.min((i+1)*korak, brKorisnika), korisnici, brUser, brAdmin, vreme)
		}

		for(nit <- niti) {
			nit.start()
		}

		for(nit <- niti) {
			nit.join()
		}

		println(s"Procenat usera je ${brUser.get().toDouble*100.0 / brKorisnika.toDouble}")
		println(s"Procenat admina je ${brAdmin.get().toDouble*100.0 / brKorisnika.toDouble}")
		println(s"Prosek prijave je ${vreme.get().toDouble / brKorisnika.toDouble}")

//
//		val brUser = rez.get("User")._1.toDouble
//		println(s"Procenat usera je ${brUser / brKorisnika.toDouble}")
//
//		val brAdmin = rez.get("Admin")._1.toDouble
//		println(s"Procenat admina je ${brAdmin / brKorisnika.toDouble}")
//
//		val vrPrijave = rez.get("User")._2.toDouble + rez.get("Admin")._2.toDouble
//		println(s"Prosek prijave je ${vrPrijave / brKorisnika.toDouble}")
	}

	class Nit(poc : Int, kraj : Int, korisnici : ArrayBuffer[(String, Int)], brUser : AtomicInteger, brAdmin : AtomicInteger, vreme : AtomicInteger) extends Thread {
			  //rez : ConcurrentHashMap[String, (Int, Long)]) extends Thread {
		override def run(): Unit = {

			for(i <- poc until kraj) {
				if(korisnici(i)._1.equalsIgnoreCase("User")) {
					brUser.synchronized {
						brUser.getAndIncrement()
					}
					vreme.synchronized {
						vreme.getAndAdd(korisnici(i)._2)
					}
				} else {
					brAdmin.synchronized {
						brAdmin.getAndIncrement()
					}
					vreme.synchronized {
						vreme.getAndAdd(korisnici(i)._2)
					}
				}
			}


//			var brUser = 0
//			var vrUser = 0
//			var brAdmin = 0
//			var vrAdmin = 0
//			for(i <- poc until kraj) {
//				val k = korisnici(i)
//				if(k._1.equalsIgnoreCase("User")) {
//					brUser = brUser + 1
//					vrUser = vrUser + k._2
//				} else {
//					brAdmin = brAdmin + 1
//					vrAdmin = vrAdmin + k._2
//				}
//			}
//			rez.synchronized {
//				rez.replace("User", (rez.get("User")._1 + brUser, rez.get("User")._2 + vrUser))
//				rez.replace("Admin", (rez.get("Admin")._1 + brAdmin, rez.get("Admin")._2 + vrAdmin))
//			}
		}
	}
}
