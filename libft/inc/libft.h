/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:09:24 by tspoof            #+#    #+#             */
/*   Updated: 2022/12/15 15:05:11 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "vec.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief ASCII to integer.
 *
 * Returns integer from number string.
 * @param str Number as a string
 * @return int Number as a integer
 */
int		ft_atoi(const char *str);
/**
 * @brief Zero a byte string.
 *
 * Zeroes \b n number of bytes in memory
 * starting from location pointed by \b s.
 * @param s Pointer to memory
 * @param n Number of bytes
 */
void	ft_bzero(void *s, size_t n);
/**
 * @brief Allocate and zero.
 *
 * Allocates memory and sets every byte to 0.
 * @param count How many elements
 * @param size Size of a element (eg. 4 bytes)
 * @return void* Pointer to the allocated memory
 * @attention Allocates memory
 */
void	*ft_calloc(size_t count, size_t size);
/**
 * @brief Is an alphabet or a number.
 *
 * Checks if character is an alphabet or a number.
 * @param c Character as an ASCII desimal
 * @return int 1 if true, 0 if false
 */
int		ft_isalnum(int c);
/**
 * @brief Check if char is alphabet.
 *
 * @param c
 * @return int
 */
int		ft_isalpha(int c);
/**
 * @brief Check if char is ASCII.
 *
 * @param c
 * @return int
 */
int		ft_isascii(int c);
/**
 * @brief Check if char is digit.
 *
 * @param c
 * @return int
 */
int		ft_isdigit(int c);
/**
 * @brief Check if char is printable.
 *
 * @param c
 * @return int
 */
int		ft_isprint(int c);
/**
 * @brief Integer to ASCII.
 *
 * Returns a number as a string.
 * @param n Number
 * @return char* Number \b n as a string
 * @attention Allocates memory
 */
char	*ft_itoa(int n);
/**
 * @brief List add back.
 *
 * @param lst
 * @param new
 */
void	ft_lstadd_back(t_list **lst, t_list *new);
/**
 * @brief List add front.
 *
 * @param lst
 * @param new
 */
void	ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Clear list.
 *
 * @param lst
 * @param del
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief Delete node.
 *
 * @param lst
 * @param del
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Iterate list.
 *
 * @param lst
 * @param f
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * @brief Last node in a list.
 *
 * @param lst
 * @return t_list*
 */
t_list	*ft_lstlast(t_list *lst);
/**
 * @brief List map.
 *
 * @param lst
 * @param f
 * @param del
 * @return t_list*
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/**
 * @brief Create a new node.
 *
 * @param content
 * @return t_list*
 */
t_list	*ft_lstnew(void *content);
/**
 * @brief Size of a list.
 *
 * @param lst
 * @return int
 */
int		ft_lstsize(t_list *lst);
/**
 * @brief Long to ASCII.
 *
 * Returns a number as a string.
 * @param n long Number
 * @return char* Number \b n as a string
 * @attention Allocates memory
 */
char	*ft_ltoa(long n);
/**
 * @brief Scan memory for a character.
 *
 * Scans \b n bytes of memory from address \b s for a character \b c.
 *
 * @param s Starting address
 * @param c Character to find
 * @param n Till how many bytes from the starting address \b s
 * @return void* Address of the found character or a NULL if character not found
 */
void	*ft_memchr(const void *s, int c, size_t n);
/**
 * @brief Memory compare.
 *
 * Compares \b n number of bytes from two addresses \b s1 and \b s1.
 * @param s1 First address
 * @param s2 Second address
 * @param n Number of bytes

 * @return int If \b s1 and \b s2 are equal returns 0.
 * Else returns difference of the byte that was not equal.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief Copies memory to destination.
 *
 * Copies \b n bytes of memory from source to destination.
 * @param dst Address of the destination
 * @param src Address of the source
 * @return void* Address of destination
 * @attention Does not handle overlapping.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);
/**
 * @brief Copy memory area.
 *
 * Copies \b len bytes of memory from source to destination.
 * @param dst Address of the destination
 * @param src Address of the source
 * @param len Number of bytes
 * @return void* Address of the destination
 */
void	*ft_memmove(void *dst, const void *src, size_t len);
/**
 * @brief Fill memory area with a contant byte.
 *
 * Fills \b len number of bytes of memory with \b c.
 * @param b Memory address
 * @param c Value to set the bytes to
 * @param len Number of bytes
 * @return void* Address of \b b
 */
void	*ft_memset(void *b, int c, int len);
/**
 * @brief Writes char to file.
 *
 * @param c
 * @param fd
 */
void	ft_putchar_fd(char c, int fd);
/**
 * @brief Writes new line to file.
 *
 * @param s
 * @param fd
 */
void	ft_putendl_fd(char *s, int fd);
/**
 * @brief Writes number to file.
 *
 * @param n
 * @param fd
 */
void	ft_putnbr_fd(int n, int fd);
/**
 * @brief Writes string to file.
 *
 * @param s
 * @param fd
 */
void	ft_putstr_fd(char *s, int fd);
/**
 * @brief Splits string to substrings.
 *
 * Splits string \b s by character \b c to substrings.
 * @param s String
 * @param c Character
 * @return char** Array of substrings
 * @attention Allocates memory
 */
char	**ft_split(char const *s, char c);
/**
 * @brief Search a character.
 *
 * Searches a character from a string and returns it's address.
 * @param s String
 * @param c Character
 * @return char* Address of the found character or NULL if not found
 */
char	*ft_strchr(const char *s, int c);
/**
 * @brief Duplicates a string.
 *
 * @param s1 String to make a copy from
 * @return char* Address of the new string
 */
char	*ft_strdup(const char *s1);
/**
 * @brief Calls a function for each char of a string.
 *
 * Function \b f takes the index and address of a character in the string.
 *
 * @param s String
 * @param f Function
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/**
 * @brief Joins two strings together.
 *
 * @param s1 String 1
 * @param s2 Strong 2
 * @return char* New string containing \b s1 and \b s2
 * @attention Allocates memory
 */
char	*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief Adds string to end of a string.
 *
 * Adds source to end of the destination limited by the destination size.
 *
 * @param dst String
 * @param src String
 * @param dstsize Size of the destination
 * @return size_t Sum of the lengths of source and destination
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/**
 * @brief Copies string to destination.
 *
 * Copies string to destination and makes sure it's null terminated.
 *
 * @param dst String
 * @param src String
 * @param dstsize Size of the destination
 * @return size_t Lenght of the source
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/**
 * @brief Length of the string.
 *
 * @param s String
 * @return size_t Length of the string
 */
size_t	ft_strlen(const char *s);
/**
 * @brief Create a copy of a string passing each char through a function.
 *
 * Creates a new string and assigns the values to that string by
 * taking a character from the string \b s
 * and passing it trough the function \b f.
 * Function \b f takes a character and index of that character as parameters.
 *
 * @param s String
 * @param f	Function
 * @return char* New string
 * @attention Allocates memory
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * @brief String compare.
 *
 * Compares two strings and returns the difference of the first missmatch
 * character or 0 if strings are equal.
 *
 * @param s1 String
 * @param s2 String
 * @param n Number of characters to check
 * @return int 0 if equal else the difference of the first missmatch character
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Search string from string.
 *
 * Searches string from a string and returns
 * the address of the start of the found string.
 *
 * @param haystack String
 * @param needle String
 * @param len How many char to check
 * @return char* Address of the found string
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
/**
 * @brief Search a character starting from the end.
 *
 * Searches a character from a string and returns it's address.
 *
 * @param s String
 * @param c Character
 * @return char* Address of found char or NULL if not found
 */
char	*ft_strrchr(const char *s, int c);
/**
 * @brief Trim start and end of a string.
 *
 * Trims set of characters from start and end of a string.
 *
 * @param s1 String
 * @param set Set of character to trim from the string
 * @return char* Trimmed string
 * @attention Allocates memory
 */
char	*ft_strtrim(char const *s1, char const *set);
/**
 * @brief Gets a piece of string out of a string.
 *
 * Gets \b len length piece of string from a strung starting at index \b start.
 * @param s String
 * @param start Starting index
 * @param len How many chars
 * @return char* Address of the new substring
 * @attention Allocates memory
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Changes char to lowercase.
 *
 * @param c
 * @return int
 */
int		ft_tolower(int c);
/**
 * @brief Changes char to uppercase.
 *
 * @param c
 * @return int
 */
int		ft_toupper(int c);
/**
 * @brief Unsigned long to lowercase hexadesimal string.
 *
 * @param n unsigned long
 * @return char* hexadesimal string in lowercase
 * @attention Allocates memory
 */
char	*ft_ulongtohex(unsigned long n);

#endif
