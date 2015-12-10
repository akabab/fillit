/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 20:09:01 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/25 14:41:00 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <string.h>

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

/*
**	Get_next_line
*/
# define BUFF_SIZE	4096

int					get_next_line(int const fd, char **line);

/*
**	Printf
*/
int					ft_printf(const char *format, ...);

/*
**	Memory
*/
void				*ft_memset(void *b, int c, size_t n);
void				*ft_memcpy(void *dst, void const *src, size_t n);
void				*ft_memccpy(void *dst, void const *src, int c, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
void				*ft_memmove(void *dst, void const *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
**	String
*/
size_t				ft_strlen(char const *str);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strdup(char const *s1);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
char				*ft_strcat(char *dest, char const *src);
char				*ft_strncat(char *dest, char const *src, size_t n);
size_t				ft_strlcat(char *dest, char const *src, size_t n);
char				*ft_strstr(char const *str, char const *to_find);
char				*ft_strnstr(char const *str, char const *to_find, size_t n);
char				*ft_strchr(char const *str, int c);
char				*ft_strrchr(char const *str, int c);
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
char				*ft_strjoin3(char const *a, char const *b, char const *c);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_once(char const *s, char c);
char				*ft_strreplace(char *src, char *from, char *to);

int					ft_str_isdigit(char *str);
int					ft_str_isint(char *str);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

/*
**	Numbers
*/
size_t				ft_nbrlen(int n);
int					ft_atoi(char const *str);
char				*ft_itoa(int n);

/*
**	Write
*/
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
**	Simple List
*/
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
void				ft_lstpush(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
**	Math
*/
int					ft_min(int x, int y);
float				ft_fmin(float x, float y);
double				ft_dmin(double x, double y);
int					ft_max(int x, int y);
float				ft_fmax(float x, float y);
double				ft_dmax(double x, double y);
size_t				ft_abs(int n);
size_t				ft_power(int n, int p);
double				fdeg_to_rad(double value);
double				frad_to_deg(double value);
double				frad(double value);
double				fdeg(double value);
int					decimal_to_octal(int n);
int					octal_to_decimal(int n);

/*
**	Free
*/
void				free_tab(char ***tab);
void				free_ntab(char ***tab, int n);

/*
**	Error
*/
void				ft_perror(const char *msg);
void				error_msg(char *message);
void				error_msg_exit(char *message);

#endif
