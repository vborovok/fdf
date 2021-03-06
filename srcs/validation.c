/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 14:46:22 by fmasha-h          #+#    #+#             */
/*   Updated: 2020/11/04 14:48:15 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	defer(int fd, char **buf)
{
	if (*buf != NULL)
		free(*buf);
	buf = NULL;
	close(fd);
	return (-1);
}

int			validate_color(char *line, int i)
{
	if (line[i] == '0')
	{
		i++;
		if (line[i] == 'x')
		{
			i++;
			if (in_hex(line[i]))
			{
				while (line[i] && (in_hex(line[i])))
					i++;
				return (i);
			}
		}
	}
	return (-1);
}

int			validate_digit(char *line, int i)
{
	if (line[i] == '0' && ft_isdigit(line[i + 1]) == 0)
		return (++i);
	if (ft_isdigit_not_zero(line[i]))
	{
		while (ft_isdigit(line[i]))
			i++;
		return (i);
	}
	if (line[i] == '-' && ft_isdigit_not_zero(line[i + 1]) == 1)
		return (++i);
	if (line[i] == ',')
	{
		if ((i = validate_color(line, ++i)) == -1)
			return (-1);
		else
			return (i);
	}
	if (ft_isalpha(line[i]) == 1)
		return (-1);
	return (-1);
}

int			validate_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == 1)
			i++;
		else if ((i = validate_digit(line, i)) < 0)
			return (-1);
	}
	return (0);
}

int			count_input_len(char *str, t_img *img,\
							char *buf, int first_line_points_num)
{
	int		fd;
	int		len;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &buf) > 0)
	{
		if (validate_line(buf) == 0 && (len = count_words(buf)) > 0)
		{
			if (first_line_points_num == -1)
				first_line_points_num = len;
			else if (first_line_points_num != len)
				return (defer(fd, &buf));
			img->grid_square += len;
			free(buf);
			buf = NULL;
		}
		else
			return (defer(fd, &buf));
	}
	defer(fd, &buf);
	if (img->grid_square == 0)
		return (-1);
	set_rotation_step(img);
	return (0);
}
