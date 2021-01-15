/*
 * miniprojekt.c
 *	Labyrinth
 *  Author: Cyrano Fischer
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define OBEN 72
#define UNTEN 80
#define LINKS 75
#define RECHTS 77

	const char geradeV = 186;			//  ║
	const char geradeH = 205;			//  ═
	const char vertikalUndHorizontal = 206; 		//	╬
	const char vertikalMitLinks = 185;				//  	╣
	const char vertikalMitRechts = 204;				//	╠
	const char horizontalMitOben = 202;				//		╩
	const char horizontalMitUnten = 203;			//	╦
	const char eckeObenR = 187;						//		╗
	const char eckeUntenR = 188;					//	╝
	const char eckeUntenL = 200;					//		╚
	const char eckeObenL = 201;						//	╔
	const char ende = 33;		//		!
	const char player = 207;	//	¤

	char initialisierung(int *pi, int *pk, int x[20][20], int *pwieder, int *pwiederNeu, int *pgewinn, int *pcounter, int *pfalscheEingabe);

	void bewegung(int px[20][20], int *pi, int *pk,  int *pcounter, int *pgewinn,
			int *pfalscheRichtung, int *pfalscheEingabe, int *pwieder, int *pwiederNeu );					//Bewegung Prototyp

	void karteZeigen(int x[20][20], int *pcounter, int *pmaxSchritt, int *pfalscheEingabe, int *pfalscheRichtung);					//Karte Anzeigen Prototyp

	void karteEins(int *pi, int *pk, int x[20][20], int *pmaxSchritt);					//karte 1 Prototyp

	void karteTest(int *pi, int *pk, int x[20][20], int *pmaxSchritt);                  //Karte Test Prototyp

	void karteZwei(int *pi, int *pk, int x[20][20], int *pmaxSchritt);					//karte 2 Prototyp

	void karteDrei(int *pi, int *pk, int x[20][20], int *pmaxSchritt);					//karte 3 Prototyp

	void winLose(int *pi, int *pk, int x[20][20], int *pwieder, int *pwiederNeu, int *pgewinn, int *pcounter, int *pfalscheEingabe,int *pmaxSchritt);						//winLose Prototyp

int main()
{
	int wieder, wiederNeu, i, k, gewinn,counter,falscheRichtung, falscheEingabe,x[20][20], maxSchritt;			//wieder spielenX2,  i = spalte, k = zeile, gewinn, coordinaten, maximal Schrittenanzahl
	char auswahl;
    do{

       	auswahl = initialisierung(&i, &k, x, &wieder, &wiederNeu, &gewinn, &counter, &falscheEingabe);	//LvL vorbereitung und auswahl

		switch(auswahl)								//LvL auswaehlen
		{
		case 49: karteEins(&i, &k, x, &maxSchritt); break;		//LvL 1
		case 50: karteZwei(&i, &k, x, &maxSchritt); break;		//LvL 2
		case 51: karteDrei(&i, &k, x, &maxSchritt); break;		//LvL 3
        case 52: karteTest(&i, &k, x, &maxSchritt); break;		//Testkarte
		default: return 0; break;							//Beenden
        
		}

		do {

			karteZeigen(x, &counter, &maxSchritt, &falscheEingabe, &falscheRichtung);				//Kartezeiger funktion

			bewegung(x,&i, &k, &counter, &gewinn, &falscheRichtung, &falscheEingabe, &wieder, &wiederNeu);		//Bewegung funktion

			winLose(&i, &k, x, &wieder, &wiederNeu, &gewinn, &counter, &falscheEingabe, &maxSchritt);			//Testen ob man gewonnen oder verloren hat

		} while (wieder == 0);
	} while(wiederNeu == 1);

	return 0;
}

void karteZeigen(int x[20][20], int *pcounter, int *pmaxSchritt, int *pfalscheEingabe, int *pfalscheRichtung){
	system("cls");									//clear
	int n,m;

	printf( "Schrittanzahl = %d/%d\n",*pcounter, *pmaxSchritt);							//Schrittzaehler

						for(n = 0; n < 20; n++){							//karte anzeigen
							for (m = 0; m < 20; m++)
								printf("%c",x[m][n]);
						printf("\n");
						}

	if (*pfalscheRichtung == 1)							//wenn man in die falsche Richtung gibt, sagt er "Richtung geht nicht!"
		printf("Richtung geht nicht!\n");
	else
		printf("\n");

	if (*pfalscheEingabe == 1)							//wenn man in die falsche Eingabe gibt, sagt er "Falsche eingabe!"
		printf("Falsche eingabe!\n");
	else
		printf("\n");									//damit es nicht kommisch wird wenn eine falsche Richtung oder Eingabe gibt

	*pfalscheEingabe = 0;
	*pfalscheRichtung = 0;				//reset

	printf("\n Um zu beenden, 9 drueken:\n \n Um in menu zu gehen, 8 eingeben\n");

}

void bewegung(int px[20][20], int *pi, int *pk,  int *pcounter, int *pgewinn,
		int *pfalscheRichtung, int *pfalscheEingabe, int *pwieder, int *pwiederNeu ){
	int tempk, tempi;
	int a, wahl;			//wahl der Richtung
	wahl = 0;

	a = getch();		//taste gedrueckt oder beenden/menu
	if (a == 57)
		*pwieder = 1;		// beenden
	else if (a == 56){
		 *pwieder = 1; *pwiederNeu = 1;}
	else if (a == 224){

		wahl = getch();		//richtung lesen

	switch(wahl){

		case OBEN: 								//nach Oben
			tempk = *pk - 1;					//vorübergehend k um zu testen
			if (px[*pi][tempk]== 0){			//ueberpruefen ob oden frei ist
				px[*pi][tempk] = player;		//spieler neue position
				px[*pi][*pk] = 0;				//alte position loeschen
				--*pk;					// k aendern fuer weitere bewegungen
				++*pcounter;
				}
			else						//falls oben nicht frei ist
				if (px[*pi][tempk] == 33)		//falls ende position
					*pgewinn = 1;				//spieler hat gewonnen
				else
					*pfalscheRichtung = 1;	//es ist eine wand!!

			break;

		case RECHTS:								//nach Rechts
			tempi = *pi + 1;
			if(px[tempi][*pk] == 0){
				px[tempi][*pk] = player;
				px[*pi][*pk] = 0;
				++*pi;
				++*pcounter;
			}
			else
				if (px[tempi][*pk] == 33)
					*pgewinn = 1;
				else
					*pfalscheRichtung = 1;
			break;

		case LINKS:								//nach Links
			tempi = *pi - 1;
			if (px[tempi][*pk] == 0){
				px[tempi][*pk] = player;
				px[*pi][*pk] = 0;
				--*pi;
				++*pcounter;
			}
			else
				if (px[tempi][*pk] == 33)
					*pgewinn = 1;
				else
					*pfalscheRichtung = 1;
			break;

		case UNTEN:					//nach unten
			tempk = *pk + 1;
			if (px[*pi][tempk] == 0){
				px[*pi][tempk] = player;
				px[*pi][*pk] = 0;
				++*pk;
				*pcounter+=1;
			}
			else
				if (px[*pi][tempk] == 33){
						*pgewinn = 1;
						*pcounter +=1;
				}
				else
							*pfalscheRichtung = 1;
			break;

		default:*pfalscheEingabe = 1;break;
		}

	}
	else
		*pfalscheEingabe = 1;
}

void karteTest(int *pi, int *pk, int x[20][20], int *pmaxSchritt){                    //Karte Test

	//---------------------Startposotion-----------------------//

	            *pi = 4;           //X-Achse//
	            *pk = 4;           //Y-Achse//

	//---------------------Umrandung---------------------------//

	            x[0][0] = eckeObenL;                                    //	    ╔
	            x[14][0] = eckeObenR;                                   //	╗
	            x[0][14] = eckeUntenL;                                  //	    ╚
	            x[14][14] = eckeUntenR;                                 //	╝

	            x[1][0]=x[2][0]=x[3][0]=x[4][0]=x[5][0]=x[6][0]=
	            x[7][0]=x[8][0]=x[9][0]=x[10][0]=x[12][0]=x[13][0]=
	            x[1][14]=x[2][14]=x[3][14]=x[4][14]=x[5][14]=x[7][14]=
	            x[8][14]=x[9][14]=x[10][14]=x[11][14]=x[12][14]=
	            x[13][14]=x[6][14]=x[11][0] = geradeH;	        //  ═

	            x[0][1]=x[0][3]=x[0][4]=x[0][5]=x[0][7]=x[0][8]=
	            x[0][9]=x[0][10]=x[0][11]=x[0][12]=x[0][13]=
	            x[14][1]=x[14][4]=x[14][5]=x[14][6]=x[14][7]=
	            x[14][8]=x[14][9]=x[14][10]=x[14][11]=x[14][12]=
	            x[14][13]=x[0][2]=x[0][6]=x[14][2]=x[14][3] =
	            geradeV;		                                        //  ║

	            x[1][1] = ende;			                                //		!

				x[*pi][*pk] = player;

				*pmaxSchritt = 600;
	        }

void karteEins(int *pi, int *pk, int x[20][20], int *pmaxSchritt){					//karte 1

	//---------------------Startposition-----------------------//

				*pi = 8;          //X-Achse//
				*pk = 1;          //Y-Achse//

	//---------------------Umrandung---------------------------//

	            x[0][0] = eckeObenL;                                    //	    ╔
	            x[9][0] = eckeObenR;                                    //	╗
	            x[0][9] = eckeUntenL;                                   //	    ╚
	            x[9][9] = eckeUntenR;                                   //	╝
	            x[0][4]=vertikalMitRechts;	                            //	    ╠
	            x[9][2]=x[9][4]=x[9][8] = vertikalMitLinks;				//  ╣
	            x[2][9]=x[8][9]= horizontalMitOben;				        //		╩
	            /*horizontalMitUnten;*/			                            //	╦

	            x[1][0]=x[2][0]=x[3][0]=x[4][0]=x[5][0]=x[6][0]=
	            x[7][0]=x[8][0]=x[1][9]=x[3][9]=x[4][9]=x[5][9]=
	            x[6][9]=x[7][9] = geradeH;			                    //  ═

	            x[0][1]=x[0][2]=x[0][3]=x[0][5]=x[0][6]=x[0][7]=
	            x[0][8]=x[9][1]=x[9][3]=x[9][5]=x[9][6]=x[9][7]=
	            geradeV;		                                        //  ║


	//-------------------Mauern u. Wege-------------------------//

	            x[6][6]=x[8][8] = eckeObenL;			                //	╔
				x[4][2]=x[2][4] = eckeObenR;			                //		╗
				x[2][5]=x[4][7] = eckeUntenL;			                //	╚
				x[6][7] = eckeUntenR;		                            //	    ╝
				/*x[3][5] = vertikalUndHorizontal;*/	                //	╬
	            x[4][5] = vertikalMitLinks;				                //  	╣

				x[2][2]=x[3][2]=x[6][2]=x[7][2]=
	            x[8][2]=x[1][4]=x[6][4]=x[7][4]=x[8][4]=x[3][5]=
	            x[7][6]=x[5][7] = geradeH;			                    //  ═

	            x[4][3]=x[4][4]=x[4][6]=x[2][7]=x[2][8] = geradeV;		//  ║

				x[1][8] = ende;			                                //		!

				x[*pi][*pk] = player;

				*pmaxSchritt = 30;
			}

void karteZwei(int *pi, int *pk, int x[20][20], int *pmaxSchritt){					//karte 2

//--------------------Startposition-----------------------//

			*pi = 7;          //X-Achse//
			*pk = 13;          //Y-Achse//

//----------------------Umrandung-------------------------//

            x[0][0] = eckeObenL;                                    //	    ╔
            x[14][0] = eckeObenR;                                   //	╗
            x[0][14] = eckeUntenL;                                  //	    ╚
            x[14][14] = eckeUntenR;                                 //	╝
            x[0][2]=x[0][6] = vertikalMitRechts;	                //	    ╠
            x[14][2]=x[14][3] = vertikalMitLinks;				    //  ╣
            x[6][14] = horizontalMitOben;				            //		╩
            x[5][0]=x[11][0] = horizontalMitUnten;                  //	╦

            x[1][0]=x[2][0]=x[3][0]=x[4][0]=x[6][0]=
            x[7][0]=x[8][0]=x[9][0]=x[10][0]=x[12][0]=x[13][0]=
            x[1][14]=x[2][14]=x[3][14]=x[4][14]=x[5][14]=x[7][14]=
            x[8][14]=x[9][14]=x[10][14]=x[11][14]=x[12][14]=
            x[13][14] = geradeH;			                        //  ═

            x[0][1]=x[0][3]=x[0][4]=x[0][5]=x[0][7]=x[0][8]=
            x[0][9]=x[0][10]=x[0][11]=x[0][12]=x[0][13]=
            x[14][1]=x[14][4]=x[14][5]=x[14][6]=x[14][7]=
            x[14][8]=x[14][9]=x[14][10]=x[14][11]=x[14][12]=
            x[14][13] = geradeV;		                            //  ║


//-------------------Mauern u. Wege-------------------------//

            x[7][2]=x[13][2]=x[4][5]=x[2][8]=x[9][10]=
            x[6][12] = eckeObenL;			                        //	╔
			x[9][2]=x[5][5]=x[12][7] = eckeObenR;			        //		╗
			x[5][3]=x[9][5]=x[2][12] = eckeUntenL;	                //	╚
			x[3][4]=x[8][8]=x[5][10]=x[10][10]=x[9][12]=
            x[12][12] = eckeUntenR;                                 //	    ╝
			x[7][7] = vertikalUndHorizontal;                        //	╬
            x[7][3]=x[5][6]=x[5][8] = vertikalMitLinks;	            //  	╣
            x[9][3]=x[5][7]=x[7][8] = vertikalMitRechts;	        //	╠
            x[13][3]=x[4][6] = horizontalMitOben;				    //		╩
            x[8][7] = horizontalMitUnten;                           //	╦

			x[1][2]=x[8][2]=x[6][3]=x[10][3]=x[12][3]=
            x[2][4]=x[10][5]=x[11][5]=x[12][5]=x[1][6]=x[3][6]=
            x[6][7]=x[9][7]=x[10][7]=x[11][7]=x[3][8]=x[4][8]=
            x[4][10]=x[3][12]=x[4][12]=x[7][12]=x[8][12]=
            x[11][12] = geradeH;                                    //  ═

            x[5][1]=x[11][1]=x[3][2]=x[5][2]=x[3][3]=x[7][4]=
            x[9][4]=x[7][5]=x[7][6]=x[12][8]=x[2][9]=x[5][9]=
            x[7][9]=x[10][9]=x[12][9]=x[2][10]=x[7][10]=x[12][10]=
            x[2][11]=x[9][11]=x[12][11]=x[6][13] = geradeV;		    //  ║

			x[6][6] = ende;			                                //		!

			x[*pi][*pk] = player;

			*pmaxSchritt = 50;
		}

void karteDrei(int *pi, int *pk, int x[20][20], int *pmaxSchritt){					//karte 3

//--------------------Startposition-----------------------//

			*pi = 18;          //X-Achse//
			*pk = 3;          //Y-Achse//

//----------------------Umrandung-------------------------//

            x[0][0] = eckeObenL;                                          //	    ╔
            x[19][0] = eckeObenR;                                         //	╗
            x[0][19] = eckeUntenL;                                        //	    ╚
            x[19][19] = eckeUntenR;                                       //	╝
            x[0][9]=x[0][10]=x[0][14] = vertikalMitRechts;    	          //	    ╠
            x[19][2]=x[19][8]=x[19][10]=x[19][15]= vertikalMitLinks;      //  ╣
            x[12][19] = horizontalMitOben;				                  //		╩
            x[14][0]=x[15][0] = horizontalMitUnten;                       //	╦

            x[1][0]=x[2][0]=x[3][0]=x[4][0]=x[5][0]=x[6][0]=
            x[7][0]=x[8][0]=x[9][0]=x[10][0]=x[11][0]=x[12][0]=
            x[13][0]=x[16][0]=x[17][0]=x[18][0]=x[1][19]=x[2][19]=
            x[3][19]=x[4][19]=x[5][19]=x[6][19]=x[7][19]=x[8][19]=
            x[9][19]=x[10][19]=x[11][19]=x[13][19]=x[14][19]=
            x[15][19]=x[16][19]=x[17][19]=x[18][19] = geradeH;	          //  ═

            x[0][1]=x[0][2]=x[0][3]=x[0][4]=x[0][5]=x[0][6]=
            x[0][7]=x[0][8]=x[0][11]=x[0][12]=x[0][13]=x[0][15]=
            x[0][16]=x[0][17]=x[0][18]=x[19][1]=x[19][3]=x[19][4]=
            x[19][5]=x[19][6]=x[19][7]=x[19][9]=x[19][11]=x[19][12]=
            x[19][13]=x[19][14]=x[19][16]=x[19][17]=x[19][18] =
            geradeV;		                                              //  ║


//-------------------Mauern u. Wege-------------------------//

            x[2][2]=x[8][2]=x[17][2]=x[4][4]=x[17][10]=x[3][11]=
            x[11][15]=x[11][4]=x[12][10]=x[15][3]=x[13][1] = eckeObenL;			                      //	╔
			x[9][4]=x[17][5]=x[6][13]=x[12][17] =
            eckeObenR;		                                              //		╗
			x[2][7]=x[15][8]=x[3][13]=x[11][13]=x[6][15]=
            x[14][17]=x[11][17]=x[15][5] = eckeUntenL;	                                 //	╚
			x[15][1]=x[17][3]=x[11][8]=x[1][10]=x[4][11]=
            x[9][17]=x[13][11]=x[13][2] = eckeUntenR;                                        //	    ╝
			x[13][10] = vertikalUndHorizontal;                            //	╬
            x[3][12]=x[9][13]=x[4][7]=x[15][4] = vertikalMitLinks;	                      //  	    ╣
            x[4][6] = vertikalMitRechts;	          //	╠
            x[8][4]=x[7][9]=x[15][13]=x[14][1]=x[12][11] = horizontalMitOben;			      //		╩
            x[13][4]=x[10][8]=x[1][9]=x[14][13]=x[9][11]=x[11][11] = horizontalMitUnten;     //	╦

			x[3][2]=x[4][2]=x[5][2]=x[6][2]=x[9][2]=x[10][2]=
            x[11][2]=x[12][2]=x[18][2]=x[16][3]=
            x[5][4]=x[6][4]=x[7][4]=x[12][4]=x[14][4]=
            x[16][5]=x[3][7]=x[9][8]=x[16][8]=x[17][8]=x[18][8]=
            x[2][9]=x[6][9]=x[8][9]=x[14][10]=x[15][10]=
            x[18][10]=x[6][11]=x[7][11]=x[8][11]=x[10][11]=
            x[2][12]=x[4][13]=x[5][13]=x[8][13]=x[12][13]=x[13][13]=
            x[16][13]=x[17][13]=x[1][14]=x[2][15]=x[3][15]=x[4][15]=
            x[7][15]=x[12][15]=x[16][15]=x[17][15]=x[18][15]=
            x[2][17]=x[3][17]=x[4][17]=x[5][17]=x[6][17]=x[7][17]=
            x[8][17]=x[15][17]=x[16][17]=x[17][17]=x[5][6] = geradeH;             //   ═

            x[2][3]=x[8][3]=x[2][4]=x[2][5]=x[4][5]=x[9][5]=x[11][5]=
            x[13][5]=x[2][6]=x[7][6]=x[9][6]=x[11][6]=
            x[13][6]=x[17][6]=x[7][7]=x[11][7]=x[13][7]=x[15][7]=
            x[4][8]=x[7][8]=x[13][8]=x[4][9]=x[10][9]=x[13][9]=
            x[4][10]=x[17][11]=x[9][12]=x[11][12]=x[15][12]=
            x[6][14]=x[9][14]=x[14][14]=x[9][15]=x[14][15]=x[9][16]=
            x[11][16]=x[14][16]=x[12][18] = geradeV;		      //       ║

			x[18][1] = ende;			                                  //   !

			x[*pi][*pk] = player;

			*pmaxSchritt = 105;
		}

char initialisierung(int *pi, int *pk, int x[20][20], int *pwieder, int *pwiederNeu, int *pgewinn, int *pcounter, int *pfalscheEingabe){
	char wahl;

	for (*pi = 0; *pi<20; *pi += 1){				//Alles auf null stellen um sicher zu sein, dass kein "Mist" gespeichert ist
	        	for(*pk = 0; *pk <20; *pk+= 1)
	        		x[*pi][*pk] = 0;
	        }
	system("cls");
	        printf( "Labyrinth:\n"
	                "\nDas Ziel ist es am Ende(!) vom Labyrinth anzukommen\n"
	                "mit der minimalen Anzahl von Schritten.\n"
	                "Um sich zu bewegen, benutzen sie die Pfeiltasten\n"
	        		"\nDruecken sie die Nummer des LvL, um es zu spielen:\n"
	        		" LvL 1 , LvL 2 , LvL 3, Test LvL 4,\n "
	        		"alles anderes beendet den Programm\n");
	        fflush(stdin);
	        scanf("%c", &wahl);						//LvL auswählen

	        *pwieder = 0;
	        *pwiederNeu = 0;
	        *pgewinn = 0;
	        *pcounter = 0;
	        *pfalscheEingabe = 0;
			system("cls");
	        return wahl;
}

void winLose(int *pi, int *pk, int x[20][20], int *pwieder, int *pwiederNeu, int *pgewinn, int *pcounter, int *pfalscheEingabe,int *pmaxSchritt){	//Testen ob man gewonnen oder verloren hat
	if (*pcounter > *pmaxSchritt){															//Maximal Schrittenanzahl ueberschritten
		printf("Sie haben Verloren. Um wieder zu spielen geben sie 1 ein:\n");
		fflush(stdout);
		scanf("%d", &*pwiederNeu);
		*pwieder = 1;										//zuruck zum Lvl auswaehlen
		x[*pi][*pk]= 0;											//reset position
	}


	if (*pgewinn == 1){																						//Ende Erreicht
		printf("\n\n\nSie Haben mit %d Schritten Gewonnen!!!\n1 eingeben um wieder zu spielen:\n", *pcounter);
		fflush(stdout);
		scanf("%d", &*pwiederNeu);
		*pwieder = 1;									//zuruck zum Lvl auswaehlen
		x[*pi][*pk]= 0;										//reset position
	}
}
