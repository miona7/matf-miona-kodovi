import java.io.*;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        // InputStream, OutputStream
        InputStream in;
        OutputStream out;

        // za rad sa fajlovima, ima podrazumevano ponasanje
        FileInputStream fis;
        // zatvaranje resursa, kroz try catch finaly, sami ili ako implementira AutoClosable
        FileOutputStream fos;

        // mozemo da baferisemo oko fajl input strima, i da ih koristimo zajedno
        BufferedInputStream bis;
        // BufferedInputStream bis = new BufferedInputStream(new FileInputStream())

        BufferedReader br;
        BufferedWriter bw;
        PrintWriter pw; // radi automatsko flasovanje

        // flaserovanje iz bafera, izbacimo sve, da ne bi ostalo i nestalo, neki rade automatski, negde rucno
    }
}