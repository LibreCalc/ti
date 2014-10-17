/*
  Copyright (c) 2014 Pierre Parent
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "tiString.h"
#include "tiConfig.h"
#include "tiVariant.h"


/**
 * @brief Permet de gérer les commandes naturelle que l'on peut entrer dans l'écran principal par exemple
 * @param s La commande
 * @param conf L'état actuel de la configuration de la ti
 * @return le résultat de la commande
 */
TiVariant SendCommand( TiString s, TiConfig& conf);

/**
 * @brief Permet de trouver un symbole d'affectation dans la chaine de caractères
 * @param s la chaine de caractère
 * @return La position du caractère d'affectation
 */
int findSto(TiString s);
#endif