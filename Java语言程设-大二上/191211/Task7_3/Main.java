import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		
		while(input.hasNext()) {
			int n = input.nextInt();
			int begin = input.nextInt();
			int end = input.nextInt();
			
			StringBuffer res = new StringBuffer();
			
			for(int i=0; i<n; i++) {
				res.append(i + "");
			}
			
			System.out.println(res.substring(begin, end));
		}
		input.close();
	}
}
