package grafix;

import javax.swing.JFrame;

public class Print {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		JFrame frame=new JFrame();
		Flowchart flow=new Flowchart();
		
		frame.setBounds(0,0,1200,800);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.add(flow);
		frame.setVisible(true);
		

	}

}
