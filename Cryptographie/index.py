# ----------   ----------  ----------   ---------- ---------- #
# CECI EST LE FICHIER QUI SE CHARGE DE L'INTERFACE UTILISATEUR #
# ----------   ----------  ----------   ---------- ---------- #

from source import *
from random import randint
from math import sqrt

mode = "auto" # On a un mode manuel (en choisit la clé 3), et un mode automatique (choisit le clé 3 à partir de la clé globale mais réduit un petit peu les possibilités)
answer = ""
key = ""
key3 = ""
while True:
    answer = input("Quelle action voulez-vous utiliser ? (c/u/e/m) ->")
    if answer == "c": # Crypter
        answer = input("Entrez le message à crypter ->")
        key = input("Entrez la clé ->")
        if mode == "hand":
            while len(key3) != 10 or key3.count("0") != 1 or key3.count("1") != 1 or key3.count("2") != 1 or key3.count("3") != 1 or key3.count("4") != 1 or key3.count("5") != 1 or key3.count("6") != 1 or key3.count("7") != 1 or key3.count("8") != 1 or key3.count("9") != 1:
                key3 = input("Entrez la clé 3 (9 chiffres, tous différents) ->")
        try:
            print(f"RESULT : {crypt(answer, key, key3)}")
        except:
            print("Une erreur s'est produite...")
    elif answer == "u": # Décrypter
        answer = input("Entrez le message à décrypter ->")
        key = input("Entrez la clé ->")
        try:
            print(f"RESULT : {uncrypt(answer, key)}")
        except:
            print("Une erreur s'est produite...")
    elif answer == "e": # Fermer le programme
        print("Fermeture du programme...")
        exit()
    elif answer == "m": # Changer de mode
        if mode == "auto":
            print("Mode manuel activé.")
            mode = "hand"
        elif mode == "hand":
            print("Mode automatique activé.")
            mode = "auto"
    else:
        print("Réponse invalide. Entrez \"c\", \"u\", \"e\" ou \"m\" pour respectivement crypter, décrypter, arrêter le programme, et passer en mode manuel/automatique.")