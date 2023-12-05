---
title: "Motivacija: Primerjava sistemskih klicev Unix in Windows"
author: Miha Meglič
date: 10. april 2023
geometry: margin=3cm
---

# Motivacija

Že od nekdaj me zanimajo operacijski sistemi ter njihova interakcija z uporabniškimi vmesniki in strojno opremo. Razumel sem namreč kako delujejo programi na nizkem nivoju (npr. vgrajeni sistemi) in kako na visokem nivoju (npr. uporabniške aplikacije), vedno pa mi je manjkalo nekaj v sredini - operacijski sistemi. Tekom študija sem precej dopolnil svoje znanje na danih področjih, ter poglobil zanimanje za delovanje operacijskih sistemov in njihovih komponent, kot so na primer imenski prostori (*angl. namespace*), sistemski klici, jedrni moduli (*angl. kernel module*) in druge, ki jih mogoče sploh še nisem odkril.

Pri predmetu Operacijski sistemi in pa v prostem času sem na teh področjih pridobil ogromno znanja v kontekstu operacijskega sistema GNU/Linux, sedaj pa imam priložnost raziskati še drugo stran zgodbe - Windows API.

# Problemska domena

Unix-like sistemi kot je Linux so na področju nižje nivojskih uporabniških aplikacij skorajda neke vrste "de facto" standard, kar pomeni da smo vsi dokaj dobro seznanjeni in prilagojeni na delo z Linux sistemskimi klici. Tu pa se poraja vprašanje - kako te stvari narediti v operacijskih sistemih Windows?

- Kakšna je razlika v hitrosti izvajanja enakovredne kode?
- Kakšna je razlika v preprostosti uporabe?
- Kako dobro so različne funkcionalnosti dokumentirane?
- Kateri od sistemov podpira več in/ali bolj napredne funkcionalnosti?
- Kako bi ustvarili prevajalno plast, da bi lahko Linux aplikacije poganjali na Windowsih ali obratno?

# Pregled področja

Ob dokaj hitrem pregledu virov na dano temo sem odkril sledeča uporabna besedila:

1. D. Mohar, „Sledenje programom v operacijskem sistemu Linux“, Diplomsko delo, Univerza v Ljubljani, 2016 [Online]. Dostopno: <https://repozitorij.uni-lj.si/IzpisGradiva.php?id=80176>.
2. B. Šter, „Sistemsko programiranje v Linuxu“ Založba FE in FRI, Ljubljana, 2014. [Online]. Dostopno: <http://www.dlib.si/details/URN:NBN:SI:doc-PZ68VXUE>.
3. B. Fras, „Gonilniki v operacijskem sistemu Linux : diplomsko delo“, Diplomsko delo, Univerza v Mariboru, Maribor, 2020 [Online]. Dostopno: <https://dk.um.si/IzpisGradiva.php?id=77762>.
4. M. Nanut, „Varno izvajanje programov v operacijskem sistemu GNU/Linux“, Diplomsko delo, Univerza v Ljubljani, 2014 [Online]. Dostopno: <https://repozitorij.uni-lj.si/IzpisGradiva.php?id=30077>.

# Sorodne rešitve

Prevajanje ali emulacija Linux programov na Windowsih:

- [MinGW](https://mingw.osdn.io/) - preko ponovnega prevajanja kode
- [Cygwin](https://www.cygwin.com/)
- [WSL](https://learn.microsoft.com/en-us/windows/wsl/) (*Windows Subsystem for Linux*)

Prevajanje ali emulacija Windows programov na Linuxu:

- [Wine](https://www.winehq.org/)
- [Proton](https://github.com/ValveSoftware/Proton) - samo računalniške igrice

# Idejni in terminski plan

1. Identificirati skupine sorodnih sistemskih klicev
2. Opisati sistemske/API klice, ki jih sistema ponujata - **do konca maja 2023**
3. Izdelati primer programa za vsako od skupin
4. Primerjati razne parametre izdelanih programov - **do konca junija 2023**  
   *število vrstic, čas izvajanja, preprostost uporabe*
5. Oblikovati zaključek na vprašanja postavljena zgoraj (v poglavju Problemska domena)

Predvidevam, da bom najkasneje do konca julija 2023 zaključil s pisanjem ter nalogo zagovarjal v avgustu 2023.
