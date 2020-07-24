import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int a, b;
		while(input.hasNext()) {
			a = input.nextInt();
			b = input.nextInt();
			if(Math.abs(a) > 1000) {
				System.out.println("|a|>1000");
			}
			else {
				System.out.println(a+b);
			}
		}
		input.close();
	}
}
