import java.util.Scanner

object Restoran {
	def main(args: Array[String]): Unit = {
		val sc : Scanner = new Scanner(System.in)

		val brNeusluzenihStolova: Int = sc.nextInt()
		val korak = Math.ceil(brNeusluzenihStolova / 5.0).toInt

		// init() konobari
		val ognjen : Konobar = new Konobar("Ognjen", korak)
		val zika : Konobar = new Konobar("Zika", korak)
		val pera : Konobar = new Konobar("Pera", korak)
		val mika : Konobar = new Konobar("Mika", korak)
		val laza : Konobar = new Konobar("Laza", brNeusluzenihStolova - 4*korak)

		// start()
		ognjen.start()
		zika.start()
		pera.start()
		mika.start()
		laza.start()

		// join()
		ognjen.join()
		zika.join()
		pera.join()
		mika.join()
		laza.join()

		// rezultat

	}

	class Konobar(ime : String, brStolova : Int) extends Thread {
		override def run(): Unit = {
			for(i <- 0 until brStolova) {
				Thread.sleep(1000)
				println(s"Konobar ${ime} je usluzio sto ${i}")
			}
			println(s"Konobar ${ime} je zavrsio za posluzivanjem")
		}
	}
}
