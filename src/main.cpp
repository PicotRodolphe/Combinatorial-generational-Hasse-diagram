#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

void generate(int, int);
void list();
int unrank();
int previous();
int next();

const int puissance=4;
const int count = 2 << puissance ;



vector<vector<bitset<puissance>>> solutions (puissance+1);

void affiche () {
	for ( std::vector<bitset<puissance>> elem : solutions){
		for (bitset<puissance> e : elem)
		{
			cout << e << endl ;
		}
	}
}

template <size_t puissance>


void generate(int run, int endroit,bitset<puissance> acc){
	if (run == 0 ){
		solutions[endroit].push_back(acc);
	}
	else {

		bitset<puissance> un = acc;
		un[run-1]=1;

		generate(run-1, endroit, acc);
		generate(run-1, endroit+1, un);
	}
}

void list(){

}

int factorial(int n){
	int tmp = 1;

	for (int i = 1; i <= n; ++i)
	{
		tmp*=i;
	}

	return tmp;
}

int binomial(int n, int k){
	return factorial(n)/(factorial(k)*(factorial(n-k)));
}

int parcour(bitset<puissance> elem, int reste, int min, int max, int zero, int un){

	// cout << " elem : " << elem << endl ;
	// for (int i = 0; i < puissance; ++i)
	// {
	// 	cout << " elem [" << i << "] : " << elem[i] << endl;
	// }
	// cout << " reste : " << reste << endl ;
	// cout << " min : " << min << endl ;
	// cout << " max : " << max << endl ;
	// cout << " zero : " << zero << endl ;
	// cout << " un : " << un << endl << endl << endl ;

	// works with the lexicographical order


 	if( !zero ){
		return min; 
	}
	else {
		if (elem[reste-1]){
			// cout << " passage vrai " << endl;
			int bin = binomial(reste-1, un-1);
			return parcour(elem, reste-1, min+binomial(reste-1,un) , max , zero, un-1);
		}
		else{
			int bin = binomial(reste-1, zero-1);
			return parcour(elem, reste-1, min , max-bin , zero-1, un);
		}
				
	}
}

int ranka(bitset<puissance> elem){

	int c0 = 0 ;

	for (int i = 0; i < puissance ; i++){
		if ( elem[i] == 0) {
			c0++;
		}
	}

 	return parcour(elem, puissance, 1, binomial(puissance, puissance-c0), c0, puissance-c0);
}

int unrank(int i, int un){ 
	bitset<puissance> acc;
	int reste = puissance;
	int nbr_un = un;
	int tampon=1;

	while(reste != 0){
		int pivot = binomial(reste-1, nbr_un);
		cout << " test pivot : " << pivot << endl;
		cout << " i : " << i << endl;
		cout << " reste : " << reste << endl;
		cout << " nbr_un : " << nbr_un << endl;
		cout << " tampon : " << tampon << endl;
		if (pivot <= i )
		{
			cout << "            passage gauche " << endl;
			acc[reste]=1;
			reste--;
			nbr_un--;
			i-=pivot;
		}
		else{
			cout << "             passage droite " << endl;
			acc[reste]=0;
			reste--;
			tampon++;
		}
	}

	cout << "mot binaire " << acc << endl ;

	return (int)(acc.to_ulong());
}

int previous(){

}

int next(){
	
}

int main(int argc, char const *argv[])
{
	bitset<puissance> test = bitset<puissance> (15);
	bitset<puissance> tmp;
	// generate(puissance, 0, tmp);
	cout << ranka(test) << endl ;
	// cout << unrank(2,3) << " doit faire " << 0101 << endl;
	affiche();
	return 0;
}