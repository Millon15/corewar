/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:11:00 by ndidenko          #+#    #+#             */
/*   Updated: 2017/11/30 16:19:06 by ndidenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 100
# define FD_MAX 128

# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <wchar.h>
# include <locale.h>
# include <fcntl.h>

typedef enum		e_size
{
	no_size = -1,
	hh = 0,
	h = 1,
	l = 2,
	ll = 3,
	j = 4,
	z = 5
}					t_size;

typedef struct		s_parsing
{
	int				flag_sharp;
	int				flag_zero;
	int				flag_minus;
	int				flag_plus;
	int				flag_space;
	int				width;
	int				precision;
	t_size			size;
	char			letter;
	int				len;
}					t_parsing;

void				*ft_memset(void *destination, int c, size_t n);
void				ft_bzero(void *destination, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c,
															size_t size);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *array1, const void *array2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *string);
char				*ft_strcpy(char *cpyto, const char *src);
char				*ft_strncpy(char *copyto, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat (char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(char *str, char *to_find);
char				*ft_strnstr(const char *str1, const char *str2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int d);
int					ft_isalnum(int c);
int					ft_isascii(int a);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list*elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int					ft_islower(int c);
int					ft_isupper(int c);
void				ft_strswap(char **s1, char **s2);
int					ft_lstsize(t_list *lst);
int					ft_is_space(char c);

int					get_next_line(const int fd, char **line);

char				*ft_itoa_max(intmax_t n);
char				*ft_itoa_base(uintmax_t n, int base);
int					ft_2to10(char *bin);

int					ft_printf(char *str, ...);
int					ft_print_conv(char *conv, va_list ap);

size_t				ft_search_conversion_letter(char *str);
int					ft_myprint(char *str, va_list ap);
void				ft_struct_init(t_parsing *parsing);
int					ft_printf(char *str, ...);
int					ft_validconv(char *conv);
int					ft_validchar(char *str);
int					ft_valid_flag(const char c);
int					ft_valid_modifier(char c);
int					ft_is_digit(char c);
int					ft_parse_flags(char *conv, t_parsing *parsing);
int					ft_parse_width(char *conv, t_parsing *parsing);
void				ft_detect_precision(char *conv, t_parsing *parsing);
int					ft_parse_precision(char *conv, t_parsing *parsing);
int					ft_parse_size(char *conv, t_parsing *parsing);

void				processing_c(t_parsing *parsing, va_list ap);
void				processing_letter(t_parsing *parsing, va_list ap);

void				processing_s(t_parsing *parsing, va_list ap);

void				processing_d(t_parsing *parsing, va_list ap);
char				*ft_make_str_d(char *str, t_parsing *parsing, intmax_t n);
char				*ft_d1(char *str, t_parsing *parsing, int len,
														intmax_t nbr);
char				*ft_d2(char *str, t_parsing *parsing, int len,
														intmax_t nbr);
char				*ft_d2_2(char *str, t_parsing *parsing, int len,
														intmax_t nbr);
char				*ft_d3(char *str, t_parsing *parsing, int len,
														intmax_t nbr);
char				*ft_d3_1(char *str, t_parsing *parsing, int len);
char				*ft_d4(char *str, t_parsing *parsing, int len,
														intmax_t nbr);

void				processing_u(t_parsing *parsing, va_list ap);
char				*ft_make_str_u(char *str, t_parsing *parsing,
														uintmax_t nbr);

void				processing_o(t_parsing *parsing, va_list ap);
char				*ft_make_str_o(char *str, t_parsing *parsing,
														uintmax_t nbr);

void				processing_x(t_parsing *parsing, va_list ap);
char				*ft_make_str_x(char *str, t_parsing *parsing,
														uintmax_t nbr);
char				*ft_x2(char *str, t_parsing *parsing, int len,
														uintmax_t nbr);
char				*ft_x3(char *str, t_parsing *parsing, int len);

void				processing_p(t_parsing *parsing, va_list ap);

void				processing_unicode(t_parsing *parsing, va_list ap);

void				processing_pct(t_parsing *parsing);
void				processing_invalid(t_parsing *parsing);

char				*ft_left(char *s, int width, int precision, char c);
char				*ft_right(char *s, int width, int precision, char c);

#endif
