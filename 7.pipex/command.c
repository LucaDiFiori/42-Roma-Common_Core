/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:44:56 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/15 14:30:40 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	- Cerco "PATH" nella matrice delle variabili d anbiente (esiste sicuramente)
	  con la funzione strnstr
*/
static char	*cmd_env_search(char *cmd, char **envp)
{
	/*CANCELLARE------------------------------*/
    (void)cmd;
	/******************************************/
    
	int  i;
	
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	
    return (envp[i]);
    /*******************************************/
}

/*
	- Eseguo lo split sulla stringa passata per estrarre il comando con le opzioni
	- chiamo la funzione per estrarre il percorso del comando
	- chiamo execve per avviare il comando
*/
void	command(char *argv, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = NULL;
	cmd_path = NULL;
	
	cmd = ft_split(argv, ' ');
    
	if (cmd == NULL)
		quit_free("Error: Unable to split the string.\n", NULL, NULL, 1);
	
	cmd_path = cmd_env_search(cmd[0], envp);
	if (cmd_path == NULL)
		quit_free("Error: Command path not found", NULL, cmd, 3);
	
	if (execve(cmd_path, cmd, envp) == -1)
		quit_free("Error executing execve\n", cmd_path, cmd, 4); /*Presumo di dover liberare tutto perche allocati se sono arrivato qui*/
}