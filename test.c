/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novella <novella@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 18:06:06 by novella           #+#    #+#             */
/*   Updated: 2026/11/15 19:19:59 by novella          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BLUE "\033[34m"

t_list	*ft_lstlast(t_list *lst);
unsigned int	ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

static int	test_failures;
static int	deleted_contents;

static void	print_status(int matches)
{
	if (matches)
		printf(GREEN "✅OK\n" RESET);
	else
	{
		printf(RED "❌FAIL\n" RESET);
		test_failures++;
	}
}

static int	int_returnchecker(int (*f1)(int), int (*f2)(int), int nb,
		int compare_boolean)
{
	int	value1;
	int	value2;

	value1 = f1(nb);
	value2 = f2(nb);
	printf("Input: %d | standard: %d | ft: %d | ", nb, value1, value2);
	if (compare_boolean)
	{
		value1 = (value1 != 0);
		value2 = (value2 != 0);
	}
	print_status(value1 == value2);
	return (value1 == value2);
}

static void	test_unary_int(const char *name, int (*f1)(int),
		int (*f2)(int), const int *values, size_t count, int compare_boolean)
{
	size_t	i;

	printf(BLUE "\n%s\n" RESET, name);
	i = 0;
	while (i < count)
	{
		int_returnchecker(f1, f2, values[i], compare_boolean);
		i++;
	}
}

static void	check_int_values(const char *name, int value1, int value2)
{
	printf("%s | standard: %d | ft: %d | ", name, value1, value2);
	print_status(value1 == value2);
}

static int	compare_sign(int value)
{
	if (value < 0)
		return (-1);
	if (value > 0)
		return (1);
	return (0);
}

static void	check_comparison(const char *name, int value1, int value2)
{
	check_int_values(name, compare_sign(value1), compare_sign(value2));
}

static void	check_condition(const char *name, int condition)
{
	printf("%s | ", name);
	print_status(condition);
}

static void	check_string(const char *name, const char *actual,
		const char *expected)
{
	printf("%s | ", name);
	print_status(actual != NULL && strcmp(actual, expected) == 0);
}

static void	check_bytes(const char *name, const void *actual,
		const void *expected, size_t size)
{
	printf("%s | ", name);
	print_status(memcmp(actual, expected, size) == 0);
}

static void	check_size(const char *name, size_t actual, size_t expected)
{
	printf("%s | actual: %zu | expected: %zu | ", name, actual, expected);
	print_status(actual == expected);
}

static void	test_memory_functions(void)
{
	unsigned char	source[] = {'A', '\0', 'B', 'C'};
	unsigned char	actual[8];
	unsigned char	expected[8];
	unsigned char	move_actual[8] = "abcdef";
	unsigned char	move_expected[8] = "abcdef";
	unsigned char	*zeroed;
	size_t			i;

	printf(BLUE "\nMEMORY FUNCTIONS\n" RESET);
	check_condition("ft_memset returns destination",
		ft_memset(actual, 'x', sizeof(actual)) == actual);
	memset(expected, 'x', sizeof(expected));
	check_bytes("ft_memset contents", actual, expected, sizeof(actual));
	ft_bzero(actual, 3);
	memset(expected, 0, 3);
	check_bytes("ft_bzero", actual, expected, sizeof(actual));
	check_condition("ft_memcpy returns destination",
		ft_memcpy(actual, source, sizeof(source)) == actual);
	check_bytes("ft_memcpy copies embedded null", actual, source,
		sizeof(source));
	memmove(move_expected + 2, move_expected, 4);
	check_condition("ft_memmove returns destination",
		ft_memmove(move_actual + 2, move_actual, 4) == move_actual + 2);
	check_bytes("ft_memmove overlap", move_actual, move_expected,
		sizeof(move_actual));
	check_condition("ft_memchr finds embedded null",
		ft_memchr(source, '\0', sizeof(source)) == source + 1);
	check_condition("ft_memchr misses outside length",
		ft_memchr(source, 'C', 3) == NULL);
	zeroed = ft_calloc(4, sizeof(int));
	check_condition("ft_calloc allocates", zeroed != NULL);
	if (zeroed != NULL)
	{
		i = 0;
		while (i < 4 * sizeof(int) && zeroed[i] == 0)
			i++;
		check_condition("ft_calloc zeroes memory", i == 4 * sizeof(int));
		free(zeroed);
	}
}

static char	map_character(unsigned int index, char c)
{
	if (index % 2 == 0)
		return (ft_toupper(c));
	return (ft_tolower(c));
}

static void	iter_character(unsigned int index, char *c)
{
	(void)index;
	*c = ft_toupper(*c);
}

static void	test_string_functions(void)
{
	char		buffer[16];
	char		*result;
	char		**parts;
	char		haystack[] = "libft tester";
	size_t		length;
	size_t		i;

	printf(BLUE "\nSTRING FUNCTIONS\n" RESET);
	check_size("ft_strlen", ft_strlen("libft"), strlen("libft"));
	result = ft_strdup("libft test");
	check_string("ft_strdup", result, "libft test");
	free(result);
	check_condition("ft_strchr", ft_strchr("banana", 'n') == strchr("banana", 'n'));
	check_condition("ft_strchr finds nul",
		ft_strchr("banana", '\0') == strchr("banana", '\0'));
	check_condition("ft_strrchr", ft_strrchr("banana", 'a')
		== strrchr("banana", 'a'));
	check_condition("ft_strrchr misses", ft_strrchr("banana", 'x') == NULL);
	check_condition("ft_strnstr finds substring",
		ft_strnstr(haystack, "test", 12) == haystack + 6);
	check_condition("ft_strnstr respects length",
		ft_strnstr(haystack, "tester", 10) == NULL);
	memset(buffer, 'x', sizeof(buffer));
	length = ft_strlcpy(buffer, "libft", 4);
	check_string("ft_strlcpy truncates", buffer, "lib");
	check_size("ft_strlcpy return", length, 5);
	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, "42", 3);
	length = ft_strlcat(buffer, "Libft", 6);
	check_string("ft_strlcat truncates", buffer, "42Lib");
	check_size("ft_strlcat return", length, 7);
	result = ft_strjoin("42", " Libft");
	check_string("ft_strjoin", result, "42 Libft");
	free(result);
	result = ft_substr("libft", 2, 2);
	check_string("ft_substr", result, "bf");
	free(result);
	result = ft_substr("libft", 20, 3);
	check_string("ft_substr past end", result, "");
	free(result);
	result = ft_strtrim("..libft..", ".");
	check_string("ft_strtrim", result, "libft");
	free(result);
	parts = ft_split("..one..two.", '.');
	check_condition("ft_split allocates", parts != NULL);
	if (parts != NULL)
	{
		check_string("ft_split first word", parts[0], "one");
		check_string("ft_split second word", parts[1], "two");
		check_condition("ft_split terminates array", parts[2] == NULL);
		i = 0;
		while (parts[i] != NULL)
			free(parts[i++]);
		free(parts);
	}
	check_condition("ft_split empty input",
		(parts = ft_split("", ',')) != NULL && parts[0] == NULL);
	if (parts != NULL)
		free(parts);
	result = ft_itoa(0);
	check_string("ft_itoa zero", result, "0");
	free(result);
	result = ft_itoa(-12345);
	check_string("ft_itoa negative", result, "-12345");
	free(result);
	result = ft_itoa(INT_MIN);
	check_string("ft_itoa INT_MIN", result, "-2147483648");
	free(result);
	result = ft_strmapi("aBc", map_character);
	check_condition("ft_strmapi contents",
		result != NULL && memcmp(result, "AbC", 3) == 0);
	free(result);
	memcpy(buffer, "aBc", 4);
	ft_striteri(buffer, iter_character);
	check_string("ft_striteri", buffer, "ABC");
}

static void	count_delete(void *content)
{
	(void)content;
	deleted_contents++;
}

static void	increment_content(void *content)
{
	(*(int *)content)++;
}

static void	*map_plus_ten(void *content)
{
	int	*mapped_content;

	mapped_content = malloc(sizeof(int));
	if (mapped_content)
		*mapped_content = *(int *)content + 10;
	return (mapped_content);
}

static void	free_content(void *content)
{
	free(content);
}

static void	test_lstmap(void)
{
	t_list	first;
	t_list	second;
	t_list	*mapped;
	int		first_value;
	int		second_value;

	printf(BLUE "\nFT_LSTMAP\n" RESET);
	first_value = 1;
	second_value = 2;
	first.content = &first_value;
	first.next = &second;
	second.content = &second_value;
	second.next = NULL;
	mapped = ft_lstmap(&first, map_plus_ten, free_content);
	check_condition("ft_lstmap maps each content",
		mapped != NULL && mapped->content != NULL && mapped->next != NULL
		&& mapped->next->content != NULL
		&& *(int *)mapped->content == 11
		&& *(int *)mapped->next->content == 12);
	check_condition("ft_lstmap leaves original unchanged",
		first_value == 1 && second_value == 2);
	ft_lstclear(&mapped, free_content);
	check_condition("ft_lstmap empty input", ft_lstmap(NULL,
			map_plus_ten, free_content) == NULL);
}

static void	test_list_functions(void)
{
	t_list	*list;
	t_list	*first;
	t_list	*second;
	int		first_value;
	int		second_value;
	int		front_value;

	printf(BLUE "\nLIST FUNCTIONS\n" RESET);
	list = NULL;
	first_value = 1;
	second_value = 2;
	front_value = 0;
	first = ft_lstnew(&first_value);
	second = ft_lstnew(&second_value);
	check_condition("ft_lstnew", first != NULL && first->content == &first_value
		&& first->next == NULL);
	ft_lstadd_back(&list, first);
	ft_lstadd_back(&list, second);
	check_condition("ft_lstadd_back", list == first && first->next == second);
	check_condition("ft_lstsize", ft_lstsize(list) == 2);
	check_condition("ft_lstlast", ft_lstlast(list) == second);
	ft_lstiter(list, increment_content);
	check_condition("ft_lstiter", first_value == 2 && second_value == 3);
	first = ft_lstnew(&front_value);
	ft_lsadd_front(&list, first);
	check_condition("ft_lsadd_front", list == first && first->next->content
		== &first_value);
	check_condition("ft_lstsize after front insert", ft_lstsize(list) == 3);
	ft_lstclear(&list, count_delete);
	check_condition("ft_lstclear empties list", list == NULL);
	check_condition("ft_lstclear calls deleter", deleted_contents == 3);
	first = ft_lstnew(&front_value);
	ft_lstdelone(first, count_delete);
	check_condition("ft_lstdelone calls deleter", deleted_contents == 4);
	check_condition("ft_lstlast empty list", ft_lstlast(NULL) == NULL);
	check_condition("ft_lstsize empty list", ft_lstsize(NULL) == 0);
}

static void	write_putchar_case(int fd)
{
	ft_putchar_fd('X', fd);
}

static void	write_putstr_case(int fd)
{
	ft_putstr_fd("libft", fd);
}

static void	write_putendl_case(int fd)
{
	ft_putendl_fd("libft", fd);
}

static void	write_putnbr_case(int fd)
{
	ft_putnbr_fd(INT_MIN, fd);
}

static void	check_output(const char *name, void (*writer)(int),
		const char *expected)
{
	FILE	*file;
	char	buffer[64];
	int		fd;
	size_t	size;

	file = tmpfile();
	if (file == NULL)
	{
		perror("tmpfile");
		check_condition(name, 0);
		return ;
	}
	fd = fileno(file);
	if (fd < 0)
	{
		perror("fileno");
		fclose(file);
		check_condition(name, 0);
		return ;
	}
	writer(fd);
	fflush(file);
	fseek(file, 0, SEEK_SET);
	size = fread(buffer, 1, sizeof(buffer) - 1, file);
	buffer[size] = '\0';
	check_string(name, buffer, expected);
	fclose(file);
}

static void	test_output_functions(void)
{
	printf(BLUE "\nFILE DESCRIPTOR FUNCTIONS\n" RESET);
	check_output("ft_putchar_fd", write_putchar_case, "X");
	check_output("ft_putstr_fd", write_putstr_case, "libft");
	check_output("ft_putendl_fd", write_putendl_case, "libft\n");
	check_output("ft_putnbr_fd", write_putnbr_case, "-2147483648");
}

static void	test_atoi(void)
{
	const char	*values[] = {"0", "42", "  -42", "+17", "123abc", "\t9"};
	size_t		i;

	printf(BLUE "\nFT_ATOI\n" RESET);
	i = 0;
	while (i < sizeof(values) / sizeof(values[0]))
	{
		printf("Input: \"%s\" | ", values[i]);
		check_int_values("atoi", atoi(values[i]), ft_atoi(values[i]));
		i++;
	}
}

static void	test_strncmp(void)
{
	printf(BLUE "\nFT_STRNCMP\n" RESET);
	check_comparison("equal", strncmp("abc", "abc", 3),
		ft_strncmp("abc", "abc", 3));
	check_comparison("different", strncmp("abc", "abd", 3),
		ft_strncmp("abc", "abd", 3));
	check_comparison("prefix", strncmp("ab", "abc", 3),
		ft_strncmp("ab", "abc", 3));
	check_comparison("zero length", strncmp("abc", "xyz", 0),
		ft_strncmp("abc", "xyz", 0));
}

static void	test_memcmp(void)
{
	const unsigned char	s1[] = {'a', '\0', 'b'};
	const unsigned char	s2[] = {'a', '\0', 'c'};

	printf(BLUE "\nFT_MEMCMP\n" RESET);
	check_comparison("equal", memcmp("abc", "abc", 3),
		ft_memcmp("abc", "abc", 3));
	check_comparison("different", memcmp("abc", "abd", 3),
		ft_memcmp("abc", "abd", 3));
	check_comparison("zero length", memcmp("abc", "xyz", 0),
		ft_memcmp("abc", "xyz", 0));
	check_comparison("embedded null", memcmp(s1, s2, 3),
		ft_memcmp(s1, s2, 3));
}

int	main(void)
{
	const int	alpha_values[] = {EOF, 0, 'A', 'z', '0', 255};
	const int	digit_values[] = {EOF, 0, '0', '9', 'A', 255};
	const int	alnum_values[] = {EOF, 0, 'A', 'z', '0', '!', 255};
	const int	ascii_values[] = {EOF, 0, 127, 128, 255};
	const int	print_values[] = {EOF, 0, ' ', '~', 127, 255};
	const int	lower_values[] = {EOF, 'A', 'Z', 'a', '0', 255};
	const int	upper_values[] = {EOF, 'a', 'z', 'A', '0', 255};

	test_unary_int("FT_ISALPHA", isalpha, ft_isalpha, alpha_values,
		sizeof(alpha_values) / sizeof(alpha_values[0]), 1);
	test_unary_int("FT_ISDIGIT", isdigit, ft_isdigit, digit_values,
		sizeof(digit_values) / sizeof(digit_values[0]), 1);
	test_unary_int("FT_ISALNUM", isalnum, ft_isalnum, alnum_values,
		sizeof(alnum_values) / sizeof(alnum_values[0]), 1);
	test_unary_int("FT_ISASCII", isascii, ft_isascii, ascii_values,
		sizeof(ascii_values) / sizeof(ascii_values[0]), 1);
	test_unary_int("FT_ISPRINT", isprint, ft_isprint, print_values,
		sizeof(print_values) / sizeof(print_values[0]), 1);
	test_unary_int("FT_TOLOWER", tolower, ft_tolower, lower_values,
		sizeof(lower_values) / sizeof(lower_values[0]), 0);
	test_unary_int("FT_TOUPPER", toupper, ft_toupper, upper_values,
		sizeof(upper_values) / sizeof(upper_values[0]), 0);
	test_atoi();
	test_strncmp();
	test_memcmp();
	test_memory_functions();
	test_string_functions();
	test_list_functions();
	test_lstmap();
	test_output_functions();
	return (test_failures != 0);
}
