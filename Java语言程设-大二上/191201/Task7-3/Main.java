import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			String tmp = input.nextLine();
			int sum = 0;
			for(int i = 0; i < tmp.length(); i++) {
				if(tmp.charAt(i) >= '0' && tmp.charAt(i) <= '9') {
					sum += tmp.charAt(i) - '0';
				}
			}
			System.out.println(sum);
		}
		input.close();
	}
}
