/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_array_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:37:44 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/18 22:37:49 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_char_array_len(char **array)
{
	int	len;

	len = 0;
	while (array && array[len])
		len++;
	return (len);
}
