Opis na dzie� 16.06.2014:

1. WPROWADZENIE:
Na chwil� obecn� jes mo�liwe poruszanie si� postaci� po mapie oraz strzelanie. Efekt eksplozji i wykrywanie kolizji dodane zostan� w nast�pnym commicie.

G��wnymi klasami projektu s�: 
* DrawableObject - podstawowy obiekt, kt�ry mo�na wczyta�, modyfikowa�, przemieszcza� i rysowa� w �wiecie gry (wraz z wersj� DrawableObject2D, kt�ra u�yta b�dzie do tworzenia interfejsu u�ytkownika).

*Scene - scena �wiata gry - singleton - przenoszone do niej b�d� z maina odpowiednie dla niej funkcje i w�asno�ci

*GameMaster - TODO - singleton - obs�uga wydarze� w grze

* MusicMixer - mikser d�wi�ku wykorzystuj�cy bibliotek� irrKlang - zar�wno odg�osy z gry, jak i podk�ad muzyczny.

*Utworzona jest ju� hierarchia klas przeciwnik�w i broni - kiedy dopracowany zostanie silnik graficzny, zostanie odpowiednio rozwini�ta i zmodyfikowana.





2. STEROWANIE:
WSAD - przemieszczanie si�, ruchy myszy - ruch kamer� - klasyczny fps-owy spos�b.

space - skok

z - stanie x - kucanie c - czo�ganie

e - sprint

LPM - strza� z broni

m - w��czenie/wyl�czenie podk�adu d�wi�kowego
n - nast�pny ut�wr