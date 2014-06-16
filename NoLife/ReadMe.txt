Opis na dzieñ 16.06.2014:

1. WPROWADZENIE:
Na chwilê obecn¹ jes mo¿liwe poruszanie siê postaci¹ po mapie oraz strzelanie. Efekt eksplozji i wykrywanie kolizji dodane zostan¹ w nastêpnym commicie.

G³ównymi klasami projektu s¹: 
* DrawableObject - podstawowy obiekt, który mo¿na wczytaæ, modyfikowaæ, przemieszczaæ i rysowaæ w œwiecie gry (wraz z wersj¹ DrawableObject2D, która u¿yta bêdzie do tworzenia interfejsu u¿ytkownika).

*Scene - scena œwiata gry - singleton - przenoszone do niej bêd¹ z maina odpowiednie dla niej funkcje i w³asnoœci

*GameMaster - TODO - singleton - obs³uga wydarzeñ w grze

* MusicMixer - mikser dŸwiêku wykorzystuj¹cy bibliotekê irrKlang - zarówno odg³osy z gry, jak i podk³ad muzyczny.

*Utworzona jest ju¿ hierarchia klas przeciwników i broni - kiedy dopracowany zostanie silnik graficzny, zostanie odpowiednio rozwiniêta i zmodyfikowana.





2. STEROWANIE:
WSAD - przemieszczanie siê, ruchy myszy - ruch kamer¹ - klasyczny fps-owy sposób.

space - skok

z - stanie x - kucanie c - czo³ganie

e - sprint

LPM - strza³ z broni

m - w³¹czenie/wyl¹czenie podk³adu dŸwiêkowego
n - nastêpny utówr