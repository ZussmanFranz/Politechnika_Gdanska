import java.util.Scanner;
public class Javalab1 {
    public static void main(String[] args)
    {
        Scanner inputScanner = new Scanner(System.in);
        System.out.println("Jak masz na imię?");
        String imie = inputScanner.nextLine();
        System.out.println("Witaj "+imie+"!");
    }
}