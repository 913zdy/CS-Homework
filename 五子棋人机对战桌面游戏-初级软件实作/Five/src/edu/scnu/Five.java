package edu.scnu;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JToolBar;

public class Five extends JFrame{	
	private static final long serialVersionUID = 1L;

	private JToolBar toolbar;
	private JButton startButton,backButton,exitButton;
	private ChessBoard boardPanel;
	JLabel msg;
	JCheckBox computerFirst;
	public Five() {
		super("�������˻���ս");
		toolbar=new JToolBar();
		startButton=new JButton("��ʼ��Ϸ");
		backButton=new JButton("����");
		exitButton=new JButton("�˳�");
		boardPanel=new ChessBoard(this);
		msg=new JLabel("�µ���Ϸδ��ʼ!");
		computerFirst=new JCheckBox("�����������");
		toolbar.add(startButton);
		toolbar.add(backButton);
		toolbar.add(exitButton);
		toolbar.add(computerFirst);
		ActionMonitor monitor=new ActionMonitor();
		startButton.addActionListener(monitor);
		backButton.addActionListener(monitor);
		exitButton.addActionListener(monitor);
		this.add(toolbar, BorderLayout.NORTH);
		this.add(boardPanel,BorderLayout.CENTER);
		this.add(msg, BorderLayout.SOUTH);
		this.setLocation(350, 20);
		this.pack();
		this.setResizable(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setVisible(true);
		
	}
	class ActionMonitor implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if(e.getSource()==startButton) {
				boardPanel.restartGame();
			}
			else if(e.getSource()==backButton) {
				boardPanel.goback();
			}
			else if(e.getSource()==exitButton) {
				System.exit(0);
			}
		}
			
	}
	public static void main(String[]args) {
		new Five();
		
	}
}
