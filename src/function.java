import java.util.*;


public class function {
	
	String[] allcubes;
	String[] kernels;
	String[] cokernels;
	String[] variables;
	
	function(String[] c, String[] cokrnls, String[] krnls){
		allcubes = c;
		kernels = krnls;
		cokernels = cokrnls;
	}
	
	String[] r_kernels(String[] cubes, String[] vars){
		
		
		
		/*String[] cubescopy = cubes;
		String[] protect = new String[2];
		int track = 0;
		for(int i = 0; i < vars.length;){
			
			System.out.println("For this variable " + vars[i]);
			//for(int g = 0; g < cubescopy.length; g++)
				//System.out.println(cubescopy[g]);
			
			String[] temp = this.divide(vars[i]).ftostring();
			if(temp.length==0){
				i++;
				System.out.println("HIT");
				for(int g = 0; g < protect.length; g++)
					System.out.println(protect[g]);
			}
			else{
				System.out.println("went to else");
				if(track==0){
					System.out.println("track == 0");
					cubescopy = new String[temp.length];
					cubescopy = temp;
					protect = cubescopy;
					//for(int g = 0; g < cubescopy.length; g++)
					//	System.out.println(cubescopy[g]);
				}
				else{
					System.out.println("ended up in 2nd else");
					cubescopy = temp;
					track++;
					//for(int g = 0; g < cubescopy.length; g++)
					//	System.out.println(cubescopy[g]);
				}
				i++;
			}
			
		}
		
		

		/*for(int i = 0; i < vars.length;){		
			String[] tempcubes = cubes;
			for(int x = 0; x < (i + 1); x++){
				String[] temp = divide(tempcubes, vars[x]);
				if(temp.length==0){
					x = i + 1;
					i++;
				}
				for(int y = 0; y < temp.length; y++)
					tempcubes[y] = temp[y];
				if(x==i){
					for(int g = 0; g < tempcubes.length; g++)
						System.out.println(tempcubes[g]);
					x++;
				}
			}
		}*/
		return null;
	}

//***********R_KERNEL METHOD ENDS HERE******************//	
	
//***********DIVISION METHOD BEGINS HERE****************//
	function divide(String d){
		int track = 0;
		String[] usedcubes = allcubes;
		cokernels[0] = d;
		for(int c = 0; c < usedcubes.length; c++){		//allcubes == array of strings
			for(int ch = 0; ch < usedcubes[c].length();){
				if(d.equals(Character.toString(usedcubes[c].charAt(ch)))){		
					usedcubes[c] = usedcubes[c].replaceAll(d, "");
					ch = usedcubes[c].length();
					track++;
				}
				if(ch==(usedcubes[c].length()-1) && !d.equals(Character.toString(usedcubes[c].charAt(ch)))){
					usedcubes[c] = "";
					ch++;
					}
				else{ 
					ch++;
				}			
			}					
		}
		if(track<2){
			usedcubes = new String[0];
		}
		
		else {
			int t = 0;
			String[] temp = new String[usedcubes.length];
			
			for(int y = 0; y < usedcubes.length; y++){
				if(!usedcubes[y].equals("")){
					temp[t] = usedcubes[y];
					t++;		
				}
			}
			usedcubes = new String[t];
			for(int y = 0; y < t; y++)
				usedcubes[y] = temp[y];
		}
		for(int y = 0; y<usedcubes.length; y++)
			kernels[0] = kernels[0] + " + " + usedcubes[y];
		System.out.println(allcubes);
		function a = new function(allcubes, cokernels, kernels);
		return a;		
	}
//**********DIVISION METHOD ENDS HERE*******************//
	
	String[] ftostring(){
		return allcubes;
	}
	
	String[] fkernels(){
		return kernels;
	}
	
}
