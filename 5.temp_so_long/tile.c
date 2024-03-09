/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/01/26 18:57:57 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*FUNZIONI PER LA GESTIONE DELLE TILES*/
#include "so_long.h"

/*QUESTA FUNZIONE RIEMPIE I CAMPI "COORDINATE" DEGLI ELEMENTI RICEVUTI IN IMPUT_______________
- a seconda della lettera ricevuta in imput riempie i campi "coordinata x", 
  "corrdinata y" e "tipo" della struct.
(es se la lettera e' P riempira' gli elementi della struct personaggio contenuta
 in "map") 
 - Il type sarà passato, al momento della lettura della matrice, all'argomento "char asset"
   (Corrisponde al carattere contenuto all'interno di ogni casella della matrice)
 - le coordinate corrispondono agli indici della casella e verrano passati agli argomenti
   int x e int y
   (Es: posizione della matrice (3,1) = P: - 3 = x
                                           - 1 = y
                                           - P = type )
 Queste informazioni verranno salvate nel membro "map" della struct "t_game" che, 
 a sua volta, contiene gli elementi "player, exit, etc"
 */
void set_tile_location(t_game *ptr_game, char asset, int x, int y)
{
    if (asset == 'P')
        {
           ptr_game -> map.player.tile_type = asset;
           ptr_game -> map.player.x_axis = x;
           ptr_game -> map.player.y_axis = y;
        }
    else if (asset == 'E')
        {
           ptr_game -> map.exit.tile_type = asset;
           ptr_game -> map.exit.x_axis = x;
           ptr_game -> map.exit.y_axis = y;
        }
    else if (asset == 'N')  
        {
           ptr_game -> map.enemy.tile_type = asset;
           ptr_game -> map.enemy.x_axis = x;
           ptr_game -> map.enemy.y_axis = y;
        }    
    else if (asset == 'C')
        {
           ptr_game -> map.collect[ptr_game -> map.n_coin].tile_type = asset;
           ptr_game -> map.collect[ptr_game -> map.n_coin].x_axis = x;
           ptr_game -> map.collect[ptr_game -> map.n_coin].y_axis = y;          /*NOTA: "collect" è un arrai, dovrò quindi
                                                                                                per ciarcun elemento (caratterizzato
                                                                                                dall'indice "n_coin" che, al
                                                                                                tempo stesso, rappresenta il count di 
                                                                                                monete in gico) assegnare i valori dellti
                                                                                                dalla matrice*/
           ptr_game -> map.n_coin++;                                           /*Aumento il count dei collezionabili presenti 
                                                                                        nella mappa*/                                                                                                                                                 
        } 
}