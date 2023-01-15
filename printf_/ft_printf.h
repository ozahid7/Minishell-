/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozahid- <ozahid-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:49:22 by ozahid-           #+#    #+#             */
/*   Updated: 2023/01/05 03:09:35 by ozahid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar(int fd, char c);
int	ft_unsignednumber(int fd, unsigned int nb);
int	ft_putnbr(int fd, long nb);
int	ft_putstr(int fd, char *str);
int	ft_hexa(int fd, unsigned int nb, char arg);
int	ft_argp(int fd, unsigned long nb);
int	fprint(int fd, const char *str, ...);

#endif
