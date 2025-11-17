import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue

object Putovanje {
	def main(args: Array[String]): Unit = {
		val sc1 : Scanner = new Scanner(System.in)
		val odrediste = sc1.nextLine()
		sc1.close()

		val red : ConcurrentLinkedQueue[(String, Int, Int, Boolean)] = new ConcurrentLinkedQueue[(String, Int, Int, Boolean)]()

		// init()
		val agencije : Array[Agencija] = new Array[Agencija](3)
		agencije(0) = new Agencija("LuxuryTravel", "/home/miona/IdeaProjects/TMP/src/main/scala/LuxuryTravel.data", odrediste, red)
		agencije(1) = new Agencija("ITravel", "/home/miona/IdeaProjects/TMP/src/main/scala/ITravel.data", odrediste, red)
		agencije(2) = new Agencija("TravelLove", "/home/miona/IdeaProjects/TMP/src/main/scala/TravelLove.data", odrediste, red)

		// start()
		for(a <- agencije) {
			a.start()
		}

		// join()
		for(a <- agencije) {
			a.join()
		}

		// rez
		var najboljaPonuda : Float = Float.MaxValue
		var najboljaCena : Int = 0
		var ind : Boolean = false
		var ime : String = "-"

		println("Pristigle ponude:")
		red.forEach(x => {
			if(x._4) {
				println(x._1 + ": " + x._2 + " " + x._3)
				val ponuda : Float = x._3.toFloat / x._2
				if(ponuda < najboljaPonuda) {
					najboljaPonuda = ponuda
					najboljaCena = x._3
					ind = true
					ime = x._1
				}
			} else {
				println(x._1 + ": Nema ponude")
			}
		})

		println("\nNajpovoljnija ponuda:")
		if(ind) {
			println(ime + " " + najboljaCena)
		}
	}

	class Agencija(ime : String, fajl : String, destinacija : String, red : ConcurrentLinkedQueue[(String, Int, Int, Boolean)]) extends Thread {
		override def run(): Unit = {
			val sc : Scanner = new Scanner(new File(fajl))
			while (sc.hasNextLine) {
				val niz = sc.nextLine().split(",")
				if(niz(0).equalsIgnoreCase(destinacija)) {
					red.add(ime, niz(1).toInt, niz(2).toInt, true)
					sc.close()
					return
				}
			}
			red.add(ime, 0, 0, false)
			sc.close()
		}
	}
}
