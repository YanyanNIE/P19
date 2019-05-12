package devoir;

import java.io.Serializable;

public class Resto implements Serializable{
	private String nom;
	private String tel;
	private Point2D pos;
	
	public Resto(String nom, String tel, double x, double y) {
		this.nom = nom;
		this.tel = tel;
		this.pos = new Point2D(x,y);
	}
	
	public String getNom() {
		return nom;
	}
	
	public String getTel() {
		return tel;
	}
	
	public Point2D getPos() {
		return pos;
	}
	
	public void setNom(String nom) {
		this.nom = nom;
	}
	
	public void setTel(String tel) {
		this.tel = tel;
	}
	
	public void setPos(double x, double y) {
		this.pos.setX(x);
		this.pos.setY(y);
	}

	public String InfoResto() {
		return "Nom de Restaurant: "+this.nom+"\r"+
	                       " Tel: "+ this.tel+"\r"+
				           "Position: "+ this.getPos().InfoPoint();
	}

}
