import java.io.*;
import java.util.*;
class fileRead{
	public static void main(String args[]) throws IOException{
		FileReader in = null;
		FileReader ins = null;
		FileWriter out = null;
		try{
			in = new FileReader("dictionary.txt");
			out = new FileWriter("output.txt");
			int c,j,m = 0;
			String z = null;
			while((c = in.read()) != -1){
				if((char)c != '\0'){
					if((char)c!='|' && m == 0){
						if(((char)c>='a' && (char)c<='z') || ((char)c>='A' && (char)c<='Z')){
							//out.write((char)c);
							System.out.print((char)c);
						}
					}
					else{
						System.out.println("buffHello");
						z += (char)c;
						m = 1;
					}
				}
				else{
					System.out.println("Hello");
					System.out.println(z);
					int temp = Integer.parseInt(z);
					ins = new FileReader("sentiment_labels.txt");//File with sentiment_values
					String id = null;
					while((j = ins.read())!=-1 && (char)j!='|'){
						id+=(char)j;
					}
						int temp2 = Integer.parseInt(z);
						if(temp==temp2){
							BufferedReader bufferedReader = new BufferedReader(ins);
							String line;
							int idx;
							while((line = bufferedReader.readLine()) != null){
								if((idx = line.indexOf("|")) != -1){
									String t = line.substring(idx);
									out.write(t);
								}
							}
						}
					z=null;
					m = 0;
				}
			}
		}
		catch(IOException e){
			e.printStackTrace();
		}
		finally{
			/*if(in!=null){
				in.close();
			}
			if(out!=null){
				out.close();
			}*/
		}
	}
}