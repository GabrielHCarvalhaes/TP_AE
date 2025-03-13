import java.util.Scanner;
import java.io.UnsupportedEncodingException;
import java.io.PrintStream;

public class Anagrama {
    
    public static void main(String[] args) throws UnsupportedEncodingException {
        // Configura o System.out para usar UTF-8
        System.setOut(new PrintStream(System.out,true, "UTF-8"));
        
        Scanner sc = new Scanner(System.in, "UTF-8");
        String linha = sc.nextLine();
        
        // Entra em um loop que continua até que a linha de entrada seja "FIM"
        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            // Converte a linha para letras minúsculas para facilitar a comparação
            linha = linha.toLowerCase();
            String[] palavras = new String[2];
            
            // Chama a função separando para dividir a linha em duas palavras
            separando(linha, palavras);
            String palavra1 = palavras[0], palavra2 = palavras[1];

            // Chama a função analisando para verificar se as palavras são anagramas
            boolean ehAnagrama=analisando(palavra1, palavra2);
            if (ehAnagrama) {
                MyIO.println("SIM");
            } else {
                MyIO.println("NÃO");
            }
            linha = sc.nextLine();
        }

        sc.close();
    }
    
    // Função que separa a linha em duas palavras, divididas pelo caractere '-'
    public static void separando(String linha, String[] palavras) {
        int posicao = 0;
        
        // Encontra a posição do caractere '-' na linha
        while (linha.charAt(posicao) != '-') {
            ++posicao;
        }

        // Cria arrays de caracteres para armazenar as duas palavras
        char[] um = new char[posicao - 1], dois = new char[linha.length() - (posicao+2)];

        // Lê a primeira palavra (antes do '-')
        for (int i = 0; i < posicao - 1; i++) {
            um[i] = linha.charAt(i);
        }

        // Lê a segunda palavra (depois do '-')
        int i = 0;
        for (int j = posicao + 2; j < linha.length(); j++, i++) {
            dois[i] = linha.charAt(j);
        }
        // Converte os arrays de caracteres em strings e armazena no array palavras
        palavras[0] = new String(um);
        palavras[1] = new String(dois);
    }
    
    // Função que verifica se as duas palavras são anagramas
    public static boolean analisando(String p1, String p2) {
        
        boolean letraigual = false, ehAnagrama = false, p2EhAngrama = true, p1EhAngrama = true;

        // Verifica se todas as letras da segunda palavra estão na primeira palavra
        for (int i = 0; i < p2.length(); i++) {
            
            for (int j = 0; j < p1.length(); j++) {
                if (p2.charAt(i) == p1.charAt(j)) {
                    letraigual = true; 
                    j = p1.length(); 
                }
            }

            // Se uma letra da segunda palavra não for encontrada na primeira, não é anagrama
            if (!letraigual) {
                i = p2.length(); 
                p2EhAngrama = false; 
            }
            letraigual = false; 
        }

        // Verifica se todas as letras da primeira palavra estão na segunda palavra
        for (int i = 0; i < p1.length(); i++) {
            
            for (int j = 0; j < p2.length(); j++) {
                if (p1.charAt(i) == p2.charAt(j)) {
                    letraigual = true; 
                    j = p2.length(); 
                }
            }

            // Se uma letra da primeira palavra não for encontrada na segunda, não é anagrama
            if (!letraigual) {
                i = p1.length(); 
                p1EhAngrama = false; 
            }

            letraigual = false; 
        }

        // Se ambas as palavras forem anagramas uma da outra, marca como verdadeiro
        if (p1EhAngrama && p2EhAngrama) {
            ehAnagrama = true;
        }

        return ehAnagrama;
    }
}