import java.util.ArrayList;
import java.util.Scanner;
import ja

public class Substring {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();
        
        // Entra em um loop que continua até que a linha de entrada seja "FIM"
        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            
            int comprimentoMAX = comprimentoMax(linha);
        
            System.out.println(comprimentoMAX);

            linha = sc.nextLine();
        }

        sc.close();
    }

    // Função que calcula o comprimento da maior substring sem caracteres repetidos
    public static int comprimentoMax(String linha) {

        int comprimentoMax = 0;
        ArrayList<Character> lista = new ArrayList<>();

        for (int i = 0; i < linha.length(); i++) {

            char caractereAtual = linha.charAt(i);

            // Verifica se o caractere atual já está na lista
            if (lista.contains(linha.charAt(i))) {
                // Remove todos os caracteres anteriores até a primeira ocorrência do caractere repetido
                int indiceRepetido = lista.indexOf(linha.charAt(i));
                for (int j = 0; j <= indiceRepetido; j++) {
                    lista.remove(0);
                }
            }

            // Adiciona o caractere atual à lista
            lista.add(caractereAtual);

            // Atualiza o comprimento máximo se o tamanho da lista atual for maior
            if (comprimentoMax < lista.size()) {
                comprimentoMax = lista.size();
            }
        }

        return comprimentoMax;
    }
}