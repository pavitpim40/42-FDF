int	ft_toupper(int c)
{
	if ((c >= 'a' && c <= 'z'))
		c = c - 32;
	return (c);
}


int	ft_whitespace(char c)
{
	if(c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isprefix(char *str, int base)
{
	if (base == 16 && str[0] == '0' && str[1] == 'x')
		return (1);
	if (base == 8 && str[0] == '0')
		return (1);
	if (base == 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B'))
		return (1);
	return (0);
}

int	ft_isdigit_base(char c, int base)
{
	char	*digits;
	int		i;

	digits = "0123456789ABCDEF";
	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (1);
		i++;
	}
	return (0);
}

int	ft_isnumber_inbase(char *str, int base)
{
	int i;

	i = 0;
	while(ft_whitespace(str[i]))
		i++;
	if(base != 10 && !ft_isprefix(&str[i], base))
		return (0);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit_base(str[i], base))
			return (0);
		i++;
	}
	return (1);
}

#include <stdio.h>
int main ()
{
	printf(ft_isnumber_inbase("0x123", 16) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0x123", 10) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0x123", 8) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0x123", 2) ? "true\n" : "false\n");
	printf("====================================\n");

	printf(ft_isnumber_inbase("0b101", 2) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0b101", 10) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0b101", 8) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0b101", 16) ? "true\n" : "false\n");
	printf("====================================\n");

	printf(ft_isnumber_inbase("0123", 2) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0123", 10) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0123", 8) ? "true\n" : "false\n");
	printf(ft_isnumber_inbase("0123", 16) ? "true\n" : "false\n");
	printf("====================================\n");
}