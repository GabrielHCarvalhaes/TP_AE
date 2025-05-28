import java.util.Random;

public class Main {
  
    public static int array[];
    
    public static void main(String[] args) {
       
        array = gerarArray(100000);

        //Selection
        int []arraytest = array.clone();
        long tempInicio = System.nanoTime();
        int [] stats=selectionSort(arraytest);
        long tempFim = System.nanoTime();
        double duracao = (tempFim - tempInicio)/1000000.0;
        System.out.printf("Selecao - Tempo: %.6f ms | Comparações: %d | Trocas: %d\n", 
                 duracao, stats[0], stats[1]);
        
        //Insertion
        arraytest = array.clone();
        tempInicio = System.nanoTime();
        stats=insertionSort(arraytest);
        tempFim = System.nanoTime();
        duracao = (tempFim - tempInicio)/1000000.0;
        System.out.printf("Insercao - Tempo: %.6f ms | Comparações: %d | Trocas: %d\n", 
                 duracao, stats[0], stats[1]);
        
        //Bubble
        arraytest = array.clone();
        tempInicio = System.nanoTime();
        stats=bubbleSort(arraytest);
        tempFim = System.nanoTime();
        duracao = (tempFim - tempInicio)/1000000.0;
        System.out.printf("Bolha - Tempo: %.6f ms | Comparações: %d | Trocas: %d\n", 
                 duracao, stats[0], stats[1]);
        
        //Quick
        arraytest = array.clone();
        tempInicio = System.nanoTime();
        stats=quickSort(arraytest);
        tempFim = System.nanoTime();
        duracao = (tempFim - tempInicio)/1000000.0;
        System.out.printf("Quick - Tempo: %.6f ms | Comparações: %d | Trocas: %d\n", 
                 duracao, stats[0], stats[1]);
    }

    public static int[] gerarArray( int n){
        Random random = new Random();
        int []array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = random.nextInt(100000);
        }
        return array;
    }

    public static int[] selectionSort(int[] array) {
        int comparacoes = 0;
        int trocas = 0;
        int n = array.length;
        
        for(int i = 0; i < (n - 1); i++) {
            int menor = i;
            for(int j = (i+1); j < n; j++) {
                comparacoes++;
                if(array[menor] > array[j]) {
                    menor = j;
                }
            }
            if (menor != i) {
                swap(array, menor, i);
                trocas++;
            }
        }
        return new int[]{comparacoes, trocas};
    }

    public static int[] insertionSort(int[] array) {
        int comparacoes = 0;
        int trocas = 0;
        int n = array.length;
        
        for(int i = 1; i < n; i++) {
            int tmp = array[i];
            int j = i - 1;
            
            while((j >= 0) && (array[j] > tmp)) {
                comparacoes++;
                array[j+1] = array[j];
                j--;
                trocas++;
            }
            comparacoes++; // Conta a última comparação que falhou
            array[j+1] = tmp;
        }
        return new int[]{comparacoes, trocas};
    }

    public static int[] bubbleSort(int[] array) {
        int comparacoes = 0;
        int trocas = 0;
        int n = array.length;
        
        for(int i = (n-1); i > 0; i--) {
            for(int j = 0; j < i; j++) {
                comparacoes++;
                if(array[j] > array[j+1]) {
                    swap(array, j, j+1);
                    trocas++;
                }
            }
        }
        return new int[]{comparacoes, trocas};
    }

    public static int[] quickSort(int[] array) {
        int[] stats = new int[2]; // stats[0] = comparacoes, stats[1] = trocas
        quickSort(0, array.length-1, array, stats);
        return stats;
    }

    private static void quickSort(int esq, int dir, int[] array, int[] stats) {
        int i = esq, j = dir;
        int pivo = array[(esq+dir)/2];
        
        while(i <= j) {
            while(array[i] < pivo) {
                stats[0]++;
                i++;
            }
            stats[0]++; // conta a comparação que falhou
            
            while(array[j] > pivo) {
                stats[0]++;
                j--;
            }
            stats[0]++; // conta a comparação que falhou
            
            if(i <= j) {
                swap(array, i, j);
                stats[1]++;
                i++;
                j--;
            }
        }
        
        if(esq < j) {
            quickSort(esq, j, array, stats);
        }
        if(i < dir) {
            quickSort(i, dir, array, stats);
        }
    }

    public static void swap(int[] array, int a, int b) {
        int tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;
    }

}