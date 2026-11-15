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

static int	test_failures;

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
	return (test_failures != 0);
}
