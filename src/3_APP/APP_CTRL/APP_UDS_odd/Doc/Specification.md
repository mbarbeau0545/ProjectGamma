# Specification globale 
Offrir un service de diagnostic.
- Communiquer en UART / CAN avec l'ECU pour 
    - Connaitre avec un taux de rafraichissement de x ms les valeurs de Sensors/ Actuators
    - Prendre le contrôle sur les actionneurs pour voir s'ils s'activent indépendemment de la logic (boucle ouverte)
    - Connaitre la charge CPU.
    - Connaitre / Changer la valeur de paramètre.
    - Lecture des codes erreurs en cours et ceux enregistrées
    - flasher l'ECU


# start communication entre un / plusieurs ECU 
C'est l'application qui initie la communication, l'utilisateur appuiera sur un bouton et cela permettra d'envoyer une requête à l'ECU
pour dire que qlq veux se connecter et échanger avec lui. l'ECU accepte ou non, s'il accepte il envoie son identifiant unique et la version de son software. si les deux versions (celle entré par le user et celle flashé dans l'ecu ne correspondent pas), l'application doit en informer le user.   
Une fois que la communication est établie, suivant ce que veut faire le user, l'application enverra une requête à l'ECU (un mask avec les bits à 1 là où il veut des trucs). 
les requêtes sont composées de 8 octets, le 1 octet l'ID de l'ECU, le deuxième l'ID de la requête et le dernier octet le checksum 
- L'utilisateur veut savoir un temps réel la valeur des capteurs et des actuators 
    l'application envoie une requête avec le bon Id le taux de raffraîchissement (en ms) et attend un aknowlegment de la part de l'ECU pour lui dire OK, 
    si c'est OK l'ECU envoit toutes les x ms les données des actuators et des sensors, l'état des services, la valeur de la machine à état de chaque module, et des agents. le temps de cyclic. 

- l'utilisateur veut contrôler les actionneurs :
    - il envoie l'état d'un ou des actionneurs toutes les x ms. 

- l'utilisateur envoie l'id du paramètre qu'il veut et on lui envoie (idem pour set les paramètres. )

- 