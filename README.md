# 📠 Electronic Turing Machine Prototype

Ce projet implémente un prototype fonctionnel et physique d'une **Machine de Turing** sur microcontrôleur **Microchip PIC24**. Il utilise une matrice de LED RGB pilotée en SPI pour afficher l'état de la bande et de la tête de lecture, ainsi que des boutons-poussoirs pour configurer la bande manuellement avant de lancer un algorithme de calcul (ici, un algorithme d'addition binaire).

Le projet est structuré sous forme d'étapes de tests conditionnels (`#if CURRENT_TEST`) permettant de valider le matériel de manière incrémentale (boutons seuls, matrice seule, puis système complet).

---

## 🚀 Fonctionnalités (Test Principal : `TEST_MACHINE_TURING`)

* **Bande de Turing Physique :** Une bande de 8 cases symbolisée sur l'écran. 
    * `0` (Vide) ➡️ LED éteinte (Noir)
    * `1` (Bit à 1) ➡️ LED Verte
    * `2` (Bit à 0) ➡️ LED Rouge
* **Tête de Lecture Mobile :** Un curseur Bleu affiche la position actuelle de la tête de lecture sur la dernière ligne de la matrice.
* **Éditeur de Bande Interactif :** * Boutons `UP` / `DOWN` : Déplacement horizontal du curseur.
    * Bouton `SELECT` (Clic court) : Permet de cycler la valeur de la case pointée (Vide ➡️ Vert ➡️ Rouge ➡️ Vide).
* **Moteur de Calcul Synchrone :** * Bouton `SELECT` (Appui long > 1s) : Lance l'exécution automatique de l'algorithme d'addition binaire.
    * **Bouclier anti-plantage :** Si la bande est complètement vide, le système fait clignoter l'écran et refuse de lancer le calcul pour éviter une boucle infinie.
    * Mise à jour visuelle en temps réel à chaque transition d'état (temporisation de 1,5s entre chaque étape).

---

## 🛠️ Architecture Matérielle & Configuration

Le projet est conçu pour un microcontrôleur PIC24 (géré via le compilateur `XC16` sous MPLAB X).

### Brochage (Mapping)
* **Périphérique d'affichage (Matrice LED) :** * `MOSI` ➡️ Broche RP12 (`RB12`)
    * `SCK` ➡️ Broche RP13 (`RB13`)
    * `CS` (Chip Select) ➡️ Broche `RB14`
* **Entrées (Boutons avec Pull-ups internes activés) :**
    * `BTN_UP` (Gauche) ➡️ `RA0`
    * `BTN_DOWN` (Droite) ➡️ `RA1`
    * `BTN_SELECT` (Édition / Validation) ➡️ `RA4`
    * `BTN_START` ➡️ `RB7`
* **Indicateur visuel :** `LED_TEST` ➡️ `RB4`

### Protocole d'affichage
L'affichage repose sur une liaison **SPI 8-bits Master**. Le format de couleur envoyé à la matrice est le **RGB332** (1 octet par pixel) :
* `COULEUR_NOIR` : `0x00`
* `COULEUR_ROUGE` : `0xE0`
* `COULEUR_VERT` : `0x1C`
* `COULEUR_BLEU` : `0x03`

---

## 📁 Structure du Code

L'organisation des fichiers respecte les standards de l'embarqué pour assurer la modularité :

* **`main.c`** : Point d'entrée du programme. Initialise le système et exécute la boucle principale non-bloquante (`Turing_Task`).
* **`lib_turing.h`** : Centralise la configuration de l'horloge (`FCY = 4MHz`), le mapping des broches, les codes couleurs RGB332 et la sélection du test à compiler via `CURRENT_TEST`.
* **`lib_turing.c`** : Contient l'implémentation des pilotes matériels (SPI, Matrix Control) et toute la logique de la machine d'états de Turing (fonctions de transition, moteur de calcul, gestion de l'anti-rebond des boutons).

---

## ⚙️ Compilation et Choix des Tests

Le fichier `lib_turing.h` intègre un système de switch logiciel puissant pour valider la carte étape par étape. Modifiez la macro `#define CURRENT_TEST` avec l'une des valeurs suivantes :

| Macro | Description |
| :--- | :--- |
| `TEST_BOUTONS` | Allume la LED témoin dès qu'un bouton est pressé. Idéal pour valider le câblage et les pull-ups. |
| `TEST_MATRICE` | Effectue un cycle de couleurs plein écran (Rouge ➡️ Vert ➡️ Bleu ➡️ Noir) pour tester la communication SPI. |
| `TEST_MATRICE_BOUTONS` | Permet de déplacer le curseur et d'écrire sur la matrice sans lancer le calcul. |
| `TEST_MACHINE_TURING` | **(Défaut)** Mode complet incluant l'algorithme d'addition binaire et le moteur d'exécution. |
