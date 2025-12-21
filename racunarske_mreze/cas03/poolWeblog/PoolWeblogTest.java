package poolWeblog;

import java.io.*;

public class PoolWeblogTest {
    public static void main(String[] args) {
        try {
            BufferedReader br = new BufferedReader(new FileReader("/home/miona/IdeaProjects/cas3/src/poolWeblog/apache.logfile"));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
            PoolWeblog poolWeblog = new PoolWeblog(br, bw, 10);
            poolWeblog.processLog();
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
