int		ft_ceil_sqrt(int n)
{
	int		i;

	i = 0;
	while (i * i < n)
		i++;
	return (i);
}