#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void afisare_harta (unsigned long long n)//functie pentru afisarea hartii
{
    unsigned long long masca = 1;
    for (int i = 63; i >= 0; i--)
        {
            if((((i+1) % 8) == 0 ) && (i != 63))
            	printf("\n");
            if(n & (masca << i))
            	printf("#");
            else printf(".");
        }
    printf("\n\n");
}

int main()
{
    unsigned long long Harta;//harta, o gandim ca o matrice (asa cum e in functia afisare)

    int Nr_piese; //numarul de piese

    scanf("%llu",&Harta);
	
    afisare_harta(Harta); //prima afisare a hartii

    scanf("%d",&Nr_piese);

    unsigned long long piesa;

    int contor = 0; //pt eliminare linii si pt verificarea posibilitatii mutarilor
 
    int mutare;

    unsigned long long masca = 1;

    int j, i, k = 6, p, q; //pentru for-uri

    unsigned long long y = 0, z = 0;//ne vor ajuta la eliminarea liniilor complete

    int s = 0; //ajuta la schimbarea piesei dupa fiecare mutare laterala

    // linie cu primii 8 biti setati:

    unsigned long long linie1 = 1 + (1 << 1 ) + (1 << 2) + (1 << 3) + (1 << 4) + (1 << 5) + (1 <<6 ) + (1 << 7); 

    float liniiComplete = 0, nr_zerouri = 0;

    unsigned long long coloana1 = 0, coloana8 = 0;

    for(i = 0; i < 8; i++)//1 pe cea mai din stanga coloana
        coloana1 = coloana1 + ((masca << 7) << (i * 8));

    for(i = 0; i < 8; i++)//1 pe cea mai din dreapta coloana
        coloana8 = coloana8 + (masca << (i * 8));

    unsigned long long Harta_beta = Harta; //harta care va fi modificata

    for(j = 0; j < Nr_piese; j++)//aici vor fi cele M linii
    {
        scanf("%llu",&piesa);
			
        for (k = 7; k >= 0; k--)//cele 8 mutari
        {
            scanf("%d",&mutare); 
                    	
			if (mutare >= 0)
            {
                for (i = 1; i <= mutare; i++)
                {	
					if (k == 0) //caz particular pentru ultima linie
					{
						if (((piesa << (8 * k)) >> s) & masca)
                            break;
						else 
                            if (((piesa << (8 * k)) >> i ) & Harta)
                                break;
							else 
							{
                                Harta_beta = Harta | (((piesa << (8 * k))) >> i); //efectuez mutarea 
                                s++; //retine nr de shiftari laterale posibile
                            }
					}			
					else
                        if (((piesa << (8 * k)) >> i) & Harta)
                            break; //verific daca mutarea va coincide cu harta
                        else
                            if (((piesa << (8 * k)) >> i) & (coloana1))
                                break; //verific daca se poate efectua
                       		else
                            {
                                Harta_beta = Harta | (((piesa << (8 * k))) >> i); //efectuez mutarea
                                s++;
                            }
                }
                piesa = piesa >> s;
                s = 0;
            }
            else
            {
                for (i = 1; i <= abs(mutare); i++)
                {	
					if (k == 7) //caz particular pentru intrarea pe harta
					{
						if ((((piesa << (8 * k)) << s) & (masca << 7) << 56))
                            break;
						else 
                            if (((piesa << (8 * k)) << i ) & Harta)
                                break;
							else 
                            {
                                Harta_beta = Harta | (((piesa << (8 * k))) << i); //efectuez mutarea 
                                s++; //retine nr de shiftari laterale posibile
                            }
					}
		            else 																								    
                        if (((piesa << (8 * k)) << i ) & Harta)
                            break; //verific daca mutarea va coincide cu harta
                        else
                            if (((piesa << (8 * k)) << i) & (coloana8)) break; //verific daca se poate efectua
                            else 
                            {
                                Harta_beta = Harta | (((piesa << (8 * k))) << i); //efectuez mutarea 
                                s++;
                            }
																												
                }
                piesa = piesa << s;
                s = 0;
            }

            // verific daca piesa poate fi mutata in jos:
			
            if (((piesa << (8 * k)) & Harta) == (unsigned long long)(0))
            {
                Harta_beta = Harta | ((piesa << (8 * k)));
                afisare_harta (Harta_beta);
				if (((piesa << (8 * (k - 1))) & Harta))
                {							
					if ((k == 7)  && ((piesa & linie1) != piesa)) 
                    {
                        afisare_harta(Harta_beta); j = Nr_piese + 1;
                        break;
                    }
					else
					{
					   for (p = 0; p <= k -1; p++)
					       scanf("%d",&mutare);
					   Harta = Harta | (piesa << (8 * k));
					   break;
				    }
				}
			}
	    	else
                if (k == 7)
                    afisare_harta(Harta);
			    else 
				{
					for (p = 0; p <= k-1; p++)
						scanf("%d",&mutare);
					break;
				}
			 
				
        }
	    
        for (p = 0; p < 8; p++)//aici elimin liniile complete:
        {
            if ((Harta_beta & ( linie1<< (8 * p))) == (linie1 << (8 * p)))
            {
                liniiComplete++;
				contor = 1;
				
                for (q = 0;q < p; q++)
                    y = y | (linie1 << (8 * q));

                for (q = 7; q > p;q --)
                {
                    z = z | (linie1 << (8 * q));
                }

                    y = y & Harta_beta;
                    z = z & Harta_beta;
                    z = z >> 8;
                    Harta_beta = z | y;
                    z = 0;
                    y = 0;
            	    Harta = Harta_beta;
					p--;
            }
			
        }
            
		Harta = Harta_beta;
		if (contor) 
		{
			afisare_harta(Harta);
			contor = 0;
		}
    }//aici se incheie for-ul "mare"

	Harta = Harta_beta;
    for (p = 0; p < 64; p++)//facem nr de zerouri
            if (((masca << p) & (Harta)) == (unsigned long long)(0)) nr_zerouri++;


    printf("GAME OVER!\n");

    printf("Score:%.2f\n",sqrt(nr_zerouri) + pow(1.25, liniiComplete));
    return 0;
}
















