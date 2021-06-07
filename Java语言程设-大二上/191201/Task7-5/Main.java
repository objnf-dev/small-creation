import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			int a = input.nextInt();
			int b = input.nextInt();
			System.out.println(a+b);
		}
		input.close();
	}
}
