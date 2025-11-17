import java.io.File
import java.util.Scanner

object BrojPetocifrenihBrojeva {
	def main(args: Array[String]): Unit = {

		// init()
		val brojaci : Array[Brojac] = new Array[Brojac](5)
		for(i <- 0 until 5) {
			brojaci(i) = new Brojac(s"/home/miona/Downloads/cas8_9/Scala/datoteke/brojevi${i+1}.txt")
		}

		// start()
		for(b <- brojaci) {
			b.start()
		}

		// join()
		for(b <- brojaci) {
			b.join()
		}

		// rez
		brojaci.foreach(x => println(x.getBroj))
	}

	class Brojac(dat : String) extends Thread {
		var brojPet: Int = 0

		def getBroj : Int = brojPet

		override def run(): Unit = {
			val sc : Scanner = new Scanner(new File(dat))
			while(sc.hasNextInt) {
				val br : Int = sc.nextInt()
				if(br >= 10000 && br <= 99999) {
					brojPet += 1
				}
			}
		}
	}
}
