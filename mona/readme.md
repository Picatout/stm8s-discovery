MONA
====
Moniteur écris en assembleur

Ce moniteur peut-être utile pour interragir directement avec le microcontrôleur en observant l'effet produit par la modification des registres de 
contrôle des périphérique. Par exemple pour allumer la LED vers sur la carte la commande **c $500f 1** peut-être utilisée. **$500f** est l'adresse du registre
**PD_ODR**  et le LED est branché sur PD0. 
  
commandes:
----------
* @ addr, affiche la valeur de l'octet à l'adresse donnée.
* ! addr byte [byte ]*, dépose les octets données aux adresses successsives à partir de 'addr'.
* ?, affiche la liste des commandes.
* b n|$n, convertie l'entier dans l'autre base. i.e. dec->hex|hex->dec.
* c addr bitmask, met les bits masqués à zéro.
* h addr, Affiche le contenu de la mémoire en hexadécimal par rangée de 8 octets. Pause à chaque rangée. ESPACE continue, autre termine.
* m src dest count, copie le bloc mémoire de 'src' vers 'dest', 'count' est le nombre d'octets à copier.
* s addr bitmask, met à 1 les bits masqués.
* t addr bitmask, inverse la valeur des bits masqués.
* x addr, exécute le code à l'adresse donnée. i.e. x $6000 réinialise la carte. 

 utilisation
 -----------
 
  Le UART2 du STM8S-DISCOVERY est branché sur les broches **TX -> PD5** et **RX -> PD6**. Il suffit de relié ces 2 broches à un adapteur de niveaux 
  pour port sériel qui est relié à un PC. MONA communique à la vitesse de **115200 BAUD** configuré en **8N1** pas de contrôle de flux.
  
  Personnellement je travaille sur un poste en Ubuntu et j'utilise **minicom** comme émulateur de terminal **VT100**.
  
  [capteur écran MONA](capture_ecran_mona.png)
  
  


