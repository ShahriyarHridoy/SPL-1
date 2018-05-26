package grafix;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.Scanner;

import javax.swing.JPanel;

public class Flowchart extends JPanel {
	
	ArrayList<int[][]> array=new ArrayList<int[][]>();
	int height;
	public Flowchart() {
		
		
		while(true) {
			
				int[][] arr=new int[2][2];
				Scanner scr=new Scanner(System.in);
				System.out.println("Start number:");
				
				arr[0][0]=scr.nextInt();
				
				if(arr[0][0]==0) break;
				System.out.println("end number:");
				arr[0][1]=scr.nextInt();
				
				
				
				array.add(arr);
				
			
			
			
		}
		
		int[][] ar=array.get(0);
		
		 height=1000/ar[0][1];
		
		
		
	}
	
	public void paintComponent(Graphics g) {
		
		g.setColor(Color.black);
		g.fillRect(0,0,1200,1000);
		g.setColor(Color.red);
		
		for(int[][] arr:array) {
			
			arr[1][0]=arr[0][0]*height;
			arr[1][1]=arr[0][1]*height;
			
			g.fillOval(200,arr[1][0],20,20);
			g.fillOval(200,arr[1][1],20,20);
			
					
		}
		
	}
}
