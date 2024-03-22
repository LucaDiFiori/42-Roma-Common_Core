/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:44:56 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/03/20 16:23:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	- Cerco "PATH" nella matrice delle variabili d anbiente (esiste sicuramente)
	  con la funzione strnstr
*/
static char	*cmd_env_search(char *cmd, char **envp)
{
	int  	i;
	char	**all_path;
	char	*cmd_path;
	
	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	/* Divido tutti i percorsi presenti nella stringa PATH
	   NOTA = + 5 perchè skippo "PATH ="*/
	all_path = dquote_split(envp[i] + 5, ':');
	
	/*Attacco alla fine di ogni percorso il mio comando e ne testo la presenza
	  con la funzione access*/
	i = 0;
	while (all_path[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(all_path[i], "/"), cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_matrix(all_path);
			return (cmd_path);
		}
		free (cmd_path);
		i++;
	}
	/*Libero la matrice dei percorsi*/
	free_matrix(all_path);
	return (NULL);
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
	
	cmd = dquote_split(argv, ' ');
    
	if (cmd == NULL)
		quit_free("Error: Unable to split the string.\n", NULL, NULL, 1);
	
	cmd_path = cmd_env_search(cmd[0], envp);
	if (cmd_path == NULL)
		quit_free("Error: Command path not found", NULL, cmd, 3);
	
	if (execve(cmd_path, cmd, envp) == -1)
		quit_free("Error executing execve\n", cmd_path, cmd, 4); /*Presumo di dover liberare tutto perche allocati se sono arrivato qui*/
}