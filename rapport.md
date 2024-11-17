<div align="justify" style="margin-right:25px;margin-left:25px">

# Laboratoire 4 - Simulateur de trains <!-- omit from toc -->

Calum Quinn - Urs Behrmann

## Table des matières

- [Table des matières](#table-des-matières)
- [Introduction au problème](#introduction-au-problème)
- [Choix d'implémentation](#choix-dimplémentation)
    - [Priorisation](#priorisation)
    - [Zone commune](#zone-commune)
    - [Capteurs de position](#capteurs-de-position)
    - [Attente en gare](#attente-en-gare)
- [Tests effectués](#tests-effectués)
    - [Priorisation](#priorisation-1)
    - [Attente en gare](#attente-en-gare-1)
    - [Arrêt d'urgence](#arrêt-durgence)

## Introduction au problème

Le but de ce laboratoire est d'implémenter l'accès concurrent dans un cas réel. La gestion concerne un tronçon commun entre deux trains. Il est donc important d'implémenter correctement la gestion de la zone pour éviter des collisions entre les trains et des attentes inutiles.

Le projet est séparé en 2 parties. La première représente la mise en place de la gestion basique de la zone partagée. La deuxième amène un nouvel aspect de priorité qui change la gestion de quel train rentre à quel moment dans la zone commune.


## Choix d'implémentation

### Priorisation
Passage du premier arrivé à l'acceptation, pas le request

### Zone commune
trancon en haut, détection du train pour changer les aiguillages

### Capteurs de position
pas celui directement avant la zone, trop proche sinon
capteur de sortie, directement après la zone

### Attente en gare
semaphore block le premier arrivé, débloqué par l'arrivée du deuxième APRES l'attente de 2 sec


## Tests effectués

### Priorisation
cas ou les deux arrivent en même temps
cas ou le train est seul à vouloir rentrer dans la zone
cas ou l'autre est déjà dans la zone
cas ou les deux ont la même priorité, passage du premier

### Attente en gare
cas ou les deux n'arrivent pas en même temps

### Arrêt d'urgence
cas ou un train est en zone partagée et que l'autre attend

</div>
