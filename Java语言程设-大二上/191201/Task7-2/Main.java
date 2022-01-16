import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			Integer tmp = new Integer(input.nextInt());
			if(tmp.intValue() >= 10000 && tmp.intValue() <= 20000) {
				String out_string = Integer.toBinaryString(tmp.intValue()) + "," + 
						Integer.toOctalString(tmp.intValue()) + "," + 
						Integer.toHexString(tmp.intValue());
				System.out.println(out_string);
			}
			else {
				String int_val = tmp.toString();
				int sum = 0;
				for(int i = 0; i < int_val.length(); i++) {
					if(int_val.charAt(i) >= '0' && int_val.charAt(i) <= '9') {
						System.out.print(int_val.charAt(i) + " ");
						sum += int_val.charAt(i) - '0';
					}
				}
				System.out.println(sum);
			}
		}
		input.close();
	}
}
