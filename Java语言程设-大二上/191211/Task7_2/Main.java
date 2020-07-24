import java.util.*;
import java.math.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		BigInteger res = new BigInteger("0");
		while(input.hasNext()) {
			String num = input.nextLine();
			if(num.equals("e") || num.equals("E")) {
				break;
			}
			else {
				BigInteger num_int = new BigInteger(num);
				res = res.add(num_int);
			}
		}
		System.out.println(res.toString());
		input.close();
	}
}
