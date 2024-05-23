/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:40:33 by ncollign          #+#    #+#             */
/*   Updated: 2024/05/15 15:25:49 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <stddef.h>
# include <limits.h>

// Basic libft
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, char const *src, size_t size);
size_t	ft_strlen(char const *c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memchr(void const *s, int c, size_t n);
int		ft_memcmp(void const *s1, void const *s2, size_t n);
void	*ft_memcpy(void	*dest, void const *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char const *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(char const *src, int c);
char	*ft_strrchr(const char *src, int c);
char	*ft_strdup(char const *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(char const *s1, char const *s2, size_t n);
char	*ft_strnstr(char const *hay, char const *needle, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

// ft_printf
int		ft_puthex(unsigned int n, const char format);
int		ft_itoa_hex(unsigned long n, const char format);
int		ft_putptr(unsigned long int ptr);
int		ft_putunbr(unsigned int n);
int		ft_putnbr(int n);
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_nblen(int n);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
char	*get_next_line(int fd);

// Autre
void	ft_free(char **buffer);

#endif
