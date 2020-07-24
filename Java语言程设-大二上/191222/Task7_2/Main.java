import java.util.*;
class Person {
	private String name;
	private int age;
	private boolean gender;
	private int id;
	private static int num;
	
	static {
		System.out.println("This is static initialization block");
	}
	
	{
		this.id = num;
		num += 1;
		System.out.println("This is initialization block, id is " + (num - 1));
	}
	
	public Person() {
		System.out.println("This is constructor");
		System.out.println(name + "," + age + "," + gender + "," + id);
	}
	
	public Person(String name, int age, boolean gender) {
		this.name = name;
		this.age = age;
		this.gender = gender;
	}

	@Override
	public String toString() {
		return "Person [name=" + name + ", age=" + age + ", gender=" + gender + ", id=" + id + "]";
	}
}

public class Main {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		Person[] data = new Person[n];
		
		for(int i=0; i<n; i++) {
			Person tmp = new Person(input.next(), input.nextInt(), input.nextBoolean());
			data[i] = tmp;
		}
		
		for(int i=n-1; i>=0; i--) {
			System.out.println(data[i].toString());
		}
		
		Person empty = new Person();
		System.out.println(empty.toString());
		input.close();
	}
}
