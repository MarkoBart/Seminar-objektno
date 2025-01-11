#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

class Maze
{
protected:
	int matrica[37][75];
	int size_x;
	int size_y;
public:
	Maze()
	{
		char tezina;
		cout << "Unesi tezinu labirinta mala 'j',srednja 'm',velika 'l' ili extreame x." << endl;
		cout << "! NAPOMENA ZA EXTREAME OBAVEZNO KONZOLU POSTAVITI NA FULLSCREEN PRIJE UNOSA !" << endl;
		cin >> tezina;
		cout << endl;
		if (tezina == 'j')
		{
			size_x = size_y= 11;
		}
		else if (tezina == 'm')
		{
			size_x = size_y = 21;
		}
		else if (tezina == 'l')
		{
			size_x = size_y = 35;
		}
		else if (tezina == 'x')
		{
			size_x = 37;
			size_y = 73;
		}
		else
		{
			cout << "Pogresan unos srednja tezina ce automatski biti izabrana" << endl;
			size_x = size_y = 21;
		}
		generiraj_okvir_Labirinta();
	}

	void generiraj_okvir_Labirinta()
	{
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				if (i == 0 || i == size_x-1 || j==0 || j==size_y-1)
				{
					matrica[i][j] = 1;
				}
				else
				{
					matrica[i][j] = 0;
				}
			}
		}
		generiraj_rešetkasti_labirint();
		dodaj_rupe();
		dodaj_rupe();
		razbij_duge_zidove();
		razbij_duge_zidove();
		matrica[0][1] = 0;
		matrica[size_x-2][size_y-1] = 0;
	}

	void generiraj_rešetkasti_labirint()
	{
		//Resetke
		for (int i = 1; i < size_x-1; i++)
		{
			for (int j = 1; j < size_y-1; j++)
			{
				if (i % 2 == 0 || j % 2 == 0)
					matrica[i][j] = 1; 
				else
					matrica[i][j] = 0;
			}
		}

		//Setanje po resetci
		if (size_y > size_x)
		{
			
			for (int i = 1; i < size_x - 1; i += 2)
			{
				for (int j = 1; j < size_y/2+1; j += 2)
				{

					
					if (rand() % 2 == 0 && j + 2 < size_y - 1)
						matrica[i][j + 1] = 0;
					else if (i + 2 < size_x - 1)
						matrica[i + 1][j] = 0;
				}
			}
			
			for (int i = 1; i < size_x - 1; i += 2)
			{
				for (int j = size_y/2+1; j < size_y-1; j += 2)
				{

					
					if (rand() % 2 == 0 && j + 2 < size_y - 1)
						matrica[i][j + 1] = 0; 
					else if (i + 2 < size_x - 1)
						matrica[i + 1][j] = 0;
				}
			}
			
		}
		else
		{
			for (int i = 1; i < size_x - 1; i += 2)
			{
				for (int j = 1; j < size_y - 1; j += 2)
				{

					
					if (rand() % 2 == 0 && j + 1 < size_y - 1)
						matrica[i][j + 1] = 0;
					else if (i + 2 < size_x - 1)
						matrica[i + 1][j] = 0;
				}
			}
		}

	
	}
	//nasumicne rupe
	void dodaj_rupe()
	{
		
		int broj_rupa = rand() % (size_x * size_y / 35);

		for (int i = 0; i < broj_rupa; i++) {
			int x = rand() % (size_x - 2) + 1;
			int y = rand() % (size_y - 2) + 1;
			if (matrica[x][y] == 1) { 
				matrica[x][y] = 0;
			}
		}
		matrica[2][2] = 0;
		matrica[3][3] = 0;
		matrica[4][2] = 0;
		matrica[2][4] = 0;
		matrica[size_x-3][size_y-3] = 0;
		matrica[size_x-4][size_y-2] = 0;
		matrica[size_x-2][size_y-4] = 0;

	}

	void razbij_duge_zidove()
	{
		for (int j = 1; j < size_y-1; j ++)
		{
			int counter = 0;
			for (int i = 1; i < size_x-1; i ++)
			{
				if (matrica[i][j] == 1)
				{
					counter++;
				}
				else
				{
					if (counter > 5)
					{
						int rupa = rand() % counter+1;
						int x = i - counter + rupa;
						matrica[x][j] = 0;
					}
					counter = 0;
				}
			}
		}
	}


	void ispisi_Labirint(int igrac_x,int igrac_y)
	{
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				if (i == igrac_x && j == igrac_y && size_y > 35)
				{
					cout << "#";
				}
				else if (i == igrac_x && j == igrac_y)
					cout << "$";
				else
				{
					cout << (matrica[i][j] == 1 ? "#" : " ") << " ";

				}
			}
			cout << endl;
		}
	}

	bool provjera(int x, int y)
	{
		return matrica[x][y] == 0;
	}

	int getSizeX()
	{
		return size_x;
	}
	int getSizeY()
	{
		return size_y;
	}

};

class Igrac
{
private:
	int x, y;
public:
	Igrac():x(0),y(1){}

	void pomak(char smjer,int korak,Maze& labirint)
	{
		for (int i = 0; i < korak; i++)
		{
			int novi_x = x, novi_y = y;
			if (smjer == 'w')
				novi_x--;
			else if (smjer == 's')
				novi_x++;
			else if (smjer == 'a')
				novi_y--;
			else if (smjer == 'd')
				novi_y++;
			if (labirint.provjera(novi_x, novi_y))
			{
				x=novi_x;
				y=novi_y;
			}
			else
			{
				cout << "Ilegalan pomak" << endl;
				break;
			}
		}
	}

	int getX()
	{
		return x;

	}
	int getY()
	{
		return y;
	}


};

class Menager
{
private:
	Maze labirint;
	Igrac Igrac1;

public:
	Menager() {}
	void pokreni_igru()
	{
		while (1)
		{
			system("cls");
			labirint.ispisi_Labirint(Igrac1.getX(), Igrac1.getY());
			cout << endl;
			cout << "Za kretanje koristite 'w' 'a' 's' 'd' i koliko polja se zelite pomaknuti->";
			cout << " primjer s3, ";
			cout << " za prekid igre izadite iz labirinta ili pritisnite q" << endl;

			if (Igrac1.getX() == labirint.getSizeX()-2 && Igrac1.getY() == labirint.getSizeY()-1)
			{
				cout << endl;
				cout << "! Igra zavrsena, izasli ste iz labirinta" << endl;
				break;
			}

			char smjer;
			int korak;
			cin >> smjer;
			if (smjer == 'q')
				break;
			cin >> korak;
			Igrac1.pomak(smjer, korak, labirint);
		}
	}

};

int main()
{
	srand(time(0));
	Menager igra;
	igra.pokreni_igru();
	return 0;
}