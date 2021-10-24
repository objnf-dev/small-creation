import java.util.Scanner;

enum Grade {
	A, B, C, D, E
}

public class Main {
	public static Grade getGrade(int score) {
		if(score >= 90 && score <= 100) {
			return Grade.A;
		}
		else if(score >= 80 && score < 90) {
			return Grade.B;
		}
		else if(score >= 70 && score < 80) {
			return Grade.C;
		}
		else if(score >= 60 && score < 70) {
			return Grade.D;
		}
		else {
			return Grade.E;
		}
	}
	public static void printGradeInfo(Grade grade){
	    System.out.println("class name=" + Grade.class);
	    System.out.println("grade value=" + grade);
	}
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		while(input.hasNext()) {
			int score = input.nextInt();
			Grade grade = getGrade(score);
			switch (grade) {
			case A:
				System.out.println("Excellent");
				break;
			case B:
				System.out.println("Good");
				break;
			case C:
				System.out.println("Average");
				break;
			case D:
				System.out.println("Fair");
				break;
			case E:
				System.out.println("Poor");
				break;
			}
			printGradeInfo(grade);
		}
		input.close();
	}
}
