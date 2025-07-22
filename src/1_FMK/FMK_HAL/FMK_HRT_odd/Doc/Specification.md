# Introduction 
    Ce module doit permettre d'avoir plus d'output qui utilise les Timers. 
    La naissance de ce module provient d'un besoin de contrôler plusieurs moteur (qui nécessite l'utilisatation du RCR)
    et que seule les timers normaux ne peuvent assouvir. 
    Avec les HRTIM, en l'occurence un maitre et 6 esclaves timer (2 channels chacun). On pourrait se permettre 
    de s'affranchir du problème de fréquence partagé au sein d'un même timer. 
    Donc en conclusion, on aura une output par timer et on pourra utiliser les autres channels pour des input par exemple (ou pas car dépendant de la fréquence). Le cas où plusieurs I/O sont utilisées (d'un même mode ex PWM,OP,IC) sur un même timer doit être intégrées dans le software au cas où l'utilisateur souhait de la synchronisation d'event 'auto-géré'

    Le problème identifier majeur est la génération de PWM sous toutes ses formes :
        - PWM normal (Infinite Pulse) une fréquence qui ne change pas souvent et duty cycle qui change souvent -> easy. (Genral Purpose Timer)
        - PWM pas normal (Finite Pulse) ou la PWM est finie dans le temps et est gérée par le RCR compteur -> relou car RCR compteur est commun à toutes les channels (Advance Purpose Timer)
        - PWM avec régulation de courant (chaque timer à deux channels, on s'en servira d'une seule à chaque fois) possède son propre registre RCR et CCR et ARR donc tiptop, et peux faire les deux niveaux précédents 

    In fine le but de ce module est motivé par la génération de PWM avec régulation de courant qui offrirait aussi les modes moins abstrait. Cela doit être 
    fait en respectant les éventuelles autres implémentations des autres modes proposées par les librairies HAL.

# design FMK_HRT
    On va faire 

# Intégration dans le FMK 
    A ce jour, il y a lorsqu'on configure une PWM, le mode Normal et pas Normal (qu'il faut améliorer avec une configuration Capabilities des output selon le timer.) On peut simplement rajouter le mode Régulation de courant et selon la config IO on accepte ou pas. 

    implicaiton FMKIO -> 
        Comme un timer = une IO, plus nécessité à check pulse finite ou infininte,
        On appelle soit FMKTIM, soit FMK_HRTIM pour set le timer et sa config.
        pour get le dutycycle ou la freq, idem on apelle soit FMKTIM ou FMKHRTIM 
        dans l'idéal il faudrait un peu avoir la même strucutre d'argument à pour get et set.
        L'idée la plus imple serait que l'API public redirige ver sune API static qui set les bons argumetns pour après l'envoyé à FMKTIM ou l'autre 
        ou alors un tableau de fonction avec la config car cette fois-ci argument similaire.

        Ce sera donc dans la config Excel FMKIO que l'on mettra une seul channel par timer la une par exemple. au total, c'est jusqu'à 16 sorties PWM si un timer = 1 sortie (6 RegPwmPWM/AdvPWM + 3 AdvPwm + 7 PWM) = suffisant.
