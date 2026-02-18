package jan2_2025.zadatak3;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Server {
    public static final int PORT = 5555;
    public static final int BUFF_SIZE = 1024;

    private static final List<Grocerie> groceries = new ArrayList<>();
    private static Map<String, List<Grocerie>> clients = new HashMap<>();

    public static void main(String[] args) {
        loadGroceries();

        try (DatagramSocket socket = new DatagramSocket(PORT)) {

            while (true) {
                byte[] buffer = new byte[BUFF_SIZE]; // za primanje zahteva od klijenta
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                socket.receive(request);

                String requestString = (new String(request.getData(), 0, request.getLength(), StandardCharsets.UTF_8)).trim();
                String[] tmp = requestString.split(" ");

                byte[] bufferResponse; // za slanje odgovora klijentu
                DatagramPacket response;

                if (tmp.length == 1) {
                    // primili smo samo ime
                    if (clients.containsKey(tmp[0])) {
                        String responseString = "Client already exists!\n";
                        bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                        response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    } else {
                        clients.put(tmp[0], new ArrayList<>());
                        StringBuilder responseStringB = new StringBuilder("Welcome " + tmp[0] + "!\nAvailable groceries:\n");
                        for (Grocerie grocerie : groceries) {
                            responseStringB.append(grocerie.toString());
                        }
                        String responseString = responseStringB.toString();
                        bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                        response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    }
                } else if (tmp.length == 2) {
                    // view ili pay
                    if (!clients.containsKey(tmp[0])) {
                        String responseString = "Client does not exist!\n";
                        bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                        response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    } else {
                        if (tmp[1].equals("VIEW")) {
                            StringBuilder responseStringB = new StringBuilder("Cart: [");

                            double totalPrice = 0.0;
                            List<Grocerie> groceriesClient = clients.get(tmp[0]);

                            for (int i = 0; i < groceriesClient.size(); i++) {
                                totalPrice += groceriesClient.get(i).getPrice();
                                responseStringB.append(groceriesClient.get(i).getName());
                                if  (i != groceriesClient.size() - 1) {
                                    responseStringB.append(", ");
                                }
                            }
                            responseStringB.append("] Total: ");
                            responseStringB.append(totalPrice);
                            responseStringB.append("$\n");

                            String responseString = responseStringB.toString();
                            bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                            response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                            socket.send(response);
                        } else if (tmp[1].equals("PAY")) {

                            double totalPrice = 0.0;
                            List<Grocerie> groceriesClient = clients.get(tmp[0]);

                            for (int i = 0; i < groceriesClient.size(); i++) {
                                totalPrice += groceriesClient.get(i).getPrice();
                            }

                            clients.get(tmp[0]).clear();
                            clients.remove(tmp[0]);

                            String responseString = "Total: " + totalPrice + "$\n";
                            bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                            response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                            socket.send(response);
                        } else {
                            String responseString = "Wrong command!\n";
                            bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                            response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                            socket.send(response);
                        }
                    }
                } else if (tmp.length == 3) {
                    // add ili remove
                    if (!clients.containsKey(tmp[0])) {
                        String responseString = "Client does not exist!\n";
                        bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                        response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                        socket.send(response);
                    } else {
                        if (tmp[1].equals("ADD")) {
                            boolean contains = false;
                            double price = 0.0;
                            for (Grocerie grocerie : groceries) {
                                if (grocerie.getName().equals(tmp[2])) {
                                    contains = true;
                                    price = grocerie.getPrice();
                                    break;
                                }
                            }
                            if (!contains) {
                                String responseString = "Grocerie does not exist!\n";
                                bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                                response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                                socket.send(response);
                            } else {
                                clients.get(tmp[0]).add(new Grocerie(tmp[2], price));
                                String responseString = "Added to cart: " +  tmp[2] + " \n";
                                bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                                response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                                socket.send(response);
                            }
                        } else if (tmp[1].equals("REMOVE")) {
                            boolean contains = false;
                            for (Grocerie grocerie : clients.get(tmp[0])) {
                                if (grocerie.getName().equals(tmp[2])) {
                                    contains = true;
                                    clients.get(tmp[0]).remove(grocerie);
                                    break;
                                }
                            }
                            if (!contains) {
                                String responseString = "Grocerie does not exist!\n";
                                bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                                response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                                socket.send(response);
                            } else {
                                String responseString = "Removed from cart: " +  tmp[2] + " \n";
                                bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                                response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                                socket.send(response);
                            }
                        } else {
                            String responseString = "Wrong command!\n";
                            bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                            response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                            socket.send(response);
                        }
                    }
                } else {
                    String responseString = "Wrong command!\n";
                    bufferResponse = responseString.getBytes(StandardCharsets.UTF_8);
                    response = new DatagramPacket(bufferResponse, bufferResponse.length, request.getAddress(), request.getPort());
                    socket.send(response);
                }
            }
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void loadGroceries() {
        groceries.add(new Grocerie("bread", 1));
        groceries.add(new Grocerie("milk", 1.5));
        groceries.add(new Grocerie("apple", 0.7));
        groceries.add(new Grocerie("eggs", 2));
    }
}
