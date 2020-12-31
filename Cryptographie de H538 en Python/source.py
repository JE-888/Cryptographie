# ----------   ----------  ----------   ---------- ---------- #
# CECI EST LE FICHIER CONTENANT TOUTES LES FONCTIONS #
# ----------   ----------  ----------   ---------- ---------- #

from random import randint
from math import sqrt

def create_output(text): # Entre le résultat dans un fichier texte (pour les longs messages)
    with open("output.txt", "w") as f: # Dans le code, le fichier s'appelle "f", mais son nom est "output.txt"
        f.write(text)

def spin(finput, amount, fdir):

    # Décale les éléments d'une liste de amount positions, si fdir = 0 vers la gauche, sinon vers la droite

    if fdir == 0:
        for i in range(amount):
            data = finput[0]
            finput.pop(0)
            finput.append(data)
    else:
        for i in range(amount):
            data = finput[len(finput)-1]
            finput.pop(len(finput)-1)
            finput.insert(0, data)
    return finput

def wheel_roll(wheel, num, key3):
    # Fait "tourner" la roue (décale les éléments d'une liste (spin) et applique la procédure de cryptage)
    wheel = spin(wheel, num, 1)
    i = wheel.index(str(num))
    data = wheel[i]
    wheel.pop(i)
    moves_limit = i + 1 - len(wheel)
    moves_limit = sqrt(moves_limit**2)
    if key3 > moves_limit:
        wheel.insert(int(key3-moves_limit-1), str(num))
    else:
        wheel.insert(int(i+key3), str(num))
    return wheel

def generate_random_char(mode):

    # Génère un nombre aléatoire sur le format d'une lettre en ascii

    if mode == "l":
        return [str(randint(0, 3)), str(randint(0, 9)), str(randint(0, 9))]
    elif mode == "s":
        return str(randint(0, 3))+str(randint(0, 9))+str(randint(0, 9))

def convert_bases(number, base):

    # Passe un nombre number en base base

    result = []
    fliped_result = []
    while number >= base:
        r=number % base
        fliped_result.append(r)
        number = number // base
    r=number % base
    fliped_result.append(r)
    number = number // base

    # Remets le résultat (inversé) dans le bon sens

    for i in range(len(fliped_result)):
        result.append(fliped_result[len(fliped_result)-1])
        fliped_result.pop(len(fliped_result)-1)

    return result

def convert_text(text):

    # Convertit du texte en chiffres (ascii)

    num = ""
    result = ""
    for char in text:
        num = str(ord(char))
        while len(num) < 3:
            num = "0"+num
        result = result + num
    return result

def convert_num(num):

    # Convertit des nombres en texte (ascii)

    my_list = []
    result = ""
    i = 0
    new_element = ""
    for char in num:
        new_element = str(new_element) + str(char)
        if i == 2:
            my_list.append(new_element)
            new_element = 0
            i = -1
        i += 1

    for element in my_list:
        result += chr(int(element))

    return result
            

def make_key(key): # Ceci est une fonction de création de clés
    
    key = convert_text(key) # On doit pouvoir entrer une clé textuelle (plus pratique), le programme la transformera en chiffres.

    # Vérification de la validité de la clé

    try:
        key = int(key)
        key = str(key)
    except:
        print("KEY ERROR : erreur de clé.")
        return "KEY ERROR"

    # Décomposition de la clé en plusieurs sous-clés

    key1 = convert_bases(int(key), 2)
    key2 = convert_bases(int(key), 4)

    key4 = ""
    used_numbers = []
    key_chars = []

    for char in key:
        key_chars.append(char)

    key3 = int(key_chars[0])
    key_chars.pop(0)

    for char in key_chars:
        if char not in used_numbers:
            key4 += char
            used_numbers.append(char)
    
    for i in range(10):
        if str(i) not in key4:
            key4 += str(i)

    return [key1, key2, key3, key4] # Retourne une liste contenant toutes les clés

def key_iterator(key, index): # Parcoure une clé pour en extraire l'élément d'un index. Si l'index dépasse, lui retirer la longueur de la clé.
    if index < len(key):
        return key[index]
    else:
        return key[index%len(key)]
            
def crypt(message, key, key3=""):

    # Décomposition de la clé principale
    keys_list = make_key(key)
    key1 = keys_list[0]
    key2 = keys_list[1]
    if key3 == "": # On peut choisir manuellement la clé 3
        key3 = keys_list[2]
    else:
        key3 = int(key3)
    key4 = keys_list[3]

    # ---------- Etape 1 ---------- #

    text = []
    for char in message:
        text.append(char)
    i = 0
    ai = 0 # ai = absolute index, indique le nombre de "tours" de la boucle
    result = []
    while i < len(text):
        char = text[i]
        input_list = []
        char = convert_text(char)
        for num in char:
            input_list.append(num)

        if key_iterator(key1, ai) == 0: # Première possibilité
            if key_iterator(key2, ai) == 0: # key2 détermine la position du nombre aléatoire
                result.append(char+generate_random_char("s"))
            elif key_iterator(key2, ai) == 1:
                result.append(generate_random_char("s")+char)
            elif key_iterator(key2, ai) == 2:
                rnd_char = generate_random_char("l")
                result.append(rnd_char[0]+rnd_char[1]+char+rnd_char[2])
            elif key_iterator(key2, ai) == 3:
                rnd_char = generate_random_char("l")
                result.append(rnd_char[0]+char+rnd_char[1]+rnd_char[2])
            else:
                print("KEY ERROR : erreur de clé.") # Clé invalide

        elif key_iterator(key1, ai) == 1: # Deuxième possibilité
            try:
                result.append(char+convert_text(text[i+1]))
            except:
                result.append(char+"032")
            i += 1
        else:
            print("KEY ERROR : erreur de clé.") # Clé invalide

        i += 1
        ai += 1

    # ---------- Etape 2 ---------- #

    numbers_list = []
    for char in key4:
        numbers_list.append(char)

    raw_message = ""

    for element in result:
        raw_message = raw_message + str(element)

    proceeded_message = ""
    for char in raw_message:
        i = numbers_list.index(char)
        char = numbers_list[int(char)]
        proceeded_message += char
        numbers_list = wheel_roll(numbers_list, int(char), key3)

    create_output(proceeded_message) # Mets le tout dans un fichier texte
    return proceeded_message

def uncrypt(message, key):

    # Décomposition de la clé principale
    keys_list = make_key(key)
    key1 = keys_list[0]
    key2 = keys_list[1]
    key3 = keys_list[2]
    key4 = keys_list[3]

    # ---------- Etape 1 ---------- #
    
    # L'étape 1 du décryptage permet de défaire l'étape 2 du cryptage
    numbers_list = []
    for char in key4:
        numbers_list.append(char)

    ai = 0
    result = []
    code_list = []
    bckup_list = []
    raw_message = []

    for char in message:
        raw_message.append(char)

    for char in message:
        bckup_list = list(numbers_list)
        i = numbers_list.index(char)
        numbers_list = wheel_roll(numbers_list, int(char), key3)
        char = numbers_list[int(char)]
        result.append(bckup_list.index(str(raw_message[ai])))
        ai += 1
    
    # ---------- Etape 2 ---------- #

    result2 = []
    i = 0 # i va permettre d'indiquer ou on en est dans le message à décoder
    ai = 0

    while i < len(result):
        if key_iterator(key1, ai) == 0: # Enlever l'aléatoire avec les clés 1 et 2
            if key_iterator(key2, ai) == 0: # A chaque condition, selon la clé 2, on détermine la position de l'aléatoire et on le retire
                result2.append(str(result[i+0])+str(result[i+1])+str(result[i+2]))
            elif key_iterator(key2, ai) == 1:
                result2.append(str(result[i+3])+str(result[i+4])+str(result[i+5]))
            elif key_iterator(key2, ai) == 2:
                result2.append(str(result[i+2])+str(result[i+3])+str(result[i+4]))
            elif key_iterator(key2, ai) == 3:
                result2.append(str(result[i+1])+str(result[i+2])+str(result[i+3]))

        elif key_iterator(key1, ai) == 1: # Prends deux caractères
            try:
                result2.append(str(result[i+0])+str(result[i+1])+str(result[i+2])+str(result[i+3])+str(result[i+4])+str(result[i+5]))
            except: # Gère le cas où il ne reste plus qu'un caractère
                result2.append(str(result[i+0])+str(result[i+1])+str(result[i+2]))
        i += 6 # A chaque étape, on traite 6 caractère, on ajoute donc 6 à i
        ai += 1
        
    message = ""
    for element in result2:
        message += str(element)

    message = convert_num(message) # Convertit en texte à partir de la table ascii
    create_output(message) # Mets le tout dans un fichier texte
    return message