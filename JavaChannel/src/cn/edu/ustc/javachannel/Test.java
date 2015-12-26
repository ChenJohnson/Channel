package cn.edu.ustc.javachannel;

import java.io.BufferedWriter;
//import java.io.File;
//import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
//import java.io.UnsupportedEncodingException;
import java.io.Writer;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ChannelList<String> intList = new ChannelList<String>(10, "0");
		//intList.setList(0);
		
		new Thread(){
			public void run(){
				//System.out.println("entering 1...");
				int i = 0;
				try{
					while(i < 100){					
						intList.writeElem("a");
						i++;
						//System.out.println(i);
					}
				}catch(InterruptedException e){
					System.out.println(e.getMessage());
				}
				
			}
		}.start();
		
		new Thread(){
			public void run(){
				int i = 0;
				try{
					while(i < 100){					
						intList.writeElem("b");
						i++;
						//System.out.println(i);
					}
				}catch(InterruptedException e){
					System.out.println(e.getMessage());
				}
				
			}
		}.start();
		
		new Thread(){
			
			public void run(){
				try{
					int i = 0;
					Writer writer = new BufferedWriter(new OutputStreamWriter(
				              new FileOutputStream("./result.log"), "utf-8"));
				
					while(i < 200){					
						String ret = intList.readElem();
						System.out.println(ret);
						i++;
						writer.write(ret);
						writer.write("\r\n");
					}
					writer.close();
				}catch(InterruptedException e){
					System.out.println(e.getMessage());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}				
			}
		}.start();
	}

}
