import java.util.Scanner;

public class ContaP {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();

        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            
            contandoP(linha);
            linha = sc.nextLine();
        }

    }

    public static void contandoP(String linha){
        int qtdPalavras=1;

        for(int i = 0; i < linha.length(); i++){
            if(linha.charAt(i) ==' '){
                qtdPalavras++;
            }
        }

        System.out.println(qtdPalavras);

    }

}
