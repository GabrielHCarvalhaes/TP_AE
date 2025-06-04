import java.util.Scanner;

class Celula{
    int elemento;
    Celula esq,sup,dir,inf;

    Celula(){
        this.elemento = 0;
        this.esq = null;
        this.sup = null;
        this.dir = null;
        this.inf = null;
    }

    Celula(int x){
        this.elemento = x;
        this.esq = null;
        this.sup = null;
        this.dir = null;
        this.inf = null;
    }
}

class Matriz{
    Celula inicio;
    int lin,col;

    Matriz(int l, int c, Scanner sc){
        this.lin = l;
        this.col = c;

        this.inicio = new Celula(sc.nextInt());
        Celula tmp = inicio;
        //primeira linha  completa
        for(int i = 1 ; i < c; i++){
            tmp.dir = new Celula(sc.nextInt());
            tmp.dir.esq = tmp;
            tmp = tmp.dir;
        }
        // demais linhas
        for(int i = 1; i < l; i++){
            tmp = inicio;
            while (tmp.inf !=null) {
                tmp = tmp.inf;
            }
            
            tmp.inf = new Celula(sc.nextInt());
            tmp.inf.sup= tmp;
            tmp = tmp.inf;
            for(int j = 1 ; j < c; j++){
                tmp.dir = new Celula(sc.nextInt());
                tmp.dir.esq = tmp;
                tmp.dir.sup = tmp.sup.dir;
                tmp.sup.dir.inf =tmp.dir;
                tmp = tmp.dir;
            }  
        }
    }

    public void imprimirDiagonais(){

        //principal
        Celula tmp  = inicio;
        while(tmp.inf!=null){
            System.out.printf("%d ", tmp.elemento);
            tmp= tmp.inf;
            tmp = tmp.dir;
            
        }
        System.out.printf("%d \n",tmp.elemento);
        tmp = inicio;
        for(;tmp.dir != null; tmp=tmp.dir);

        //secundária
        while(tmp.inf!=null){
            System.out.printf("%d ", tmp.elemento);
            tmp= tmp.inf;
            tmp = tmp.esq;
        }
        System.out.printf("%d \n",tmp.elemento);

    }

    public static void somaMatrizes(Matriz mat1, Matriz mat2){

        for(int l = 0 ; l < mat1.lin; l++){
            Celula tmp1=mat1.inicio, tmp2 = mat2.inicio;
            for(int i = 0;  i < l; i++){
                tmp1 = tmp1.inf;
                tmp2 = tmp2.inf;
            }
            for(int c =0 ; c < mat1.col-1; c++){
                System.out.printf("%d ",tmp1.elemento+tmp2.elemento);
                tmp1=tmp1.dir;
                tmp2 = tmp2.dir;
            }
            //ultmo elemento da linha da ultima coluna;
            System.out.printf("%d \n",tmp1.elemento+tmp2.elemento);
        }

    }

    public static void mulMatrizes(Matriz mat1, Matriz mat2){
        //faz as linhas das nova matriz
        for(int l = 0 ; l < mat1.lin; l++){
            for(int c = 0; c < mat2.col; c++){
                Celula tmp1 = mat1.inicio, tmp2=mat2.inicio;
                int resul = 0;
                for(int i = 0; i <l ;tmp1 = tmp1.inf,i++);
                for(int i = 0; i < c; tmp2 = tmp2.dir,i++);
                for(int i = 0; i < mat1.lin; i++){
                    int valor = tmp1.elemento * tmp2.elemento;
                    resul +=valor;
                    tmp1 = tmp1.dir;
                    tmp2 = tmp2.inf;
                }
                System.out.printf("%d ",resul);
            }
            System.out.printf("\n");
        }
    }
}


public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int casos = sc.nextInt();
        for(int i = 0; i < casos; i++){
            int linhas = sc.nextInt();
            int colunas = sc.nextInt();

            Matriz mat1 = new Matriz(linhas, colunas, sc);

            linhas = sc.nextInt();
            colunas = sc.nextInt();

            Matriz mat2 = new Matriz(linhas, colunas, sc);
            mat1.imprimirDiagonais();
            Matriz.somaMatrizes(mat1, mat2);
            Matriz.mulMatrizes(mat1, mat2);

        }

    }
}
