
import java.util.Scanner;

public class Algebra {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        while (n<0) {

            int[] array= new int[n];
            for(int i = 0; i < n; i++){
                array[i]= sc.nextInt();
            }
            String equacao = sc.nextLine();
            System.out.println(equacao);
            n = sc.nextInt();
        }

    }

}
