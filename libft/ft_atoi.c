/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:07:37 by ycribier          #+#    #+#             */
/*   Updated: 2013/11/22 11:07:56 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(char const *str)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	j = i;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = (num * 10) + str[i] - '0';
		else if (!((str[i] == '+' || str[i] == '-') && i == j))
			break ;
		i++;
	}
	if (str[j] == '-')
		num *= -1;
	return (num);
}
