package devoir;

import java.io.Serializable;

public class Point2D implements Serializable{
	private double x;
	private double y;
	
	public Point2D(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double getX() {
		return x;
	}
	
	public double getY() {
		return y;
	}
	
	public void setX(double x) {
		this.x = x;
	}
	
	public void setY(double y) {
		this.y = y;
	}
	
	public String InfoPoint() {
		return "x:"+this.x+" Y:"+this.y;
	}
	
	public double calculerDistance(Point2D p) {
		double distance = 0.;
		distance = Math.sqrt(Math.pow(this.x-p.x, 2)+Math.pow(this.y-p.y, 2));
		return distance;
	}

}

