package socket;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server { 
	
	public static void main(String[] args) throws ClassNotFoundException {
		int numPort = 10080;
		try {
			ServerSocket serveur=new ServerSocket(numPort);
			Socket client = serveur.accept();
			
			// 获取 socket 输出流，用来向客户端发送数据
			DataOutputStream outs = new DataOutputStream(client.getOutputStream());
			// 获取 socket 输入流，用来接受客户端发过来的数据
			DataInputStream ins = new DataInputStream(client.getInputStream());
			
			boolean flag = true;
			while(flag) {
				String mesgRecu = ins.readUTF();
				
				if (mesgRecu == null || "".equals(mesgRecu)) {
					flag = false;
					System.out.println("Message VIDE.");
				}else {
					if ("desconnexion".equals(mesgRecu)) {
						flag = false;
					}
					else {
						//将客户端发来的消息加上“bien recu”，发送回给客户端
						outs.writeUTF("Bien recu:"+mesgRecu);
					}
				}
			}
			outs.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
