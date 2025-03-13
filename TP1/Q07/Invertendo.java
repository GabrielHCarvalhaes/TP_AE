import java.util.Scanner;

public class Invertendo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();

        while(!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')){
            linha=invertendo(linha);
            System.out.println(linha);
            linha=sc.nextLine();
        }
        sc.close();
    }

    public static String invertendo(String linha){
        char[] invertido= new char[linha.length()];
        int atras = linha.length()-1;
        for(int i = 0 ; i < linha.length(); i++, atras--){
            invertido[i]= linha.charAt(atras);
        }
        return new String(invertido);
    }
}
