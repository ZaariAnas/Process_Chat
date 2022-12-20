/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_com.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azari <azari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:46:17 by azari             #+#    #+#             */
/*   Updated: 2022/12/20 14:46:33 by azari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>


int main()
{
	int fdsp[2];
	int fdsc[2];
	pipe(fdsp);
	pipe(fdsc);
	int i = 0;
	int pid = fork();
	if (pid == 0)
	{
		while (i++ < 5)
		{
			int value;
			close(fdsp[0]);
			close(fdsc[1]);
			read(fdsc[0], &value, sizeof(int));
			value++;
			printf("from child -> %d\n", value);
			write(fdsp[1], &value, sizeof(int));
		}
	}
	else 
	{
		while (i++ < 5)
		{
			int value;
			close(fdsp[1]);
			close(fdsc[0]);
			write(fdsc[1], &value, sizeof(int));
			read(fdsp[0], &value, sizeof(int));
			value++;
			printf("from parent -> %d\n", value);
		}
	}
}
