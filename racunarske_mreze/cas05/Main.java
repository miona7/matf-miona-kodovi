import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        // operacije koje mozemo da izvrsavamo nad soketom su:
        // --- klijent (radi se automatski)
        // 1. connect
        // 2. send - da pisemo u soket
        // 3. receve - da citamo iz soketa tj da primamo podatke sa mreze
        // 4. close - da zatvorimo soket tj mrezni kanal
        // --- server (radimo eksplicitno)
        // 5. bind - vezujemo soket za odgovarajuci port
        // 6. listen (blokirajuc)
        // 7. accept (blokirajuc - ceka sve dok se ne uspostavi veza sa nekim klijentom)

        // koristi se za klijentsku stranu, implemntira autoclosable pa moze u try with resources
        try (Socket s = new Socket("www.matf.bg.ac.rs", 80)) {

            InputStream in = new BufferedInputStream(s.getInputStream());
            OutputStream out = new BufferedOutputStream(s.getOutputStream());

            System.out.println(s);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // koristi se za serversku stranu

        try (ServerSocket ss = new ServerSocket(9000)) {
            while (true) {
                Socket client = ss.accept();
                serve(client);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void serve(Socket client) {
    }
}