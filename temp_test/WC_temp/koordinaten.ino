/* 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Dieses Programm ist Freie Software: Sie k�nnen es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
ver�ffentlichten Version, weiterverbreiten und/oder modifizieren.

Dieses Programm wird in der Hoffnung, dass es n�tzlich sein wird, aber
OHNE JEDE GEW�HRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gew�hrleistung der MARKTF�HIGKEIT oder EIGNUNG F�R EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License f�r weitere Details.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>. 
*/

// In dieser Funktion können die Koordinaten zu den Pixeln übergeben werden und es wird die korrekte LED zurück gegeben

/*
   0 1 2 3 4 5 6 7 8 9 10 x
 0 E S K I S T L F U N F 
 1 Z E H N Z W A N Z I G
 2 D R E I V I E R T E L
 3 T G N A C H V O R J M
 4 H A L B Q Z W Ö L F P
 5 Z W E I N S I E B E N
 6 K D R E I R H F U N F
 7 E L F N E U N V I E R 
 8 W A C H T Z E H N R S
 9 B S E C H S F M U H R
 y
*/
void coords(){
int koordinate(int x, int y) {

  int m = x;     //Multiplikator
  int a = y;     //Addierer
  int led = 0;   // LED in der Matrix
 //Gerade Ungerade x koordinate?
   if ((m + 1) % 2 == 0){
     led = (a + 4) + m * 10;
   }
   else{
     led = (13 - a) + m * 10;
   }  
return led;  
}
