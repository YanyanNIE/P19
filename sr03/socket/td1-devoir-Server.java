package devoir;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;

public class Server { 
	// nomber de file ligne 
	public static int getLineNumber(String filename) throws IOException {
		FileReader fileReader = new FileReader(filename);
        LineNumberReader reader = new LineNumberReader(fileReader);
        int cnt = 0;  
        String lineRead = "";  
        while ((lineRead = reader.readLine()) != null) {}  
        cnt = reader.getLineNumber();  
        reader.close(); 
        return cnt;
	}
	
	public static Resto[] sortResto(Resto[] resto, Point2D clientPos) {
		int taille = resto.length;
		for (int i = 0; i < taille; i++) {
			for (int j = i+1; j < taille; j++) {
				double disi = clientPos.calculerDistance(resto[i].getPos());
				double disj = clientPos.calculerDistance(resto[j].getPos());
				if (disi > disj) { 
					Resto temps = resto[j];
					resto[j] = resto[i];
					resto[i] = temps;
				}
			}			
		}
		return resto; 
	}
    
	public static void main(String[] args) throws ClassNotFoundException, IOException {
		//Initialisation Restaurants
		String filename = "/Users/yanyan/eclipse-workspace/TD1/src/devoir/infoResto";
		FileReader fileReader = new FileReader(filename);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        int taille = getLineNumber(filename); 
        System.out.println("File taille(Nombre de restaurants):"+taille );
        Resto[] resto = new Resto[taille];
        
        String line = null;
        int i = 0;
        while ((line = bufferedReader.readLine()) != null) {
        	String[] sp = line.split(";");
        	String[] spPos = sp[2].split(",");
    		resto[i] = new Resto (sp[0],sp[1],Double.valueOf(spPos[0]), Double.valueOf(spPos[1]));
        	i++;
        }
        bufferedReader.close();
        
        
        //Tester l'initialisation resto
		for(int t=0; t<taille;t++ ) {
	  	    System.out.println("---Resto NO."+(t+1)+"--->");
		    System.out.println(resto[t].getNom());
		    System.out.println(resto[t].getTel());
		    System.out.println(resto[t].getPos().InfoPoint());
		}
		
		//Instancier un socket
		int numPort = 10080;
		try {
			ServerSocket serveur=new ServerSocket(numPort);
			Socket client = serveur.accept();
			
			ObjectOutputStream outs = new ObjectOutputStream(client.getOutputStream());
			ObjectInputStream ins = new ObjectInputStream(client.getInputStream());
			
			Object obj = ins.readObject();
			if (obj != null) {
				Point2D clientPos = (Point2D)obj;
				System.out.println( "\r<===Postion recu<==="+clientPos.InfoPoint());
				
				//Calculer distance minimum 
				System.out.println("\r++++++++Calculer distance minimum +++++");
			    double minDis = clientPos.calculerDistance(resto[0].getPos());
			    Resto minResto = resto[0];
			    System.out.println("--->:"+resto[0].getNom());
			    System.out.println("dis:"+minDis);
			    
			    for(int t=1; t<taille; t++ ) {
				    double dis = clientPos.calculerDistance(resto[t].getPos());
				    System.out.println("--->:"+resto[t].getNom());
				    System.out.println("dis:"+dis);
				    if (dis < minDis) {
				    	minDis = dis;
				    	minResto = resto[t];
				    }
				    
				}
			    outs.writeObject(minResto);
			    System.out.println("\r===>Resto envoye.===>");
			    
			   // Calculer 3 restos proche
			    System.out.println("++++++++Calculer 3 restos proche+++++++");
		    	Resto[] restoSort = sortResto(resto, clientPos);
		    	for(int t=0; t<taille;t++ ) {
			  	    System.out.println("---Resto NO."+(t+1)+"--->");
				    System.out.println(resto[t].getNom());
				    System.out.println("dis: "+clientPos.calculerDistance(resto[t].getPos()));
				}
		    	
		    	for(int t=0; t<3; t++ ) {
		    		outs.writeObject(restoSort[t]);
		    		System.out.println("===>Resto envoye:"+t);
		    	}
		    	
		    }
		
			outs.close();
			
		}catch (IOException e) {
				e.printStackTrace();
			}
	}
	
}

