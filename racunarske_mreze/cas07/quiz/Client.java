package quiz;

import java.net.InetAddress;
import java.util.Objects;

public class Client {
    private InetAddress address;
    private int port;

    Client(InetAddress address, int port) {
        this.address = address;
        this.port = port;
    }

    public InetAddress getAddress() {
        return address;
    }

    public int getPort() {
        return port;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null || this.getClass() != obj.getClass()) {
            return false;
        }
        Client client = (Client) obj;
        return this.address.equals(client.address) && this.port == client.port;
    }

    @Override
    public int hashCode() {
        return Objects.hash(address, port);
    }
}
