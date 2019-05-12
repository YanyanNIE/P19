package devoir;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class Client {
	public static void main(String[] args) throws ClassNotFoundException {
		int numPort = 10080; 
		String host = "localhost";
		 
		try {
			Socket client=new Socket(host,numPort);
			System.out.println("==> Demande une connexion...");
			
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			ObjectOutputStream outs = new ObjectOutputStream(client.getOutputStream());
			ObjectInputStream ins = new ObjectInputStream(client.getInputStream());
			
			System.out.println(" - Entrez le position x: ");
			String px = input.readLine();
			System.out.println(" - Entrez le position y: ");
			String py = input.readLine();	
			Point2D pos = new Point2D(Double.valueOf(px),Double.valueOf(py));
			outs.writeObject(pos);
			
			// un seul restaurants
			Object obj = ins.readObject();
			System.out.println("==>Resto recu.");
			if (obj != null) {
				Resto minResto = (Resto)obj;
				System.out.println(minResto.InfoResto());
			}
			
			// 3 proches restaurants
			for (int i=0; i<3; i++) {
				Object objp = ins.readObject();
				System.out.println("==>Resto recu:"+i);
				if (obj != null) {
					Resto minResto = (Resto)objp;
					System.out.println(minResto.InfoResto());
				}
			}
			ins.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	

}

