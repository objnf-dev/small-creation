import java.util.*;
public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		double step = 0.0001, epsilon = 0.0001;
		while(input.hasNext()) {
			double tmp = input.nextDouble();
			if(tmp < 0) {
				System.out.println(Double.NaN);
			}
			else {
				double sqrt_root = 0.0;
				while(true) {
					double diff = tmp - Math.pow(sqrt_root, 2.0);
					if(Math.abs(diff) <= epsilon) {
						System.out.printf("%.6f\n", sqrt_root);
						break;
					}
					else if(Math.pow(sqrt_root, 2.0) >= tmp) {
						System.out.printf("%.6f\n", sqrt_root);
						break;
					}
					sqrt_root += step;
				}
			}
		}
		input.close();
	}
}
