import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			int n = input.nextInt();
			String[][] table = new String[n][];
			for(int i=0; i<n; i++) {
				table[i] = new String[i + 1];
				for(int j=0; j<=i; j++) {
					table[i][j] = (i + 1) + "*" + (j + 1) + "=" + ((i + 1) * (j + 1));
					if(i != j) {
						System.out.printf("%-7s", table[i][j]);
					}
					else {
						System.out.printf("%s", table[i][j]);
					}
				}
				System.out.printf("\n");
			}
			System.out.println(Arrays.deepToString(table));
		}
		input.close();
	}
}
