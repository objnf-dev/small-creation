import java.util.*;
public class Main {
	public static class Sort implements Comparator<String> {
		@Override
		public int compare(String arg0, String arg1) {
			Integer a = new Integer(arg0.substring(6, 14));
			Integer b = new Integer(arg1.substring(6, 14));
			return a.intValue() - b.intValue();
		}
	}
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		Integer n_str = new Integer(input.nextLine());
		int n = n_str.intValue();
		String[] data = new String[n];
		for(int i=0; i<n; i++) {
			data[i] = input.nextLine();
		}
		Arrays.sort(data, new Sort());
		String[] date = new String[n];
		for(int i=0; i<n; i++) {
			date[i] = data[i].substring(6, 10) + "-" + data[i].substring(10, 12) + "-" +data[i].substring(12, 14);
		}
		while(input.hasNext()) {
			String usrinput = input.nextLine();
			if(usrinput.equals("sort1")) {
				for(int i=0; i<n; i++)
				{
					System.out.println(date[i]);
				}
			}
			else if(usrinput.equals("sort2")) {
				for(int i=0; i<n; i++)
				{
					System.out.println(data[i]);
				}
			}
			else {
				System.out.println("exit");
				return;
			}
		}
		input.close();
	}
}
