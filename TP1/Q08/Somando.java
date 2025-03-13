
import java.util.Scanner;

public class Somando {
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();

        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            fazerSoma(linha,0);
            linha=sc.nextLine();
        }

    }

    public static void fazerSoma(String linha, int i ){
        int result = 0; 
        result += soma(linha, i, result);
        System.out.println(result);
    }

    public static int soma(String linha, int i, int result){
        if( i < linha.length()){
            int valorAtual = linha.charAt(i) - '0';
            result = soma(linha,  i+1, result) + valorAtual;
        }

        return result;
    }
}

