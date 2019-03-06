package socket;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;

import ex2.Point3D;

public class Client {
	public static void main(String[] args) {
		int numPort = 10080; 
		String host = "localhost";
		 
		try {
			Socket client=new Socket(host,numPort);
			System.out.println("==> Demande une connexion...");
			client.setSoTimeout(10000);
			
			// 获取系统输入流，用来读取系统输入数据
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			
			// 获取 socket 输出流，用来向服务端发送数据
			DataOutputStream outs = new DataOutputStream(client.getOutputStream());
			// 获取 socket 输入流， 用来接受服务端发过来的数据
			DataInputStream ins = new DataInputStream(client.getInputStream());
			
			boolean flag = true;
			while(flag) {
				System.out.println(" - Entrez vos messages: ");
				// 获取系统输入
				String mesg = input.readLine();	
				//向服务端发送获取的系统输入的数据
				outs.writeUTF(mesg);
				
				if("desconnexion".equals(mesg)) {
					flag = false;
				}
				else {
					try {
						String echo = ins.readUTF();
						System.out.println(echo);
					}catch(SocketTimeoutException e) {
						System.out.println("Time out, no response...");
					}
					
				}
			}
			input.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	

}
