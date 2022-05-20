#include "MapaBits.h"
#include <iostream>

using namespace std;

void MapaBits::setOn(int mapBits[], int bytes)
{
	double bloquesDouble = bytes / 512;
	int bloquesInt = bytes / 512;
	int bloquesReales;

	//detectar los bloques
	//uso un calculo double y uno int para saber cuando un bloque tiene informacion pero no esta lleno,
	//ya que igual se encenderia todo el bloque
	if (bloquesDouble > bloquesInt)
		bloquesReales = bloquesInt + 1;
	else if (bloquesDouble == bloquesInt)
		bloquesReales = bloquesInt;
	else if (bloquesDouble < bloquesInt)
		bloquesReales = bloquesInt;

	int bits = bloquesReales * 8;
	int longitud = sizeof(mapBits);

	//encender los bits
	for (int i = 0; i < bits; i++) {
		mapBits[i] = 1;
	}
}
